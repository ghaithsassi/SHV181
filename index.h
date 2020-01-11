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
#ifndef INDEX_H
#define INDEX_H

#include<bits/stdc++.h>
#include "word.h"
#include "stream.h"
using namespace std;

class Index{
    protected:
    map<string,int> fileIdList;  //change it to static
    map<int,string> fileIdListInverse; //change it to static
    public:
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

    virtual void push(string &,string &,wordAttributes &){}
    virtual inline void push(string &w,int fileId,wordAttributes &att){}
    
    virtual vector<pair<string,wordAttributes>> searchWord(string &){}

    virtual void save(){}
    virtual void load(){} 
    virtual void print(){}
    virtual void printFileList(){}
};




template<typename Container,typename SubContainer>
class containerDataStructure:public Index{
    
    Container index;
    public:
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

            // must be rechecked here
            SubContainer *subMap = new SubContainer;
            for(int i=0;i<n;i++){
                wordAttributes *wordAtt = new wordAttributes;
                mainIndex>>file_Id>>(*wordAtt);
                subMap->insert(subMap->end(),make_pair(file_Id,*wordAtt)); 
            }
            index.insert(index.end(), make_pair(s,*subMap));
        }
        fileIdFile.close();
        mainIndex.close();        
    }
    void printFileList(){
        for(map<string,int>::iterator it = fileIdList.begin();it != fileIdList.end();it++){
            cerr<<(it->first)<<endl;
        }
    }
    
};

//add multimap
typedef containerDataStructure<map<string,map<int,wordAttributes> >,map<int,wordAttributes> > map_map_index;
typedef containerDataStructure<map<string,vector<pair<int,wordAttributes>> >,vector<pair<int,wordAttributes>> > map_vec_index;
typedef containerDataStructure<unordered_map<string,vector<pair<int,wordAttributes>> >,vector<pair<int,wordAttributes>> > unorderedmap_vec_index;

#endif