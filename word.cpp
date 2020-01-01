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

set<string> stopwordsList({
        "ourselves", "hers", "between", "yourself", "but", "again", "there", "about", "once", "during", "out", "very", "having", "with", "they", "own", "an", "be", "some", "for", "do", "its", "yours", "such", "into", "of", "most", "itself", "other", "off", "is", "s", "am", "or", "who", "as", "from", "him", "each", "the", "themselves", "until", "below", "are", "we", "these", "your", "his", "through", "don", "nor", "me", "were", "her", "more", "himself", "this", "down", "should", "our", "their", "while", "above", "both", "up", "to", "ours", "had", "she", "all", "no", "when", "at", "any", "before", "them", "same", "and", "been", "have", "in", "will", "on", "does", "yourselves", "then", "that", "because", "what", "over", "why", "so", "can", "did", "not", "now", "under", "he", "you", "herself", "has", "just", "where", "too", "only", "myself", "which", "those", "i", "after", "few", "whom", "t", "being", "if", "theirs", "my", "against", "a", "by", "doing", "it", "how", "further", "was", "here", "than"
});

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
bool word::isStopword(){
        auto it =  stopwordsList.find(name);
        if(it != stopwordsList.end())return true;
        else return false;
}
void word::pipeline(){
        /* remove any word under 2 charachers */ 
        if((int)name.size()<2)name = "";
        /* comment to deeactivate stop word removal */  
        if(this->isStopword())name = "";
}
void word::setWord(string s){
        name = s;
}

ostream & operator<<(ostream &out,word &w){
        out<<'\t'<<w.occurence;
}
istream & operator>>(istream &in, word &w){
        in>>w.occurence;
}
