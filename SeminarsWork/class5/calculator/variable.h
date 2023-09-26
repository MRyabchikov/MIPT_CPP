#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Variable
{
    string name;
    double value;

    Variable(string n, double v) : name{n}, value{v} {}
};

extern vector<Variable> var_table;

double get_value (string s);

void set_value (string s, double d);

bool is_declared (string s);

double define_name (string var, double val);