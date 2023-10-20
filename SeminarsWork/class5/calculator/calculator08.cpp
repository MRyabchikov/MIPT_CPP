#include "symbol_table.h"
#include "token.h"
#include <cmath>
#include <iostream>
using namespace std;

double expression ();

double primary ()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
            throw runtime_error("'(' expected");
        return d;
    }

    case '-':
        return -primary();
    case '+':
        return +primary();

    case number:
        return t.value;

    case name:
        return var_table.get_value(t.name);

    default:

        throw runtime_error("primary expected");
    }
}

double term ()
{
    double left = primary();

    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case '*':
            left *= primary();
            break;

        case '/':
        {
            double d = primary();
            if (d == 0)
                throw runtime_error("divide by zero");
            left /= d;
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0)
                throw runtime_error("divide by zero");
            left = fmod(left, d);
            break;
        }

        default:
            ts.putback(t);
            return left;
        }
    }
}

double expression ()
{
    double left = term();

    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case '+':
            left += term();
            break;

        case '-':
            left -= term();
            break;

        default:
            ts.putback(t);
            return left;
        }
    }
}

double declaration ()
{
    Token t = ts.get();
    bool is_const = false;
    if (t.kind == constant)
    {
        is_const = true;
        t = ts.get();
    }
    if (t.kind != name)
        throw runtime_error("name expected in declaration");

    string var = t.name;
    if (var_table.is_declared(var))
    {
        throw runtime_error("Redeclaration of " + var);
    }
    t = ts.get();
    if (t.kind != '=')
        throw runtime_error("'=' missing in declaration of " + var);

    return var_table.define_name(var, expression(), is_const);
}

double assignment ()
{
    Token t = ts.get();
    if (t.kind != name)
        throw runtime_error("name expected in assignment of");

    string var = t.name;
    if (!var_table.is_declared(var))
        throw runtime_error("Undefined name " + var);
    t = ts.get();
    if (t.kind != '=')
        throw runtime_error("'=' missing in assigment to " + var);

    var_table.set_value(var, expression());
    return var_table.get_value(var);
}

double statement ()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case set:
        return assignment();
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

void clean_up_mess () { ts.ignore(print); }

void calculate ()
{
    while (true)
        try
        {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();
            if (t.kind == quit)
                return;

            ts.putback(t);
            cout << result << statement() << endl;
        }
        catch (runtime_error& e)
        {
            cerr << e.what() << endl;
            clean_up_mess();
        }
}

int main ()
try
{
    var_table.define_name("pi", 3.141592653589793, true);
    var_table.define_name("e", 2.718281828459045, true);

    calculate();
}
catch (exception& e)
{
    cerr << "exception: " << e.what() << endl;
    return 1;
}
catch (...)
{
    cerr << "Oops, unknown exception" << endl;
    return 2;
}
