/*
Простой калькулятор
История версий :

Доработан Михаилом Рябчиковов в октябре 2023 г.
Переработан Бьярне Страуструпом в ма е 2007 г.
Переработан Бьярне Страуструпом в августе 2006 г.
Переработан Бьярне Страуструпом в августе 2004 г.
Разработан Бьярне Страуструпом (bs@cs . tamu . edu) весной 2004 г.
Эта программа реализует основные выражения калькулятора.
Ввод о существляется из потока cin; вывод - в поток cout.

Грамматика для ввода:

Вычисление:
    Инструкция
    Вывод
    Выход
    Вычисление инструкция

Инструкция:
    Объявление
    Присваивание
    Выражение

Объявление:
    "let" [const] имя = "выражение"
Присваивание:
    "set" имя = "выражение"

Выражение :
    Терм
    Выражение + Терм
    Выражение - Терм
Терм:
    Первичное_выражение
    Терм * Первичное_выражение
    Терм / Первичное_выражение
    Терм % Первичное_ выражение
Первичное_выражение :
    Число
    (Выражение)
    Математическая функция
    - Первичное_выражение
    + Первичное_выражение
Математическая функияЖ
    "имя_функции"("выражение")
Число :
    Литерал_с_плавающей_ точкой

Ввод из потока cin через Token s t ream с именем t s .
*/

#include "symbol_table.h"
#include "token.h"
#include <cmath>
#include <iostream>
using namespace std;

// Объявлена тут во избежание перекрестных вызовов
double expression ();

// Обработка математической функции
double mathematical_function (math_func f)
{
    Token t = ts.get();
    if (t.kind != '(')
        throw runtime_error("missing open paranthesis");
    double x = expression();
    t = ts.get();
    if (t.kind != ')')
        throw runtime_error("missing closing parenthesis");
    return f(x);
}

// Обработка первичного выражение
double primary ()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case math:
        return mathematical_function(t.function);
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

// Обработка терма
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

// Обработка выражения
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

// Обработка объявления
double declaration ()
{
    Token t = ts.get();
    bool is_const = false;
    if (t.kind == constant)
    {
        is_const = true;
        t = ts.get();  // В этом случае мы все еще не считали имя. Делаем это
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

// Обработка присваивания
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

// Обработка инструкции
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

void print_help ()
{
    cout << "operations :" << '\n'
         << "	addition A+B" << '\n'
         << "	subtraction A-B" << '\n'
         << "	multiplication A*B" << '\n'
         << "	division A/B" << '\n'
         << "	division with remainder A%B" << '\n'
         << "variables:" << '\n'
         << "	variable input - let name = value" << '\n'
         << "	input constants - let const name = value" << '\n'
         << "	assignment - set name = value" << '\n'
         << "existing variables:" << endl;
    var_table.print_var_table();  // Выводит все доступные переменные в формате имя: значение [- const]
}

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
            if (t.kind == help)
            {
                print_help();
                continue;
            }

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
