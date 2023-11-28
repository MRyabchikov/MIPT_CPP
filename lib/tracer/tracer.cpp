#include "tracer.h"
#include <iostream>
using namespace std;

Tracer::Tracer(const string name, const string file, int line) : s{name}
{
    cerr << indent() << "IN --> " << s << " [" << file << " " << line << "]" << endl;
    Tracer::counter++;
}

Tracer::~Tracer()
{
    Tracer::counter--;
    cerr << indent() << "Out <--" << s << endl;
}

string Tracer::indent() const
{
    string s;
    for (int i = 0; i < Tracer::counter; i++)
        s += ".  ";
    return s;
}

int Tracer::counter{0};