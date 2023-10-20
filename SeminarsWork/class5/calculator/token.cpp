#include "token.h"
#include <cctype>
#include <iostream>
using namespace std;

Token_stream ts;

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

    char ch;
    cin >> ch;

    switch (ch)
    {
    case quit:
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
        return Token{ch};

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