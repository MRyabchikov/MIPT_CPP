#include "variable.h"
#include <iostream>
#include <vector>
using namespace std;

vector<Variable> var_table;

double get_value (string s)
{
    for (int i = 0; i < int(var_table.size()); ++i)
        if (var_table[i].name == s)
            return var_table[i].value;

    throw runtime_error("get: undefined name " + s);
}

void set_value (string s, double d)
{
    for (int i = 0; i <= int(var_table.size()); ++i)
    {
        if (var_table[i].name == s)
        {
            var_table[i].value = d;
            return;
        }
    }

    throw runtime_error("set: undefined name " + s);
}

bool is_declared (string s)
{
    for (int i = 0; i < int(var_table.size()); ++i)
        if (var_table[i].name == s)
            return true;

    return false;
}

double define_name (string var, double val)
{
    if (is_declared(var))
        throw runtime_error(var + " declared twice");

    var_table.push_back(Variable{var, val});

    return val;
}