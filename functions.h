#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;

template <typename T> 
double sum(const T& data);

template<>
double sum<map<string, double>>(const map<string, double>& M);

#ifndef FUNCTIONS_CPP
#include "functions.cpp"
#endif

#endif