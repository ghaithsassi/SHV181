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
#ifndef WORD_H
#define WORD_H

#include <bits/stdc++.h>
using namespace std;

class word{
    public:
    string name;
    
    inline static string getWord(string &s){
        return s;
    }
    inline static string pipeline(string &s){
        transform(s.begin(), s.end(), s.begin(),[](unsigned char c){ return std::tolower(c); });
        return s;
    }
    bool compare(word s){
        return false;
    }
    bool compare(string s){
        return (s==name);
    }
    inline static bool isOK(string &s){
        return ( (int)s.size() > 2 );
    }

};

class score{
    int datatype; // 0 int 1 float
    union value{
        int n;
        float f;
        value(){}
        ~value(){};
    } value;
    public:
    score(){}
    score(int v){
        value.n = v;
        datatype = 0;
    }
    score(float v){
        value.f = v;
        datatype = 0;
    }
    friend ostream & operator<<(ostream &out,score &s){
        switch (s.datatype)
        {
        case 0:
            return out<<s.value.n;
        case 1:
            return out<<s.value.n;
        default:
            break;
        }
    }
    friend istream & operator>>(istream &in,score &s){
        switch (s.datatype)
        {
        case 0:
            int n;
            in>>n;
            s.value.n = n;
            return in;
        case 1:
            float f;
            in>>f;
            s.value.f = n;
            return in;
        default:
            return in;;
        }
    }
    bool operator<(score &other){
        if((datatype==other.datatype)){
            if(datatype == 0)return value.n < other.value.n;
            else if(datatype == 1) return value.f < other.value.f;
           
        }
    }
    bool operator<(int v){
        return value.n < v;
    }
    bool operator<(float v){
        return value.f < v;
    }
    score operator=(score other){
        datatype = other.datatype;
        value = other.value;
        return other;
    }
    score operator=(int v){
        datatype =0;
        value.n = v;
        return *this;
    }
    score operator=(float v){
        datatype =1;
        value.f = v;
        return *this;
    }
    score operator+=(int v){
        if(datatype == 0)value.n+=v;
        else if(datatype == 1)value.f+=v;
        return *this;
    }
    score operator+=(float v){
        if(datatype == 1)value.f+=v;
        return *this;
    }
    score operator+=(score &other){
        if(datatype == 0)value.n +=other.value.n;
        else if(datatype==1)value.f += other.value.f;
        return *this;
    }
    score operator+=(score other){
        if(datatype == 0)value.n +=other.value.n;
        else if(datatype==1)value.f += other.value.f;
        return *this;
    }
    score operator++(int){
        if(datatype == 0)value.n++;
        else if(datatype == 0)value.f++;
        return *this;
    }
    friend string to_string(score &s){
        if(s.datatype ==0) return to_string(s.value.n);
        else if(s.datatype == 0) return to_string(s.value.f);
        return "";
    }

};

class wordAttributes{
    protected:
    score myscore;
    public:
    void setScore(score s){
        myscore = s;
    }
    score getScore(){
        return myscore;
    }
    friend ostream & operator<<(ostream &out,wordAttributes &w){
        return out<<w.myscore;
    }
    //virtual ~wordAttributes()=0;
    friend istream & operator>>(istream &in, wordAttributes &w){
        return in>>w.myscore;
    }
    bool operator<(wordAttributes w){
        return (myscore< w.myscore); 
    }
    wordAttributes operator+=(wordAttributes other){
        myscore+=(other.getScore());
    }
    wordAttributes operator=(wordAttributes other){
        myscore=(other.getScore());
    }
    friend string to_string(wordAttributes w){
        return to_string(w.myscore);
    }
};

class occurence: public wordAttributes{
    //score template
    public:
    occurence(){
        myscore = 1;
    }
    occurence(int o){
        myscore =o;
    }
    void setScore(int o){
        myscore = o;
    }

    friend istream & operator>>(istream &in, occurence &w){
        int temp;
        in>>temp;
        w.myscore = temp;
    }
    bool operator<(int v){
        return (myscore < v); 
    }
    int operator++(int){
        myscore++;
    }
};


#endif