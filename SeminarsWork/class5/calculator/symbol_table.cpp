#include "symbol_table.h"
#include <iostream>
#include <vector>
using namespace std;

Symbol_table var_table;  // Здесь лежат все переменные нашего калькулятора

double Symbol_table::get_value(string s)
{
    for (int i = 0; i < int(var_table.size()); ++i)
        if (var_table[i].name == s)
            return var_table[i].value;

    throw runtime_error("get: undefined name " + s);
}

void Symbol_table::set_value(string s, double d)
{
    for (int i = 0; i <= int(var_table.size()); ++i)
    {
        if (var_table[i].name == s)
        {
            if (var_table[i].is_const == true)
                throw runtime_error("attempt to modify const value");
            var_table[i].value = d;
            return;
        }
    }

    throw runtime_error("set: undefined name " + s);
}

bool Symbol_table::is_declared(string s)
{
    for (int i = 0; i < int(var_table.size()); ++i)
        if (var_table[i].name == s)
            return true;

    return false;
}

double Symbol_table::define_name(string var, double val, bool is_const)
{
    if (is_declared(var))
        throw runtime_error(var + " declared twice");

    var_table.push_back(Variable{var, val, is_const});

    return val;
}

void Symbol_table::print_var_table() const
{
    for (auto var : var_table)
        cout << var.name << ": " << var.value << (var.is_const ? " - const\n" : "\n");
}