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
#ifndef FILE_H
#define FILE_H

#include<bits/stdc++.h>
#include "stream.h"
#include "word.h"
using namespace std;

class file{
    protected:
    string fileName;
    public:
    inline void setFilename(string filename){
        this->fileName = filename;
    }
    file(string filename){
        setFilename(filename);
    }
    virtual void close()=0;
    inline string getFileName(){
        return fileName;
    }
    virtual void open()=0;
    virtual bool getWord(string &)=0;
    virtual vector<string> getContents()=0;

};

class text:public file{
    ifstream ifile;
    public:
    text(string s):file(s){}
    //text():file<ifstream>(""){}
    inline void open(){
        ifile.open(this->fileName);
        locale x(locale::classic(), new my_ctype);
        ifile.imbue(x);
        //this->myfile = new input<ifstream>(ifile);
        //myfile->addDelimiter();
    }
    inline bool getWord(string &s){
             //if( *(this->myfile) >>s )return true;
             if( ifile>>s )return true;
             else return false;
    }
    inline void close(){
        ifile.close();
    }
    inline vector<string> getContents(){
        vector<string> vec;
        string s;
        while(getWord(s)){
            vec.push_back(s);
        }
        return vec;
    }

};

#endif
