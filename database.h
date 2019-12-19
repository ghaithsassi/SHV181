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
    map <string,map<int,word*>*> index;
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
                map<int,word*> &filesContainsWord = *(index[s]);
                auto fl = filesContainsWord.find(fileId);
                if(fl != filesContainsWord.end()){
                    filesContainsWord[fileId]->increaseOccurence();
                }else{
                    myword->increaseOccurence();
                    filesContainsWord[fileId] = myword;
                }
            }else{
                myword->increaseOccurence();
                map<int,word*> *filesContainsWord = new map<int,word*>({{fileId,myword}});
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
        ofileIdFile.open("index/fileId");

        output<ofstream> mainIndex(oIndFile);
        output<ofstream> fileIdFile(ofileIdFile);

        /* save data to files */ 
        for(auto it = index.begin();it!=index.end();it++){
            int n =(int) it->second->size();
            mainIndex<<it->first<<'\t'<<n<<'\t';
            for(auto jt = it->second->begin();jt!=it->second->end();jt++){
                mainIndex<<jt->first<<'\t'<<*(jt->second)<<'\t';
            }
            mainIndex<<""<<endl;
        }
        /* save file id */
        for(auto it = fileIdList.begin();it!=fileIdList.end();it++){
            fileIdFile<<it->first<<'\t'<<it->second<<endl;
        } 

        fileIdFile.close();
        mainIndex.close();
    }
    void load(){
        ifstream iIndFile,ifileIdFile;
        
        iIndFile.open("index/mainIndex");
        ifileIdFile.open("index/fileId");

        input<ifstream> mainIndex(iIndFile);
        mainIndex.addTabDelimiter();
        input<ifstream> fileIdFile(ifileIdFile);
        fileIdFile.addTabDelimiter();

        string s;
        int file_Id,n;
        
        while(fileIdFile>>s>>file_Id){
            fileIdList[s]=file_Id;
            fileIdListInverse[file_Id] = s;
        }

        while(mainIndex>>s){
            mainIndex>>n;
            map<int,word*>* subMap = new map<int,word*>;
            index[s] = subMap;
            for(int i=0;i<n;i++){
                word *myword = new word;
                mainIndex>>file_Id>>*myword;
                myword->setWord(s);
                (*subMap)[file_Id]=myword; 
            }
        }
     
        fileIdFile.close();
        mainIndex.close();        
    }
    
};
#endif