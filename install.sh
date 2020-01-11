g++ -c word.cpp 
g++ -c stream.cpp 
g++ -c file.cpp 
g++ -c index.cpp 
g++ -c ranking.cpp
g++ -c engine.cpp -fopenmp
g++ -c main.cpp -fopenmp
g++ word.o stream.o file.o index.o ranking.o engine.o main.o -fopenmp -o f