#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool starts_with (const string& num, const string& prefix)
{
    if (prefix.size() > num.size())
        return false;
    return num.substr(0, prefix.size()) == prefix;
}

int ask_number (const string& num)
{
    int tmp;
    stringstream ss;
    ss << num;
    if (starts_with(num, "0x"))
        ss >> hex >> tmp;
    else if (starts_with(num, "0") && num != "0")
        ss >> oct >> tmp;
    else
        ss >> tmp;
    if (!ss)
        throw runtime_error("Invalid number");
    return tmp;
}

int main (void)
{
    cout << ask_number("0x123") << endl;
    cout << ask_number("0123") << endl;
    cout << ask_number("123") << endl;
    return 0;
}