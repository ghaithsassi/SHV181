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
#ifndef INDEXING_H
#define INDEXING_H

#include<bits/stdc++.h>
#include <sys/types.h>
#include <dirent.h>
#include "database.h"
#include "file.h"
#include "ranking.h"
using namespace std;

class indexing{
    
    database *myindex;
    rankingAlgorithm *myRanker ;
    public:
    /* constructors  */ 
    indexing(){
        myindex = new mapBasedDataStructure;
        myRanker = new aLitleBitSmarterAlgorithm;
    } 
    indexing(database *db){
        myindex = db;
        myRanker = new notVerySmartRankingAlgorithm;
    }
    indexing(rankingAlgorithm *rA){
        myindex = new mapBasedDataStructure;
        myRanker = rA;
    }
    indexing(database *db,rankingAlgorithm *rA){
        myindex = db;
        myRanker = rA;
    }
    indexing(rankingAlgorithm *rA,database *db){
        myindex = db;
        myRanker =rA;
    }
    /* end of constructors */

    void indexFile(text &fileToBeIndexed){
        fileToBeIndexed.open();
        string w;
        string f = fileToBeIndexed.getFileName();
        while(fileToBeIndexed.getWord(w)){
            myindex->push(w,f);
        }
        fileToBeIndexed.close();
    }
    vector<pair<int,word*>> * findWordInIndex(string &s){
        word myword(s);
        myword.pipeline();
        string w = myword.getWord();
        return myindex->searchWord(w);        
    }
    void search(string s){
        istringstream stringstream(s);
        input<istringstream> searchTextStream(stringstream);
        searchTextStream.addDelimiter();
        map< string, vector<pair<int,word*>> * > *searchResault = new map< string, vector<pair<int,word*>> *>;
        string words;
        while(searchTextStream>>words){
            if(auto it = searchResault->find(words) != searchResault->end() )continue;
            vector<pair<int,word*>> * vec = findWordInIndex(words);
            (*searchResault)[words]=vec;
        }

        /* result */
        cout<<"-----result------"<<endl;
        vector<int> * result = myRanker->search(s,searchResault);
        for(int  i  = 0 ; i<(int)result->size();i++){
           cout<< myindex->getFileNameFromID((*result)[i])<<endl;
       }
        delete result;

       
        /*
        for(auto it  = searchResault->begin();it!=searchResault->end();it++){
            int n = (int)(it->second)->size();
            for(auto i = it->second->begin();i!=it->second->end();i++){
              cout<<it->first<<" file:"<<myindex->getFileNameFromID(i->first)<<'\t'<<*(i->second)<<endl;
            }
        }
        */
        
       delete searchResault;

    }
    void indexPath(string path){
        DIR* dirp = opendir(path.c_str());
        struct dirent * dp;
        int i(0);
        while ((dp = readdir(dirp)) != NULL) {
            i++;
            string extension;
            string name=dp->d_name;
            size_t j = name.rfind('.', name.length());
            if (j != string::npos) extension=name.substr(j+1, name.length() - j);
            else extension="";
            string file_path;
            file_path=path+"/"+dp->d_name;
            if(extension=="txt") {
                //cout<<"File : "<<dp->d_name<<" is indexed"<<endl;
                text txt(file_path);
                indexFile(txt);
            }
            if (i!=1 && i!=2 && extension==""){
                string dir;
                dir=path+"/"+dp->d_name;
                indexPath(dir);
            }
 
        }
        closedir(dirp);
    }
    void saveIndex(){
        myindex->save();
    }
    void loadIndex(){
        myindex->load();
    }

};

#endif