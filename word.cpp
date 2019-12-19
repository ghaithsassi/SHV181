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
#include "word.h"

word::word(){
        name = "";
}

word::word(string s){
        name = s;
        /* transform data to lower case */
        transform(name.begin(), name.end(), name.begin(),[](unsigned char c){ return std::tolower(c); });
}
string word::getWord(){
        return name;
}
void word::increaseOccurence(){
        occurence++;
    }
int word::getOccurence(){
        return this->occurence;
}
void word::pipeline(){
        if((int)name.size()<2)name = "";
}

ostream & operator<<(ostream &out,word &w){
        out<<w.name<<'\t'<<w.occurence;
}
istream & operator>>(istream &in, word &w){
        in>>w.name>>w.occurence;
}
