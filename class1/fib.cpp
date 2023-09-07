#include <iostream>
#include <vector>
using namespace std;

int main (void)
{
  int n;
  vector<int> v{1, 1};
  cin >> n;
  for (int i = 2; i <= n; i++)
    v.push_back(v[i - 1] + v[i - 2]);
  cout << v[n];
}