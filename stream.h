#ifndef STREAM_H
#define STREAM_H

#include <bits/stdc++.h>
using namespace std;

template<class T>
class stream:public T{
    public:
    T *myStream;
    stream(T &strm){
        myStream  = & strm;
    }
};

template<class T>
class input:public stream<T>{
    public:
    input(T &strm):stream<T>(strm){}
    void close(){
        (this->myStream)->close();
    }
    template<class type>
    friend T & operator>>(input<T> &st,type &var){
                *(st.myStream)>>var;
                return *(st.myStream); 
    }
};

template<class T>
class output:public stream<T>{
    public:
    output(T &strm):stream<T>(strm){}
    template<class type>
    friend T &operator<<(output<T> &st,type &var){
                *(st.myStream)<<var;
                return *(st.myStream); 
    }
};


#endif