#pragma once
#include <cmath>
#include <iostream>
#include <map>
using namespace std;

typedef double (*math_func)(double);

struct Token
{
    char kind;
    double value;
    string name;
    math_func function;

    Token(char ch) : kind{ch}, value{0} {}

    Token(char ch, double val) : kind{ch}, value{val} {}

    Token(char ch, math_func func) : kind{ch}, function{func} {}

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

// Символы, изпользующиеся в качестве типов в Token
constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char set = 'S';
constexpr char constant = 'C';
constexpr char space = 's';
constexpr char help = 'h';
constexpr char math = 'M';
constexpr int interruption_key = 0;

// Ключевые слова и спец-символы
const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string setkey = "set";
const string constkey = "const";
const string helpkey = "help";
const string quitkey = "quit";

// Поддерживаемые математические функции
extern map<string, math_func> math_functions;

// Основной поток ввода
extern Token_stream ts;