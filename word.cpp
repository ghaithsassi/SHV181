#include "word.h"

word::word(){
        name = "";
}

word::word(string s){
        name = s;
}
string word::getWord(){
        return name;
}
void word::increaseOccurence(){
        occurence++;
    }
ostream & operator<<(ostream &out,word &w){
            out<<w.name<<" "<<w.occurence;
}
