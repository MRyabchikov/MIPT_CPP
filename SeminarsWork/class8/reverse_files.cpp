#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

void reverse_file (const string& filename)
{
    constexpr long long chunk = 128;
    array<char, chunk> lbuf, rbuf;
    fstream lfs{filename, ios_base::binary};
    fstream rfs{filename, ios_base::binary};
    if (!lfs || !rfs)
        throw runtime_error("can't open file " + filename);
    rfs.seekg(0, ios_base::end);
    streampos lpos = lfs.tellg(), rpos = rfs.tellg();
    while (lpos < rpos)
    {
        lpos = lfs.tellg();
        int n = min((rpos - lpos) / 2, chunk);
        rpos -= n;
        rfs.seekg(rpos);
        lfs.read(lbuf.data(), n);
        rfs.read(rbuf.data(), n);
        reverse(lbuf.begin(), lbuf.begin() + n);
        reverse(rbuf.begin(), rbuf.begin() + n);
        lfs.seekp(lpos);
        rfs.seekp(rpos);
        lfs.write(lbuf.data(), n);
        rfs.write(rbuf.data(), n);
    }
}