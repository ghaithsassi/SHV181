#include<bits/stdc++.h>

#include "file.h"
#include "indexing.h"
using namespace std;

class rankingAlgorithm{
    public:
    virtual void sort(){}
};
class ranker{
    public:
    rankingAlgorithm algorithm;
};
int main(){
    int n = 10;
    int k=15;
    text txt1("Tesla__Inc.txt");
    text txt2("Elon_Musk.txt");
    indexing myindex;
    myindex.indexFile(txt1);
    myindex.indexFile(txt2);
    /*
    unordered_map<string,unordered_map<int,word*>*> &ind = (myindex.myindex)->index;
    for(auto c = ind.begin();c!=ind.end();c++){
        for(auto d = (c->second)->begin();d!=(c->second)->end();d++){
            cout<<*(d->second)<<" file:"<<(d->first)<<endl;
        }
    }
   */
   cout<<"-------search----------"<<endl;
    string s;
    cin>>s;
    vector<pair<int,word*>> * vec = myindex.findWordInIndex(s);
    for(auto it = vec->begin();it!=vec->end();it++){
        cout<<*(it->second)<<" file:"<<(it->first)<<endl;
    }
    return 0;
}