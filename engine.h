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
#ifndef ENGINE_H
#define ENGINE_H

#include<bits/stdc++.h>
#include <sys/types.h>
#include <dirent.h>
#include "database.h"
#include "file.h"
#include "ranking.h"
using namespace std;

class engine{
    
    database *myindex;
    rankingAlgorithm *myRanker ;
    public:
    /* constructors  */ 
    engine(){
        myindex = new map_map_DataStructure;
        myRanker = new aLitleBitSmarterAlgorithm;
    } 
    engine(database *db){
        myindex = db;
        myRanker = new notVerySmartRankingAlgorithm;
    }
    engine(rankingAlgorithm *rA){
        myindex = new map_vec_DataStructure;
        myRanker = rA;
    }
    engine(database *db,rankingAlgorithm *rA){
        myindex = db;
        myRanker = rA;
    }
    engine(rankingAlgorithm *rA,database *db){
        myindex = db;
        myRanker =rA;
    }
    /* end of constructors */


    inline void indexFile(file &fileToBeIndexed){
        vector<pair<string,wordAttributes>> stat = analyze(fileToBeIndexed);
        string f = fileToBeIndexed.getFileName();
        int fileId = myindex->getfileId(f);
        if(fileId != -1 ){
            // update instead of push
            return;
        }else{
            fileId  = myindex->pushfile(f);
        }
        int n =(int)stat.size();
        for(int i = 0;i<n;i++){
            myindex->push(stat[i].first,fileId,stat[i].second);
        }
        
    }

    /*
    inline void indexFile(file &fileToBeIndexed){
        fileToBeIndexed.open();
        string w;
        string f = fileToBeIndexed.getFileName();
        cerr<<f<<endl;
        int fileId = myindex->getfileId(f);
        if(fileId != -1 ){
            // update instead of push
            return;
        }else{
            fileId  = myindex->pushfile(f);
        }

        while(fileToBeIndexed.getWord(w)){
            myindex->push(w,fileId);
        }
        fileToBeIndexed.close();
    }
    */
    vector<pair<string,wordAttributes>> findWordInIndex(string &s){
        string w = word::pipeline(s);
        return myindex->searchWord(w);        
    }
    void search(string s){
        istringstream stringstream(s);
        input<istringstream> searchTextStream(stringstream);
        searchTextStream.addDelimiter();
        map< string, vector<pair<string,wordAttributes>> > *searchResault = new map< string, vector<pair<string,wordAttributes>> >;
        string words;
        while(searchTextStream>>words){
            /* make words go through pipe line */ 
            words = word::pipeline(words);

           /* ignore some words */
            if(!(word::isOK(words))) continue;

            /* add result to map */
            if(auto it = searchResault->find(words) != searchResault->end() )continue;
           vector<pair<string,wordAttributes>> vec = findWordInIndex(words);
            (*searchResault)[words]=vec;
        }

        /* result */
        cout<<"-----result------"<<endl;
        cout<<"search for "<<s<<endl<<endl;  
        vector<string> * result = myRanker->search(s,searchResault);
        for(auto  i  = result->begin() ; i!=result->end();i++){
           cout<<(*i)<<endl;
       }
        delete result;

       
        /*
        for(auto it  = searchResault->begin();it!=searchResault->end();it++){
            int n = (int)(it->second)->size();
            for(auto i = it->second->begin();i!=it->second->end();i++){
              cout<<it->first<<" file:"<<myindex->getFileNameFromID(i->first)<<'\t'<<*(i->second)<<endl;
            }
        }
        */
        
       delete searchResault;

    }
    void indexPath(string path){
        DIR* dirp = opendir(path.c_str());
        struct dirent * dp;
        int i(0);
        while ((dp = readdir(dirp)) != NULL) {
            i++;
            string extension;
            string name=dp->d_name;
            size_t j = name.rfind('.', name.length());
            if (j != string::npos) extension=name.substr(j+1, name.length() - j);
            else extension="";
            string file_path;
            file_path=path+"/"+dp->d_name;
            if(extension=="txt") {
                //cout<<"File : "<<dp->d_name<<" is indexed"<<endl;
                text txt(file_path);
                this->indexFile(txt);
            }
            if (i!=1 && i!=2 && extension==""){
                string dir;
                dir=path+"/"+dp->d_name;
                indexPath(dir);
            }
 
        }
        closedir(dirp);
    }
    void saveIndex(){
        myindex->save();
    }
    void loadIndex(){
        myindex->load();
    }
    vector<pair<string,wordAttributes>> analyze(file &myfile){
        myfile.open();
        vector<string> vec = myfile.getContents();
        map<string,int> occTemp;
        
        vector<pair<string,wordAttributes>> ans;

        string s;
        int n = (int)vec.size();
        for(int i =0;i<n;i++){
            s = word::pipeline(vec[i]);
            if(word::isOK(s)){
                occTemp[s] = occTemp[s]+1;
            };
        }
        for(map<string,int>::iterator it = occTemp.begin();it != occTemp.end();it++){
                wordAttributes att;
                att.setOccurence(it->second);
                ans.push_back(make_pair(it->first,att));

        } 
        return ans;
    }


};

#endif