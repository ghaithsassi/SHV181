#ifndef ANALYZER_H
#define ANALYZER_H

#include<bits/stdc++.h>
#include "file.h"
using namespace std;

class analyzer{
    public:
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