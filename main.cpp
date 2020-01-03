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
#include <time.h>
#include "file.h"
#include "engine.h"
#include "stream.h"
#include "ranking.h"

using namespace std;

int n;// this variable is not used

//#define inputStream cin
//#define outputStream cout

/* global varibales */

//notVerySmartRankingAlgorithm *algorithm = new notVerySmartRankingAlgorithm;
//aLitleBitSmarterAlgorithm *algorithm = new aLitleBitSmarterAlgorithm;
//smarterAlgorithm * algorithm = new smarterAlgorithm;
evenMoreSmarterAlgorithm *algorithm = new evenMoreSmarterAlgorithm;

engine searchEngine(algorithm);


input<istream> inputStream(cin);
output<ostream> outputStream(cout);


void duree(time_t,time_t);
void search();
void index();
void indexafile();
void indexapath();

int main(){
    //text test_text("dataset/test.txt");  // used for debug
    int q;

      outputStream<<"indexing dataset %%%%"<<endl;
      time_t begin=time(NULL);
      searchEngine.indexPath("./dataset");
      cout<<"--Indexation time : ";
      time_t end=time(NULL);
      duree(begin,end);

    outputStream<<"------------------------------------------------------"<<endl;
    outputStream<<"      Welcome to SVH181 search engine                 "<<endl;
    start:
    outputStream<<""<<endl<<endl;
    outputStream<<"[1] :search\t[2] :index\t[3] :index a file\t[4] :index a path\t\t[0] :exit"<<endl;
    outputStream<<"[5] :load index\t[6] :save index"<<endl<<endl;
    outputStream<<">>";
    inputStream>>q;
    switch (q)
    {
    case 0:
      return 0;
    case 1:
      search();
      goto start;
      break; // just to remove compiler warnning 
    case 2:
      index();
      goto start;
      break;
    case 3:
      indexafile();
      goto start; 
      break; 
    case 4 : 
        indexapath();
        goto start;
        break;
    case 5:
        outputStream<<"loading index %%%?"<<endl;
        searchEngine.loadIndex();
        goto start;
        break;
    case 6:
        outputStream<<"saving index %%%?"<<endl;
        searchEngine.saveIndex();
        goto start;
        break;

    default:
      goto start;
      break;
    }

    return 0;
}
void duree(time_t _begin, time_t _end) 
{
  double temp; 
  double hours=0, min=0, sec=0; 
  double dureeCalc = difftime(_end, _begin);
  temp = modf(dureeCalc/3600., &hours); 
  temp = modf(temp*60., &min); 
  temp = modf(temp*60., &sec); 
  cout<<hours<<" h "<<min<<" min "<<sec<<" sec"<<endl; 
}

inline void search(){
        string s;
        outputStream<<"-------search----------"<<endl;
        getline(inputStream,s);
        time_t begin1=time(NULL);
        searchEngine.search(s);
        outputStream<<"--Search time : ";
        time_t end1=time(NULL); 
        duree(begin1,end1);
}
inline void index(){
      outputStream<<"indexing dataset %%%%"<<endl;
      time_t begin=time(NULL);
      searchEngine.indexPath("./dataset");
      cout<<"--Indexation time : ";
      time_t end=time(NULL);
      duree(begin,end);
}
inline void indexafile(){
      string s="";
      outputStream<<"-------index a file----------"<<endl;
      outputStream<<"enter file path/name.txt: ";
      inputStream>>s;
      text myfile(s);
      searchEngine.indexFile(myfile);

}
inline void indexapath(){
      string s="";
      outputStream<<"-------index a path----------"<<endl;
      outputStream<<"enter path: ";
      inputStream>>s;
      searchEngine.indexPath(s);
}