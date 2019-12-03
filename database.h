/*
SHV181
Copyright (C) 2019  ghaith sassi

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
using namespace std;

class database{
    public:
    map<string,int> fileIdList;
    int pushfile(string &f){
        int fileNbrs = (int)(this->fileIdList).size(); 
        fileIdList[f] = fileNbrs;
        return fileNbrs;
    }
    int getfileId(string &s){
        auto it = fileIdList.find(s);
        if(it  != fileIdList.end() )return fileIdList[s];
        else return -1;
    }
    virtual void push(string &,string &f){}
    virtual vector<pair<int,word*>>* searchWord(string &){}
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
            string s = myword->getWord(); 
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
};

#endif