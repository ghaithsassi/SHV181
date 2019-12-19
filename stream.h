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
#ifndef STREAM_H
#define STREAM_H

#include <bits/stdc++.h>
using namespace std;

// set delimiter for input
class my_ctype : public std::ctype<char>
{
    mask my_table[table_size];
    public:
    my_ctype(size_t refs = 0)
        : std::ctype<char>(&my_table[0], false, refs)
    {
        std::copy_n(classic_table(), table_size, my_table);
        list<char> nonAlphaNum({'-', '/', '+', '(', ')', '%', '.', ',', '$', '<', '>','[',']','*','\\','"','\'',':','!','?','#',';','~'});
        for(char c:nonAlphaNum){
            my_table[c] = (mask)space;
        }
    }
};
class tab_delimiter : public std::ctype<char>
{
    mask my_table[table_size];
    public:
    tab_delimiter(size_t refs = 0)
        : std::ctype<char>(&my_table[0], false, refs)
    {
        std::copy_n(classic_table(), table_size, my_table);
        my_table['\t'] = (mask)space;
    }
};


template <class T>
class stream : public T
{
    public:
    T *myStream;
    stream(T &strm)
    {
        myStream = &strm;
    }
    void close()
    {
        (this->myStream)->close();
    }
};

template <class T>
class input : public stream<T>
{
    public:
    input(T &strm) : stream<T>(strm){}
    void addDelimiter(){
        locale x(locale::classic(), new my_ctype);
        (this->getStream())->imbue(x);
    }
    void addTabDelimiter(){
        locale x(locale::classic(), new tab_delimiter);
        (this->getStream())->imbue(x);
    }
    template <class type>
    friend T &operator>>(input<T> &st, type &var)
    {
        *(st.myStream) >> var;
        return *(st.myStream);
    }
    T *getStream()
    {
        return this->myStream;
    }
};

template <class T>
class output : public stream<T>
{
    public:
    output(T &strm) : stream<T>(strm) {}
    template <class type>
    friend T &operator<<(output<T> &st, type &var)
    {
        *(st.myStream) << var;
        return *(st.myStream);
    }
};

#endif