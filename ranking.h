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
    static bool compare(pair<string,wordAttributes> C1,pair<string,wordAttributes>  C2){
        return C1.second < C2.second;
    }
    public:
    virtual vector<string> * sortfiles(string ch, map< string, vector<pair<string,wordAttributes>> >*searchResault)=0;
};

class notVerySmartRankingAlgorithm:public rankingAlgorithm{
    public:
    vector<string> * sortfiles(string ch, map< string, vector<pair<string,wordAttributes>> > *searchResault){
        set<string> searchResaultFiles;
        string words;
        vector<string> *vec = new vector<string>;

        for(auto it = searchResault->begin();it != searchResault->end();it++){
            for(auto jt = (it->second).begin(); jt!=(it->second).end();jt++){
                //cerr<<*(it->second)<<" file:"<<myindex->getFileNameFromID(it->first)<<endl;
                auto it2 = searchResaultFiles.find(jt->first);
                if( it2==searchResaultFiles.end()) {
                                searchResaultFiles.insert(jt->first);
                                vec->push_back(jt->first);
                }                                       
            }
        }
        /* sort files here */
        
        /* return result */
        return vec;

    }
};


class aLitleBitSmarterAlgorithm:public rankingAlgorithm{
    public:
        vector<string> * sortfiles(string ch, map< string, vector<pair<string,wordAttributes>> > *searchResault){
        // map key : file id value : occurence     
        map<string,wordAttributes> searchResaultFiles;
        string words;
        vector<pair<string,wordAttributes>> vecIntermediate;
        vector<string> *vec = new vector<string>;

        // iterate through the words in the search sentence
        for(auto it = searchResault->begin();it != searchResault->end();it++){
            //iterate through the files
            for(auto jt = (it->second).begin(); jt!=(it->second).end();jt++){
                auto it2 = searchResaultFiles.find(jt->first);
                if( it2==searchResaultFiles.end()) {
                                searchResaultFiles[jt->first]= (jt->second);
                }else{
                                searchResaultFiles[jt->first]+= (jt->second);
                }                                       
            }
        }
        /* sort files here */
        // copy the result a vector
        for(auto it= searchResaultFiles.begin();it!=searchResaultFiles.end();it++){
            // push the pair < file ,occurence  > in the vector
            vecIntermediate.push_back(make_pair(it->first,it->second));
        }
        // sort according to occurence

        sort(vecIntermediate.begin(),vecIntermediate.end(),compare);

        int n = (int)vecIntermediate.size();
        for(int i = n-1;i>=0;i--){
            vec->push_back(vecIntermediate[i].first);
        }
        /* return result */
        return vec;

    }
};

class smarterAlgorithm:public rankingAlgorithm{
    public:
        vector<string> * sortfiles(string ch, map< string, vector<pair<string,wordAttributes>> > *searchResault){
        // map key : file id value : occurence     
        map<string,wordAttributes> searchResaultFiles;
        string words;
        vector<pair<string,wordAttributes>> vecIntermediate;
        vector<string> *vec = new vector<string>;

        // iterate through the words in the search sentence
        for(auto it = searchResault->begin();it != searchResault->end();it++){
            //iterate through the files
            for(auto jt = (it->second).begin(); jt!=(it->second).end();jt++){
                auto it2 = searchResaultFiles.find(jt->first);
                if( it2==searchResaultFiles.end()) {
                                searchResaultFiles[jt->first]= (jt->second);
                                //vec->push_back(jt->first);
                }else{
                                searchResaultFiles[jt->first]+= (jt->second);
                }                                       
            }
        }
        /* sort files here */
        // copy the result a vector
        for(auto it= searchResaultFiles.begin();it!=searchResaultFiles.end();it++){
            // push the pair < occurence   , file > in the vector
            vecIntermediate.push_back(make_pair(it->first,it->second));
        }
        // sort according to occurence
        sort(vecIntermediate.begin(),vecIntermediate.end(),compare);
        int n = (int)vecIntermediate.size();
        for(int i = n-1;i>=max(0,n-5);i--){
            vec->push_back(vecIntermediate[i].first+ " " + to_string(vecIntermediate[i].second));
        }
        /* return result */
        return vec;

    }
};

