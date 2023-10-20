#include "token.h"
#include "variable.h"
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
        return get_value(t.name);

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
    if (t.kind != name)
        throw runtime_error("name expected in declaration");

    string var = t.name;
    if (is_declared(var))
    {
        throw runtime_error("Redeclaration of " + var);
    }
    t = ts.get();
    if (t.kind != '=')
        throw runtime_error("'=' missing in declaration of " + var);

    return define_name(var, expression());
}

double statement ()
{
    Token t = ts.get();
    switch (t.kind)
    {
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
    define_name("pi", 3.141592653589793);
    define_name("e", 2.718281828459045);

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
