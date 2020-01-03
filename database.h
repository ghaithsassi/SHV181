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
    map<string,int> fileIdList;  //change it to static
    map<int,string> fileIdListInverse; //change it to static

    int pushfile(string &f){
        int fileNbrs = (int)(this->fileIdList).size(); 
        fileIdList[f] = fileNbrs;
        fileIdListInverse[fileNbrs] = f;
        return fileNbrs;
    }
    int getfileId(string &s){
        auto it = fileIdList.find(s);
        if(it  != fileIdList.end() )return (it->second);
        else return -1;
    }
    string getFileNameFromID(int n){
        auto it = fileIdListInverse.find(n);
        if(it != fileIdListInverse.end()){
            return it->second;
        }else
        {
            return "";
        }
        
    }
    virtual void push(string &,string &){}
    virtual void push(string &,int){}
    virtual void push(string &,string &,wordAttributes &){}

    virtual vector<pair<string,wordAttributes>> searchWord(string &){}
    virtual inline void push(string &w,int fileId,wordAttributes &att){}
    virtual void save(){}
    virtual void load(){} 
    virtual void print(){}
};


/*
class mapBasedDataStructure:public database{
    public:
    map <string,map<int,word*>*> index;
    void push(string &w,string &f){
            int fileId = this->getfileId(f);
            if(fileId ==-1 ){
                fileId = this->pushfile(f);
            }

            word *myword =this->analayzer(w);
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

        // save data to files
        for(auto it = index.begin();it!=index.end();it++){
            int n =(int) it->second->size();
            mainIndex<<it->first<<'\t'<<n<<'\t';
            for(auto jt = it->second->begin();jt!=it->second->end();jt++){
                mainIndex<<jt->first<<'\t'<<*(jt->second)<<'\t';
            }
            mainIndex<<""<<endl;
        }
        //save file id
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
*/


template<typename Container,typename SubContainer>
class containerDataStructure:public database{
    public:
    Container index;

    inline void push(string &w,int fileId,wordAttributes &att){

        typename Container::iterator it = find(index,w);
        if( it != index.end()){
            (it->second).insert((it->second).end(),make_pair(fileId,att));

        }else{
            SubContainer *filesContainsWord = new SubContainer;
            filesContainsWord->insert(filesContainsWord->end(),make_pair(fileId,att));
            index.insert(index.end(),make_pair(w,*filesContainsWord));
        }

    }
    
    inline void push(string &w,string &f,wordAttributes &att){
        int fileId = this->getfileId(f);
        if(fileId ==-1 ){
            fileId = this->pushfile(f);
        }
        
        w=word::pipeline(w);
        // don't add the word if it's not ok
        if(!(word::isOK(w)))return;


        typename Container::iterator it = find(index,w);
        if( it != index.end()){
            typename SubContainer::iterator fileVar = find((it->second),fileId);
            if(fileVar != (it->second).end()){
                //need to be secified push or update
                //(fileVar->second).method();
            }else{
                (it->second).insert((it->second).end(),make_pair(fileId,att));
            }
        }else{
            SubContainer *filesContainsWord = new SubContainer;
            filesContainsWord->insert(filesContainsWord->end(),make_pair(fileId,att));
            index.insert(index.end(),make_pair(w,*filesContainsWord));
        }

    }

    //here we increase the occurence
    inline void push(string &w,int fileId){

        w=word::pipeline(w);
        // don't add the word if it's not ok
        if(!(word::isOK(w)))return;


        typename Container::iterator it = find(index,w);
        if( it != index.end()){
            typename SubContainer::iterator fileVar = find((it->second),fileId);
            if(fileVar != (it->second).end()){
                //update
                (fileVar->second).add();
            }else{
                wordAttributes *att = new wordAttributes;
                (it->second).insert((it->second).end(),make_pair(fileId,*att));
            }
        }else{
            SubContainer *filesContainsWord = new SubContainer;
            wordAttributes *att = new wordAttributes;
            filesContainsWord->insert(filesContainsWord->end(),make_pair(fileId,*att));
            index.insert(index.end(),make_pair(w,*filesContainsWord));
        }

    }
    inline void push(string &w,string &f){
        int fileId = this->getfileId(f);
        if(fileId ==-1 ){
            fileId = this->pushfile(f);
        }
        push(w,fileId);
    }

    //spectial functions used to sreach in container
    // try to change the variables' names
    template<typename T,typename Key>
    inline static typename vector<T>::iterator find(vector<T> &c,Key value){
        typename vector<T>::iterator i = c.begin(); 
        for( ; i != c.end();i++){
            if(  (i->first)==value )return i;
        }
        return i;
    }
    template<typename Key,typename Value>
    inline static typename map<Key,Value>::iterator find(map<Key,Value> &c,Key value){
        typename map<Key,Value>::iterator  i = c.find(value);
        return i;
    }
    template<typename Key,typename Value>
    inline static typename unordered_map<Key,Value>::iterator find(unordered_map<Key,Value> &c,Key value){
        typename unordered_map<Key,Value>::iterator  i = c.find(value);
        return i;
    }


    // search 
    vector<pair<string,wordAttributes>> searchWord(string &w){
        vector<pair<string,wordAttributes>> filevector;
        typename Container::iterator it = find(index,w);
        if(it != index.end()){
                for(typename SubContainer::iterator jt = (it->second).begin();jt != (it->second).end();jt++){
                    filevector.push_back(make_pair(getFileNameFromID(jt->first),(jt->second)));
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
        for(typename Container::iterator it = index.begin();it!=index.end();it++){
            // word Subcontainer size
            int n =(int) (it->second).size();

            // write to main index
            mainIndex<<(it->first)<<'\t'<<n<<'\t';
            for(typename SubContainer::iterator jt = (it->second).begin();jt!=(it->second).end();jt++){
                mainIndex<<(jt->first)<<'\t'<<(jt->second)<<'\t';
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
            fileIdList.insert(fileIdList.end(),make_pair(s,file_Id));
            fileIdListInverse.insert(fileIdListInverse.end(),make_pair(file_Id,s));
        }

        while(mainIndex>>s){
            mainIndex>>n;
            // must be checked here
            SubContainer *subMap = new SubContainer;
            index.insert(index.end(), make_pair(s,*subMap));

            for(int i=0;i<n;i++){
                wordAttributes *wordAtt = new wordAttributes;
                mainIndex>>file_Id>>(*wordAtt);
                subMap->insert(subMap->end(),make_pair(file_Id,*wordAtt)); 
            }
        }
     
        fileIdFile.close();
        mainIndex.close();        
    }
    
};

//add multimap
typedef containerDataStructure<map<string,map<int,wordAttributes> >,map<int,wordAttributes> > map_map_DataStructure;
typedef containerDataStructure<map<string,vector<pair<int,wordAttributes>> >,vector<pair<int,wordAttributes>> > map_vec_DataStructure;
typedef containerDataStructure<unordered_map<int,map<int,wordAttributes> >,map<int,wordAttributes>> unorderedMap_map_DataStructure;


#endif