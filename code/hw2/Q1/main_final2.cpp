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
        int n, m, s, rs;
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
        // table.push_front(s);
        while (s > 0)
        {
            if (s == 2)
                table.push_front(1), s--;
            else if (s == 1)
                table.push_front(1), s--;
            else
            {

                table.push_front(s / 2);
                s = s - s / 2;
            }
        }
        s = table.size();
        vector<ll> dq(n * m * s, 0);
        vector<ll> map(n * m, 0);
        int i = 0, j = 0, k = 0;
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
        while (i < n)
        {
            j = 0;
            while (j < m)
            {
                ll U1dq = getdq(dq, n, m, s, i - 1, j, s - 1);
                ll U2dq = getdq(dq, n, m, s, i - table[s - 1], j, s - 1);
                ll U3dq = getdq(dq, n, m, s, i - table[s - 1] / 2 == 0 ? 1 : table[s - 1] / 2, j, s - 1);
                ll L1dq = getdq(dq, n, m, s, i, j - 1, s - 1);
                ll L2dq = getdq(dq, n, m, s, i, j - table[s - 1], s - 1);
                ll L3dq = getdq(dq, n, m, s, i, j - table[s - 1] / 2 == 0 ? 1 : table[s - 1] / 2, s - 1);
                if (table[s-1])
                ll Diagdq = getdq(dq, n, m, s, i - table[s - 1] / 2 == 0 ? 1 : table[s - 1] / 2,
                                  j - table[s - 1] / 2 == 0 ? 1 : table[s - 1] / 2, s - 1);
                ll num = getmap(map, n, m, i, j);
                // set dp value in dq[s = 0]
                ll dp_val = (max({U1dq, U2dq, U3dq, L1dq, L2dq, L3dq, Diagdq}) == CRASH || num == CRASH) ? CRASH : max({U1dq, U2dq, L1dq, L2dq}) + num;
                setdq(dq, n, m, s, i, j, 0, dp_val);
                k = 1;
                //step 2
                while (k < s)
                {
                    //upper past (k-1)
                    ll UPdq = getdq(dq, n, m, s, i - table[k - 1], j, k - 1);
                    ll UP2dq = getdq(dq, n, m, s, i - table[k - 1] / 2 == 0 ? 1 : table[k - 1] / 2, j, k - 1);
                    // left past (k-1)
                    ll LPdq = getdq(dq, n, m, s, i, j - table[k - 1], k - 1);
                    ll LP2dq = getdq(dq, n, m, s, i, j - table[k - 1] / 2 == 0 ? 1 : table[k - 1] / 2, k - 1);
                    ll DiagPdq = getdq(dq, n, m, s, i - table[k - 1] / 2 == 0 ? 1 : table[k - 1] / 2, j - table[k - 1] / 2 == 0 ? 1 : table[k - 1] / 2, k - 1);
                    // curr dp[i][j] == dq[i][j][0]
                    ll currdp = getdq(dq, n, m, s, i, j, k - 1);
                    setdq(dq, n, m, s, i, j, k, max({UPdq, UP2dq, LPdq, LP2dq, DiagPdq, currdp}));
                    k++;
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
            k = s - 1;
            bool found = 1;
            while (i >= 0 && j >= 0)
            {
                found = getdq(dq, n, m, s, i, j, k) == getdq(dq, n, m, s, i, j, 0) ? 1 : 0;
                if (found)
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

                ll U1dq = getdq(dq, n, m, s, i - 1, j, k);
                ll U2dq = getdq(dq, n, m, s, i - table[k], j, k);
                ll U3dq = getdq(dq, n, m, s, i - (table[k] / 2 == 0 ? 1 : table[k] / 2), j, k);
                ll L1dq = getdq(dq, n, m, s, i, j - 1, k);
                ll L2dq = getdq(dq, n, m, s, i, j - table[k], k);
                ll L3dq = getdq(dq, n, m, s, i, j - (table[k] / 2 == 0 ? 1 : table[k] / 2), k);
                ll Diagdq = getdq(dq, n, m, s, i - (table[k] / 2 == 0 ? 1 : table[k] / 2), j - table[k] / 2 == 0 ? 1 : table[k] / 2, k);
                ll maxdp = max({U1dq, U2dq, U3dq, L1dq, L2dq, L3dq, Diagdq});
                if (maxdp == Diagdq)
                    j = j - (table[k] / 2 == 0 ? 1 : table[k] / 2), i = i - (table[k] / 2 == 0 ? 1 : table[k] / 2);
                else if (maxdp == U2dq)
                    i = i - table[k];
                else if (maxdp == L1dq)
                    j--;
                else if (maxdp == L2dq)
                    j = j - table[k];
                else if (maxdp == U3dq)
                    i = i - table[k] / 2 == 0 ? 1 : table[k] / 2;
                else if (maxdp == L3dq)
                    j = j - table[k] / 2 == 0 ? 1 : table[k] / 2;
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
