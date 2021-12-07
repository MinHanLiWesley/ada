#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    string str = "8246821 -1456456 x";

    string::size_type sz = 0; // alias of size_t

    while (!str.empty())
    {
        if(str[sz] == 'x')
            {
                long long ll = -456456456;
                cout << str.substr(0, sz) << " interpreted as " << ll << '\n';
                sz += 2;
                continue;
            }
        long long ll = std::stoll(str, &sz, 0);
        cout << str.substr(0, sz) << " interpreted as " << ll << '\n';
        str = str.substr(sz);
    }
}