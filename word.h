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
    string getWord();
    void increaseOccurence();
    friend ostream & operator<<(ostream &,word &);
};

#endif