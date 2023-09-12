#include <iostream>
using namespace std;

double slow_pow (double x, int n)
{
    double ans = 1;
    for (int i = 0; i < n; i++)
        ans *= x;
    return ans;
}

int main (void)
{
    cout << slow_pow(7, 0) << endl;
    cout << slow_pow(5, 3) << endl;
    return 0;
}