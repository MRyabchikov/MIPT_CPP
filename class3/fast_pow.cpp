#include <iostream>
using namespace std;

double slow_pow (double x, int n)
{
    if (n <= 0 && x == 0)
    {
        throw runtime_error("Zero in non-positive power");
    }
    else if (n < 0)
        return slow_pow(1 / x, -n);
    double ans = 1;
    for (int i = 0; i < n; i++)
        ans *= x;
    return ans;
}

double fast_pow (double x, int n)
{
    if (n <= 0 && x == 0)
    {
        throw runtime_error("Zero in non-positive power");
    }
    else if (n < 0)
        return fast_pow(1 / x, -n);
    if (n == 0)
        return 1;
    else if (n % 2 == 0)
    {
        double tmp = fast_pow(x, n / 2);
        return tmp * tmp;
    }
    return x * fast_pow(x, n - 1);
}

int main (void)
{
    cout << slow_pow(7, 0) << endl;
    cout << slow_pow(5, 3) << endl;
    cout << slow_pow(2, -1) << endl;
    cout << fast_pow(2, 10) << endl;
    cout << fast_pow(5, 4) << endl;
    cout << fast_pow(2, -2) << endl;
    cout << fast_pow(0, -1) << endl;
    return 0;
}