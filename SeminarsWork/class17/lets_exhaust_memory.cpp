#include <iostream>
#include <vector>
using namespace std;

int main (void)
{
    constexpr int N = 10000;
    for (;;)
    {
        int* pv = new int[N];
        for (int i = 0; i < N; i++)
            pv[i] = 2;
        pv[5000] = 3;
    }
}