#include <cmath>
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

using pow_func = double (*)(double, int);

void test_pow (double x, double eps, pow_func our_pow)
{
    bool flag = true;  //
    for (int n = -5; n <= 5; n++)
    {
        if (abs(our_pow(x, n) - pow(x, n)) > eps)
        {
            cout << "Test mistake with x = " << x << ", n = " << n << endl;
            flag = false;
        }
    }
    if (flag)
        cout << "Everything is right" << endl;
}

int main (void)
{
    test_pow(5, pow(10, -15), fast_pow);
    test_pow(5, pow(10, -15), slow_pow);
    return 0;
}