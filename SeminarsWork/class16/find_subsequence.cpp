#include <iostream>
using namespace std;

const char* find_substring (const char* s, const char* x)
{
    const char *p = x, *pot_beg = nullptr;
    while (*s != '\0')
    {
        if (*s == *p)
        {
            if (pot_beg == nullptr)
                pot_beg = s;
            p++;
            if (*p == '\0')
                return pot_beg;
        }
        else
        {
            pot_beg = nullptr;
            p = x;
        }
        s++;
    }
    return pot_beg;
}

int main (void)
{
    cout << find_substring("What a nice day!", "day");
    return 0;
}