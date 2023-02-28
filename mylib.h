#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::string;
using std::copy;
using std::fixed;
using std::sort;
using std::streamsize;
using std::numeric_limits;
using std::vector;

struct Studentas
{
    string vardas, pavarde;
    vector<int> paz;
    float egz=0;
    double vid=0, med=0;
};

void pild(vector<Studentas> &studentai, int n);
void spausd(Studentas &temp, char rezimas);

#endif // MYLIB_H_INCLUDED