class evenMoreSmarterAlgorithm:public rankingAlgorithm{
    public:
        vector<string> * sortfiles(string ch, map< string, vector<pair<string,wordAttributes>> > *searchResault){
        // map key : file id value : occurence     
        map<string,wordAttributes> searchResaultFiles;
        string words;
        vector<pair<string,wordAttributes>> vecIntermediate;
        vector<string> *vec = new vector<string>;

        // iterate through the words in the search sentence
        for(auto it = searchResault->begin();it != searchResault->end();it++){
            if(it == searchResault->begin()){
                    //iterate through the files of first word
                    for(auto jt = (it->second).begin(); jt!=(it->second).end();jt++){
                                            searchResaultFiles[jt->first]=(jt->second);
                                  
                    }

            }
            else{

                    //iterate through the files
                    for(auto jt = (it->second).begin(); jt!=(it->second).end();jt++){
                        auto it2 = searchResaultFiles.find(jt->first);
                        if( it2!=searchResaultFiles.end()) {
                                        searchResaultFiles[jt->first]+= (jt->second);

                        }
                    }                                       
                }

        }
        /* sort files here */
        // copy the result a vector
        for(auto it= searchResaultFiles.begin();it!=searchResaultFiles.end();it++){
            // push the pair < occurence   , file > in the vector
            vecIntermediate.push_back(make_pair(it->first,it->second));
        }
        // sort according to occurence
        sort(vecIntermediate.begin(),vecIntermediate.end(),compare);
        int n = (int)vecIntermediate.size();
        for(int i = n-1;i>=max(0,n-5);i--){
            vec->push_back(vecIntermediate[i].first);
        }
        /* return result */
        return vec;

    }
};

class intelligenceAlgorithm:public rankingAlgorithm{
    static bool compareWordCount(tuple<string,int,wordAttributes> T1,tuple<string,int,wordAttributes> T2){
        return (get<1>(T1)) < (get<1>(T2));
    }
    static bool compareWordOcc(tuple<string,int,wordAttributes> T1,tuple<string,int,wordAttributes> T2){
        return (get<2>(T1)) < (get<2>(T2));
    }
    public:
        vector<string> * sortfiles(string ch, map< string, vector<pair<string,wordAttributes>> > *searchResault){
        // map key : file id value : pair< nbre of words , occurence>     
        map<string,pair<int,wordAttributes>> searchResaultFiles;
        string words;
        vector<tuple<string,int,wordAttributes>> vecIntermediate;
        vector<string> *vec = new vector<string>;

        // iterate through the words in the search sentence
        for(auto it = searchResault->begin();it != searchResault->end();it++){
                    //iterate through the files
                    for(auto jt = (it->second).begin(); jt!=(it->second).end();jt++){
                        auto it2 = searchResaultFiles.find(jt->first);
                        if( it2!=searchResaultFiles.end()) {
                                        searchResaultFiles[jt->first].first++;
                                        searchResaultFiles[jt->first].second+=(jt->second);
                        }else{
                            searchResaultFiles.insert(make_pair(jt->first, make_pair(1,(jt->second))));
                        }
                    }                                       


        }

        
        /* sort files here */
        // copy the result a vector
        for(auto it= searchResaultFiles.begin();it!=searchResaultFiles.end();it++){
            // push the pair < occurence   , file > in the vector
            vecIntermediate.push_back(make_tuple(it->first,(it->second).first,(it->second).second));
        }


        // sort 
        sort(vecIntermediate.begin(),vecIntermediate.end(),compareWordOcc);
        sort(vecIntermediate.begin(),vecIntermediate.end(),compareWordCount);

        int n = (int)vecIntermediate.size();
        for(int i = n-1;i>=max(0,n-5);i--){
            vec->push_back( (get<0>(vecIntermediate[i])) +" "+ to_string( get<2>(vecIntermediate[i]) ) );
        }
        /* return result */
        return vec;

    }
};


#endif