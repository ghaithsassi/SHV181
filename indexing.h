#ifndef INDEXING_H
#define INDEXING_H

#include<bits/stdc++.h>
#include "database.h"
#include "file.h"
using namespace std;

class indexing{
    public:
    database *myindex = new datastracure;
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

        return myindex->searchWord(s);        
    }
    

};

#endif