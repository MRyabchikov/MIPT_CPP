#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct ElementLine
{
    string name;
    string type;
    string status = "None";
    vector<string> inputs;
};

istream& operator>> (istream& fin, ElementLine& obj)

{
    stringstream sstream;
    string str;
    getline(fin, str, '\n');
    sstream << str;

    sstream >> obj.name;
    sstream >> obj.type;
    if (obj.name == "source")
        sstream >> obj.status;
    else
    {
        sstream >> str;
        while (sstream >> str)
            obj.inputs.push_back(str);
    }
    return fin;
}

ostream& operator<< (ostream& fout, const ElementLine& obj)
{
    fout << "Name: " << obj.name << "\nType: " << obj.type << "\nStatus: " << obj.status << "\nInputs: ";
    for (int i = 0; i < int(obj.inputs.size()); i++)
        fout << obj.inputs[i] << " ";
    return fout;
}

int main (void)
{
    ifstream fin("SeminarsWork/class7/text.txt");
    vector<ElementLine> v;

    while (fin)
    {
        ElementLine tmp;
        fin >> tmp;
        if (fin)
            v.push_back(tmp);
    }
    for (auto curr : v)
        cout << curr << endl << endl;
}
