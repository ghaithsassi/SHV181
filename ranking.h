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
#ifndef RANKING_H
#define RANKING_H

#include<bits/stdc++.h>
#include "stream.h"
#include "word.h"
using namespace std;

class rankingAlgorithm{
    public:
    virtual vector<int> * search(string ch, map< string, vector<pair<int,word*>> * > *searchResault){}
};

class notVerySmartRankingAlgorithm:public rankingAlgorithm{
    public:
    vector<int> * search(string ch, map< string, vector<pair<int,word*>> * > *searchResault){
        set<int> searchResaultFiles;
        string words;
        vector<int> *vec = new vector<int>;

        for(auto it = searchResault->begin();it != searchResault->end();it++){
            for(auto jt = it->second->begin(); jt!=it->second->end();jt++){
                //cerr<<*(it->second)<<" file:"<<myindex->getFileNameFromID(it->first)<<endl;
                auto it2 = searchResaultFiles.find(jt->first);
                if( it2==searchResaultFiles.end()) {
                                searchResaultFiles.insert(jt->first);
                                vec->push_back(jt->first);
                }                                       
            }
        }
        
        delete &searchResaultFiles;

        /* sort files here */

        // but this is stupid ranking algorithom we do nothing here 
        
        /* return result */
        return vec;

    }
};

#endif