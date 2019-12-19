/*
SHV181
Copyright (C) 2019  ghaith sassi & ahmed yassine hammami 

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DATABASE_H
#define DATABASE_H

#include<bits/stdc++.h>
#include "word.h"
#include "stream.h"
using namespace std;

class database{
    public:
    map<string,int> fileIdList;
    map<int,string> fileIdListInverse;

    int pushfile(string &f){
        int fileNbrs = (int)(this->fileIdList).size(); 
        fileIdList[f] = fileNbrs;
        fileIdListInverse[fileNbrs] = f;
        return fileNbrs;
    }
    int getfileId(string &s){
        auto it = fileIdList.find(s);
        if(it  != fileIdList.end() )return fileIdList[s];
        else return -1;
    }
    string getFileNameFromID(int n)
    {
        auto it = fileIdListInverse.find(n);
        if(it != fileIdListInverse.end()){
            return it->second;
        }else
        {
            return "";
        }
        
    }
    virtual void push(string &,string &f){}
    virtual vector<pair<int,word*>>* searchWord(string &){}
    virtual void save(){}
    virtual void load(){}
};



class datastracure:public database{
    public:
    unordered_map <string,unordered_map<int,word*>*> index;
    void push(string &w,string &f){
            int fileId = this->getfileId(f);
            if(fileId ==-1 ){
                fileId = this->pushfile(f);
            }
            /* change word to root word */
            word *myword =new word(w);
            myword->pipeline();
            string s = myword->getWord();
            if(s==""){
                delete myword;
                return;
            }; 
            auto it = index.find(s);
            if( it != index.end()){
                unordered_map<int,word*> &filesContainsWord = *(index[s]);
                auto fl = filesContainsWord.find(fileId);
                if(fl != filesContainsWord.end()){
                    filesContainsWord[fileId]->increaseOccurence();
                }else{
                    myword->increaseOccurence();
                    filesContainsWord[fileId] = myword;
                }
            }else{
                myword->increaseOccurence();
                unordered_map<int,word*> *filesContainsWord = new unordered_map<int,word*>({{fileId,myword}});
                index[s] = filesContainsWord;
            }

    }
    vector<pair<int,word*>> *searchWord(string &w){
        vector<pair<int,word*>> * filevector = new vector<pair<int,word*>>;
        auto it = index.find(w);
        if(it != index.end()){
                for(auto it = index[w]->begin();it != index[w]->end();it++){
                    filevector->push_back(make_pair(it->first,it->second));
                }
        }
        return filevector;
    }
    void save(){
        ofstream oIndFile,oFilesMapedToWordFile,oWorldlist,ofileIdFile;
        oIndFile.open("index/mainIndex");
        oFilesMapedToWordFile.open("index/filesMapedToWord");
        oWorldlist.open("index/worldlist");
        ofileIdFile.open("index/fileId");

        output<ofstream> mainIndex(oIndFile);
        output<ofstream> filesMapedToWord(oFilesMapedToWordFile);
        output<ofstream> wordList(oWorldlist);
        output<ofstream> fileIdFile(ofileIdFile);

        /* keep track of pointer Id*/
        unordered_map<unordered_map<int,word*>*,int> subMapId;
        unordered_map<word*,int> wordId;

        /* save data to files */ 
        for(auto it = index.begin();it!=index.end();it++){
            /* save main indexfile key : string ; value : map id */ 
            auto findMap = subMapId.find(it->second);
            if(findMap == subMapId.end()){
                int subMapIdSize = (int)subMapId.size();
                subMapId[it->second]= subMapIdSize;
            }
            mainIndex<<it->first<<'\t'<<subMapId[it->second]<<endl;

            /* key : file id ; value : world id */
            for(auto jt = it->second->begin();jt!=it->second->end();jt++){
                auto findWord = wordId.find(jt->second);
                if(findWord == wordId.end()){
                    int wordIdSize = (int)wordId.size();
                    wordId[jt->second] = wordIdSize;
                }
                filesMapedToWord<<subMapId[it->second]<<'\t'<< jt->first <<'\t'<<wordId[jt->second]<<endl;
                wordList<<wordId[jt->second]<<'\t'<<*(jt->second)<<endl;

            }
        }
        /* save file id */
        for(auto it = fileIdList.begin();it!=fileIdList.end();it++){
            fileIdFile<<it->first<<'\t'<<it->second<<endl;
        } 

        fileIdFile.close();
        wordList.close();
        filesMapedToWord.close();
        mainIndex.close();
    }
    void load(){
        ifstream iIndFile,iFilesMapedToWordFile,iWorldlist,ifileIdFile;
        
        iIndFile.open("index/mainIndex");
        iFilesMapedToWordFile.open("index/filesMapedToWord");
        iWorldlist.open("index/worldlist");
        ifileIdFile.open("index/fileId");

        input<ifstream> mainIndex(iIndFile);
        mainIndex.addTabDelimiter();
        input<ifstream> filesMapedToWord(iFilesMapedToWordFile);
        filesMapedToWord.addTabDelimiter();
        input<ifstream> wordList(iWorldlist);
        wordList.addTabDelimiter();
        input<ifstream> fileIdFile(ifileIdFile);
        fileIdFile.addTabDelimiter();

        /* keep track of pointer Id*/
        unordered_map<int,unordered_map<int,word*>*> subMapId;
        unordered_map<int,word*> wordId;
        
        int word_Id;
        word *w = new word;
        while( (wordList>>word_Id>>(*w) ) ){
            wordId[word_Id] = w;
            w = new word;
        }

        unordered_map<int,word*> * subMap;
        int file_Id,subMap_Id;
        while(filesMapedToWord>>subMap_Id>>file_Id>>word_Id){
            auto it  = subMapId.find(subMap_Id);
            if(it != subMapId.end()){}
            else{
                subMap = new unordered_map<int,word*>;
                subMapId[subMap_Id]=subMap;
            }
            
            subMap = subMapId[subMap_Id];
            (*subMap)[file_Id] = wordId[word_Id];
        }
        string s;
        while(mainIndex>>s>>subMap_Id){
            auto it  = index.find(s);
            if(it != index.end()){}
            else{
                index[s] = subMapId[subMap_Id];
            }
        }
        while(fileIdFile>>s>>file_Id){
            fileIdList[s]=file_Id;
            fileIdListInverse[file_Id] = s;
        }
        
        fileIdFile.close();
        wordList.close();
        filesMapedToWord.close();
        mainIndex.close();

        
    }
    
};
#endif