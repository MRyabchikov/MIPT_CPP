#include <iostream>
#include <vector>
using namespace std;

const vector<string> noun_items{"C++", "fish", "birds"};
const vector<string> verb_items{"fly", "swim", "rules"};
const vector<string> conjuction_items{"and", "but", "or"};

bool contains (const vector<string>& v, const string& key)
{
    for (auto s : v)
        if (s == key)
            return true;
    return false;
}

bool sentence ()
{
    string word;
    cin >> word;
    if (!cin || !contains(noun_items, word))
        return false;
    cin >> word;
    if (!cin || !contains(verb_items, word))
        return false;
    cin >> word;
    if (!cin || word == ".")
        return true;
    if (!cin || !contains(conjuction_items, word))
        return false;
    return sentence();
}

int main (void)
{
    while (cin)
        cout << (sentence() ? "Ok\n" : "Not ok\n");
    return 0;
}