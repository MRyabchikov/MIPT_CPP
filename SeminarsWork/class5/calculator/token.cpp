#include "token.h"
#include <cctype>
#include <iostream>
using namespace std;

Token_stream ts;

map<string, math_func> math_functions = {{"sin", sin},   {"cos", cos},   {"tan", tan},
                                         {"asin", asin}, {"acos", acos}, {"atan", atan}};

void Token_stream::putback(Token t)
{
    if (full)
        throw runtime_error("putback() into a full buffer");

    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    char ch = ' ';
    cin >> ch;
    if (!cin)
    {
        cin.clear();
        ignore(print);
        throw runtime_error("Bad token");
    }

    switch (ch)
    {
    case interruption_key:  // Тоже относим к символам, требующим выхода из программы
        return Token{quit};
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case ';':
    case '=':
        return Token{ch};  // Эти символы представояют сами себя

    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        cin.putback(ch);
        double val;
        cin >> val;
        return Token{number, val};
    }

    default:
        if (isspace(ch))
        {
            return Token{space};
        }
        if (isalpha(ch) || ch == '_')
        {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
                s += ch;
            cin.putback(ch);

            if (s == declkey)
                return Token{let};
            if (s == setkey)
                return Token{set};
            if (s == constkey)
                return Token{constant};
            if (s == helpkey)
                return Token{help};
            if (s == quitkey)
                return Token{quit};
            try
            {
                math_func target = math_functions.at(s);
                return Token{math, target};
            }
            catch (out_of_range& e)
            {
            }

            return Token{name, s};
        }
        throw runtime_error("Bad token");
    }
}

void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    char ch;
    while (cin >> ch)
        if (ch == c)
            return;
}