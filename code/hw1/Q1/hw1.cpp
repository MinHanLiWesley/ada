#include <iostream>
#include <math.h>
using namespace std;

long long int PowOf2[100010];

int p = 998244353;
void power(long long x, unsigned int y)
{
    long idx = 0; //
    long long  res = 1; // Initialize result
    PowOf2[idx] = res;
    for (idx = 1; idx < y; idx++)
    {
        res = (x * res) % p;
        PowOf2[idx] = res;
    }
}

int flag = 0;

long long int steps(int disk[], long long int n, int src, int dest, int prohibit)
{
    if (n < 0)
        return 0;

    long long int ans = 0;
    // if n is in prohibit peg return -1
    if (disk[n] == prohibit)
    {
        flag = 1;
        return -1;
    }
    // n is in src
    else if (disk[n] == src)
    {
        ans += (PowOf2[n] + steps(disk, n - 1, src, prohibit, dest)%p)%p ;
    }
    else
    {
        return ans += steps(disk, n - 1, prohibit, dest, src)%p;
    }

    if (flag)
        return -1;
    else
        return ans%p;
}

int main()
{
    power(2, 100010);
    // cout << PowOf2[99999];
    long long int n;
    cin >> n;

    int disk[100001];

    int peg_num = 1;

    for (size_t i = 0; i < 3; i++)
    {
        long long int PegCnt = 0;
        cin >> PegCnt;
        long long int disknum = 0;
        while (PegCnt--)
        {
            cin >> disknum;
            disk[disknum - 1] = peg_num;
        }
        peg_num++;
    }

    cout << steps(disk, n - 1, 1, 3, 2) << endl;

    return 0;
}