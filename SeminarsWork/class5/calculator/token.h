#include <iostream>
#pragma once
using namespace std;

struct Token
{
    char kind;
    double value;
    string name;

    Token(char ch) : kind{ch}, value{0} {}

    Token(char ch, double val) : kind{ch}, value{val} {}

    Token(char ch, string n) : kind{ch}, name{n} {}
};

class Token_stream
{
    bool full{false};
    Token buffer{'\0'};

  public:
    Token_stream() {}

    Token get ();
    void putback (Token t);

    void ignore (char);
};

constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char set = 'S';
constexpr char constant = 'C';
constexpr char space = 's';
constexpr char help = 'h';

const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string setkey = "set";
const string constkey = "const";
const string helpkey = "help";

extern Token_stream ts;