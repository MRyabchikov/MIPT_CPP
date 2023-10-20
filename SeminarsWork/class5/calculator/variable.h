#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Variable
{
    string name;
    double value;
    bool is_const = false;

    Variable(string n, double v, bool is_c = false) : name{n}, value{v}, is_const{is_c} {}
};

extern vector<Variable> var_table;

double get_value (string s);

void set_value (string s, double d);

bool is_declared (string s);

double define_name (string var, double val, bool is_const = false);