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
