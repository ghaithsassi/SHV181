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
/*
class word{
    private:
    string name;
    int occurence = 0;
    public:
    word();
    word(string);
    void setWord(string);
    string getWord();
    void increaseOccurence();
    void pipeline();
    int getOccurence();
    bool isStopword();
    
    friend ostream & operator<<(ostream &,word &);
    friend istream & operator>>(istream&, word &);
};

*/

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

class wordAttributes{
    public:
    int occurence = 1;
    inline int getOccurence(){
        return occurence;
    }
    inline void add(){
        occurence++;
    }
    inline void setOccurence(int o){
        this->occurence = o;
    }
    friend ostream & operator<<(ostream &out,wordAttributes &w){
        out<<w.occurence;
    }
    friend istream & operator>>(istream &in, wordAttributes &w){
        in>>w.occurence;
    }

};

#endif