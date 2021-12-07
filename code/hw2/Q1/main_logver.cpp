#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define CRASH -92233720368547
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


table 是存邊常
*/

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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    // getline(cin, buffer);
    // T = stoi(buffer);
    cin >> T;

    while (T--)
    {
        // getline(cin, buffer);
        // getline(cin, buffer);
        // input
        ll n, m, s, rs, kprime;
        cin >> n >> m >> rs;
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
        s = rs;
        // the max length only use for minus
        table.push_front(rs);
        // table.push_front(s);
        ll idx = 0;
        while (s >= 3)
        {
            s = s - s / 3;
            table.push_front(s);
        }
        if (s == 2)
            table.push_front(1), s--;
        if (s == 1)
            table.push_front(0);

        s = table.size() - 1;
        vector<ll> dq(n * m * s, 0);
        vector<ll> map(n * m, 0);
        ll i = 0, j = 0, k = 0;
        string input, delim = " ";
        while (i < n)
        {
            j = 0;
            while (j < m)
            {
                string num;
                cin >> num;
                setmap(map, n, m, i, j, (num == "X" ? CRASH : stoll(num)));
                j++;
            }
            i++;
        }

        // step1
        i = 0, j = 0, kprime = 0;
        while (i < n)
        {
            j = 0;
            while (j < m)
            {
                ll U1dq = getdq(dq, n, m, s, i - 1, j, s - 1);
                ll U2dq = getdq(dq, n, m, s, i - (table[s])/3, j, s - 1);
                ll L1dq = getdq(dq, n, m, s, i, j - 1, s - 1);
                ll L2dq = getdq(dq, n, m, s, i, j - (table[s])/3, s - 1);
                ll num = getmap(map, n, m, i, j);
                // set dp value in dq[s = 0]
                ll dp_val = (max({U1dq, U2dq, L1dq, L2dq}) == CRASH || num == CRASH) ? CRASH : max({U1dq, U2dq, L1dq, L2dq}) + num;
                setdq(dq, n, m, s, i, j, 0, dp_val);
                kprime = 1;
                //step 2
                while (kprime < s)
                {
                    //upper past (k-1)
                    ll UPdq = getdq(dq, n, m, s, i - table[kprime]/3, j, kprime - 1);
                    // left past (k-1)
                    ll LPdq = getdq(dq, n, m, s, i, j - table[kprime]/3, kprime - 1);
                    // curr dp[i][j] == dq[i][j][0]
                    ll currdp = getdq(dq, n, m, s, i, j, kprime - 1);
                    setdq(dq, n, m, s, i, j, kprime, max({UPdq, LPdq, currdp}));
                    kprime++;
                }
                j++;
            }
            i++;
        }
        ll pathsum = getdq(dq, n, m, s, n - 1, m - 1, 0);
        // cout << pathsum << endl;
        if (pathsum != CRASH)
        {
            cout << "Passable" << endl;
            cout << pathsum << endl;
            deque<pair<int, int>> res;
            i = n - 1;
            j = m - 1;
            kprime = s - 1;
            bool found = 1;
            ll dp_past = pathsum - getmap(map, n, m, i, j);
            res.push_front({i + 1, j + 1});
            while (i > 0 || j > 0)
            {
                found = 0;

                for (ll x = 0; x <= s; x++)
                {
                    if (found)
                        break;
                    for (ll y = 0; y <= s - x; y++)
                    {
                        if (found)
                            break;
                        if (x == 0 && y == 0)
                            continue;
                        if (getdq(dq, n, m, s, i - x, j - y, 0) == dp_past)
                        {
                            res.push_front({i - x + 1, j - y + 1});
                            dp_past -= getmap(map, n, m, i - x, j - y);
                            found = 1;
                            i = i - x;
                            j = j - y;
                        }
                    }
                }
                if (!found)
                    system("pause");
            }
            if (res.front().first != 1 || res.front().second != 1)
                res.push_front({1, 1});
            // while (i >= 0 && j >= 0)
            // {
            //     found = getdq(dq, n, m, s, i, j, kprime) == getdq(dq, n, m, s, i, j, 0) ? 1 : 0;
            //     if (found)
            //     {
            //         //renew k
            //         kprime = s - 1;
            //         // store pt
            //         res.push_front({i + 1, j + 1});
            //     }
            //     else
            //     //縮小範圍
            //     {
            //         kprime--;
            //     }
            //     // 看上方i-1 i- table[k]跟左方j-1 j-table[k]
            //     ll U1dq = getdq(dq, n, m, s, i - 1, j, kprime);
            //     ll U2dq = getdq(dq, n, m, s, i - (table[kprime + 1] - table[kprime]), j, kprime);
            //     ll L1dq = getdq(dq, n, m, s, i, j - 1, kprime);
            //     ll L2dq = getdq(dq, n, m, s, i, j - (table[kprime + 1] - table[kprime]), kprime);
            //     ll maxdp = max({U1dq, U2dq, L1dq, L2dq});
            //     if (maxdp == U2dq)
            //         i = i - (table[kprime + 1] - table[kprime]);

            //     else if (maxdp == U1dq)
            //         i--;
            //     else if (maxdp == L2dq)
            //         j = j - (table[kprime + 1] - table[kprime]);
            //     else
            //         j--;
            // }
            cout << res.size() << endl;
            for (auto it : res)
                cout << it.first << ' ' << it.second << endl;
        }

        else
            cout << "Impassable" << endl;
    }
}
