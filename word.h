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
    
    friend ostream & operator<<(ostream &,word &);
    friend istream & operator>>(istream&, word &);
};

#endif