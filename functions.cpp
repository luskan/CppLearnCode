#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include<iostream>
#include<vector>
#include<map>
#include "functions.h"

using namespace std;

template <typename T>
double sum(const T& data)
{
    double temp_sum = 0;
    typename T::const_iterator iter = data.end();
    while ( iter != data.begin() )
    {
        --iter;
        temp_sum+=(*iter);  
    }
    return temp_sum;
}

template<>
inline double sum<map<string, double>>(const map<string, double>& M)
{
    double temp_sum = 0;
    map<string, double>::const_iterator iter = M.end();
    while (iter != M.begin())
    {
        --iter;
        temp_sum += iter->second;
    }
    return temp_sum;
}

#endif