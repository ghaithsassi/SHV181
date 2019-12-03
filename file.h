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
#ifndef FILE_H
#define FILE_H

#include<bits/stdc++.h>
#include "stream.h"
#include "word.h"
using namespace std;

template<class T>
class file{   
    protected:
    string fileName;
    input<T> *myfile;
    vector<word> worldList;
    public:
    void setFilename(string filename){
        this->fileName = filename;
    }
    file(string filename){
        setFilename(filename);
    }
    void close(){
        (*myfile).close();
    }
    string getFileName(){
        return fileName;
    }

    virtual void open()=0;
};
class text:public file<ifstream>{
    ifstream ifile;
    public:
    text(string s):file<ifstream>(s){}
    //text():file<ifstream>(""){}
    void open(){
        ifile.open(this->fileName);
        this->myfile = new input<ifstream>(ifile);
    }
    bool getWord(string &s){
             if((*(this->myfile)) >>s)return true;
             else return false;
    }

};

#endif
