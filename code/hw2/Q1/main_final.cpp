#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define CRASH -9223372036854775807
/*

step 1 dp[i][j] = dq[i][j][0] = max(dq[i-1][j][s-1],dq[i][j-1][s-1])+map[i][j]
step 2 for k < s => dq[i][j][k] = max(dq[i-1][j][k-1],dq[i][j-1][k-1],dq[i][j][0])
step 3 暴力回搜

k=0


k=1

...

k = k-1

bottom up往上建 

for m
  for n 
  step1
    for k
    step2


logk作法
找重心 切成三個可以覆蓋k的小腳型
基本上就2/3k

*/
inline void read(ll &x)
{
    x = 0;
    char c = getchar();
    if (c == 'X')
        x = CRASH;
    else
    {
        int p = 0;
        if (c == '-')
        {
            p = 1;
            c = getchar();
        }
        for (c = getchar(); c < '0' || c > '9'; c = getchar())
            ;

        for (; c >= '0' && c <= '9'; c = getchar())
            x = (x << 3) + (x << 1) + c - '0';
        if (p)
            x = -x;
    }
}
char outputbuf[15];

inline void write(ll x)
{
    if (x == 0)
        putchar('0');
    else
    {
        if (x < 0)
            putchar('-'), x = -x;

        int p = 0;
        while (x)
        {
            outputbuf[p++] = x % 10;
            x /= 10;
        }

        for (int i = p - 1; i >= 0; i--)
            putchar('0' + outputbuf[i]);
    }
}

ll getdq(vector<ll> &vec, int n, int m, int s, int i, int j, int k)
{
    if (0 <= i && i < n && 0 <= j && j < m && 0 <= k && k < s)
        return vec[i * m * s + j * s + k];
    else
        return CRASH;
}
void setdq(vector<ll> &vec, int n, int m, int s, int i, int j, int k, ll num)
{
    if (i == 0 && j == 0)
        vec[(i * m + j) * s + k] = 0;
    else
        vec[(i * m + j) * s + k] = num;
}

ll getmap(vector<ll> &vec, int n, int m, int i, int j)
{
    return vec[i * m + j];
}

