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