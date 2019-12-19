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
#include<bits/stdc++.h>
#include "file.h"
#include "indexing.h"
using namespace std;


int main(){
    int n = 10;
    int k=15;
    
    text test_text("dataset/test.txt");
    indexing searchIndex;

    /* indexing */
    
    searchIndex.indexPath("./dataset");
    (searchIndex.myindex)->save();
    

    
    //(searchIndex.myindex)->load();
    

    
    
    cout<<"-------search----------"<<endl;
    string s;
    getline(cin,s);
    searchIndex.search(s);

    
    return 0;
}