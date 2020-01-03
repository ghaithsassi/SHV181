# SHV181 
## A File search engine build in C++
### Overview
    ------------------------------------------------------
          Welcome to SVH181 search engine


    [1] :search     [2] :index      [3] :index a file       [4] :index a path               [0] :exit
    [5] :load index [6] :save index

    >>
### Example
    >>1
    -------search----------
    elon musk
    -----result------
    search for elon musk
    
    ./dataset/Elon_Musk.txt
    ./dataset/Tesla__Inc.txt
    ./dataset/corpus/45567.txt
    ./dataset/corpus/63590.txt
    ./dataset/corpus/48489.txt
    --Search time : 0 h 0 min 0 sec

## Usage



## Building and Installing


### Install from git repository

you will need :
* C++ complier >= c++17

#### using terminal 
    git colne https://github.com/ghaithsassi/SHV181.git
    cd SHV181
#### Building classes
    g++ -c word.cpp 
    g++ -c stream.cpp 
    g++ -c file.cpp 
    g++ -c database.cpp 
    g++ -c ranking.cpp
    g++ -c engine.cpp
#### Building main 
    g++ -c main.cpp
#### Building exe file
    g++ word.o stream.o file.o database.o ranking.o engine.o main.o -o f
## Documentation


## Contributing
SHV181 is developed by [hmayma](https://github.com/ahmedyassine-hammami) and [ghaithsassi](https://github.com/ghaithsassi) as part of class project

## License
GNU General Public License v3.0 or later
See [LICENSE](LICENSE.md) to see the full text