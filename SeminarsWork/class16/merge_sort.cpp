#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

template <typename T> ostream& operator<< (ostream& fout, vector<T>& v)
{
    for (auto curr : v)
        fout << curr << " ";
    return fout;
}

void merge (int* begin, int* middle, int* end, int* buf)
{
    int *p1 = begin, *p2 = middle;
    while (p1 < middle && p2 < end)
    {
        if (*p1 <= *p2)
            *buf = *p1++;
        else
            *buf = *p2++;
        buf++;
    }
    while (p1 < middle)
        *buf++ = *p1++;
    while (p2 < end)
        *buf++ = *p2++;
    for (int* p = begin; p != end; p++)
        *p = *(buf - (end - begin) + (p - begin));
}

void merge_sort_impl (int* begin, int* end, int* buf)
{
    if (begin == end - 1)
        return;
    int* middle = begin + (end - begin) / 2;
    merge_sort_impl(begin, middle, buf);
    merge_sort_impl(middle, end, buf);
    merge(begin, middle, end, buf);
}

void merge_sort (int* begin, int* end)
{
    if (begin == end)
        return;
    if (begin == nullptr || end == nullptr)
        throw invalid_argument("Null pointer");
    if (end < begin)
        throw invalid_argument("Bad order");
    int* buf = new int[end - begin];
    merge_sort_impl(begin, end, buf);
    delete[] buf;
}

int main (void)
{
    vector<int> src{1, 3, 2, 5, 4, 6, 10, 9};
    vector<int> v1{src};
    vector<int> v2{src};
    sort(v1.begin(), v1.end());
    merge_sort(&v2[0], &v2[0] + v2.size());
    cout << v1 << endl << v2 << endl << src;
    return 0;
}