void setmap(vector<ll> &vec, int n, int m, int i, int j, ll num)
{
    vec[i * m + j] = num;
}
int main()
{
    string buffer;
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    ll T;
    // getline(cin, buffer);
    // T = stoi(buffer);
    // cin >> T;
    read(T);
    // scanf("%d ", &T);
    // getchar();
    while (T--)
    {
        // getline(cin, buffer);
        // getline(cin, buffer);
        // input
        ll n, m, s, rs;
        read(n);
        read(m);
        read(rs);
        // cin >> n >> m >> rs;
        // scanf("%d %d %d ", &n, &m, &rs);
        // getline(cin, buffer);
        // istringstream ss(buffer);
        // istream_iterator<string> begin(ss), end;
        // vector<string> words(begin, end);
        // n = stoi(words[0]);
        // m = stoi(words[1]);
        // rs = stoi(words[2]);
        // rs--;
        //logk 建表
        ll count = 1;

        deque<ll> table;
        table.push_front(1);
        s = rs;
        // table.push_front(s);
        while (s > 1)
        {
            if (s == 2)
                table.push_front(1), s--;
            else
            {

                table.push_front(s / 3);
                s = s - s / 3;
            }
        }
        s = table.size();
        vector<ll> dq(n * m * s);
        // dq.resize(n * m * s);
        vector<ll> map(n * m);
        // map.resize(n * m);
        int i = 0, j = 0, k = 0;
        // string num;
        char num[20]{0};
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                read(map[i * m + j]);
                // sz;
                // read(sz);
                // scanf("%s%n ", num, &sz);
                // map[i * m + j] = num[0] == 'X' ? CRASH : atoll(num);
                // memset(num, 0, sz);
            }
        }
        // char c;
        // c = getchar();

        // while (i < n)
        // {
        //     getline(cin, input);
        //     size_t pos = 0;
        //     string token;
        //     j = 0;
        //     while (j < m)
        //     {
        //         pos = input.find(delim);
        //         token = input.substr(0, pos);
        //         ll num = (token == "X") ? CRASH : stoll(token);
        //         setmap(map, n, m, i, j, num);
        //         j++;
        //         input.erase(0, pos + delim.length());
        //     }
        //     i++;
        // }
        // step1
        i = 0, j = 0, k = 0;

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                ll U1dq = getdq(dq, n, m, s, i - 1, j, s - 1);
                ll U2dq = getdq(dq, n, m, s, i - table[s - 1], j, s - 1);
                ll L1dq = getdq(dq, n, m, s, i, j - 1, s - 1);
                ll L2dq = getdq(dq, n, m, s, i, j - table[s - 1], s - 1);
                ll maxdq = max({U1dq, U2dq, L1dq, L2dq});
                ll num = getmap(map, n, m, i, j);
                // set dp value in dq[s = 0]
                ll dp_val = (maxdq == CRASH || num == CRASH) ? CRASH : maxdq + num;
                setdq(dq, n, m, s, i, j, 0, dp_val);
                for (int k = 1; k < s; k++)
                {
                    ll UPdq = getdq(dq, n, m, s, i - table[k - 1], j, k - 1);
                    // left past (k-1)
                    ll LPdq = getdq(dq, n, m, s, i, j - table[k - 1], k - 1);
                    // curr dp[i][j] == dq[i][j][0]
                    ll currdp = getdq(dq, n, m, s, i, j, k - 1);
                    setdq(dq, n, m, s, i, j, k, max({UPdq, LPdq, currdp}));
                }
            }
        }

        // while (i < n)
        // {
        //     j = 0;
        //     while (j < m)
        //     {

        //         //step 2
        //         while (k < s)
        //         {
        //             //upper past (k-1)

        //             k++;
        //         }
        //         j++;
        //     }
        //     i++;
        // }
        ll pathsum = getdq(dq, n, m, s, n - 1, m - 1, 0);
        // cout << pathsum << endl;
        if (pathsum != CRASH)
        {
            cout << "Passable" << endl;
            cout << pathsum << endl;
            deque<pair<int, int>> res;
            i = n - 1;
            j = m - 1;
            k = s - 1;
            bool found = 1;
            while (i >= 0 && j >= 0)
            {
                if (getdq(dq, n, m, s, i, j, k) == getdq(dq, n, m, s, i, j, 0))
                {
                    //renew k
                    k = s - 1;
                    // store pt
                    res.push_front({i + 1, j + 1});
                }
                else
                //縮小範圍
                {
                    k--;
                }
                // 看上方i-1 i- table[k]跟左方j-1 j-table[k]

                ll maxdp = max({getdq(dq, n, m, s, i - 1, j, k), getdq(dq, n, m, s, i - table[k], j, k), getdq(dq, n, m, s, i, j - 1, k), getdq(dq, n, m, s, i, j - table[k], k)});
                // ll U1dq = getdq(dq, n, m, s, i - 1, j, k);
                // ll U2dq = getdq(dq, n, m, s, i - table[k], j, k);
                // ll L1dq = getdq(dq, n, m, s, i, j - 1, k);
                // ll L2dq = getdq(dq, n, m, s, i, j - table[k], k);
                // ll maxdp = max({U1dq, U2dq, L1dq, L2dq});
                if (maxdp == getdq(dq, n, m, s, i, j - table[k], k))
                    j = j - table[k];
                else if (maxdp == getdq(dq, n, m, s, i - table[k], j, k))
                    i = i - table[k];
                else if (maxdp == getdq(dq, n, m, s, i, j - 1, k))
                    j--;
                else
                    i--;
            }
            cout << res.size() << endl;
            for (auto it : res)
                cout << it.first << ' ' << it.second << endl;
        }

        else
            cout << "Impassable" << endl;
    }
}
