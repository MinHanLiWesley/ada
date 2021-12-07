#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define CRASH -9223372036854775807
/*


step 1 dq[i][j][0] = max(dq[i-1][j][s-1],dq[i][j-1][s-1])+map[i][j]
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
    cin >> T;

    while (T--)
    {
        // getline(cin, buffer);
        // getline(cin, buffer);
        // input
        int n, m, s;
        cin >> n >> m >> s;

        vector<ll> dq(n * m * s, 0);
        vector<ll> map(n * m, 0);
        int i = 0, j = 0, k = 0;
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
        i = 0, j = 0, k = 0;
        while (i < n)
        {
            j = 0;
            while (j < m)
            {
                ll Udq = getdq(dq, n, m, s, i - 1, j, s - 1);
                ll Ldq = getdq(dq, n, m, s, i, j - 1, s - 1);
                ll num = getmap(map, n, m, i, j);
                // set dp value in dq[s = 0]
                ll dp_val = ((max(Udq, Ldq) == CRASH || num == CRASH) ? CRASH : (max(Udq, Ldq) + num));
                setdq(dq, n, m, s, i, j, 0, dp_val);
                k = 1;
                //step 2
                while (k < s)
                {
                    //upper past (k-1)
                    ll UPdq = getdq(dq, n, m, s, i - 1, j, k - 1);
                    // left past (k-1)
                    ll LPdq = getdq(dq, n, m, s, i, j - 1, k - 1);
                    // curr dp[i][j] == dq[i][j][0]
                    ll currdp = getdq(dq, n, m, s, i, j, k - 1);
                    setdq(dq, n, m, s, i, j, k, max({UPdq, LPdq, currdp}));
                    k++;
                }
                j++;
            }
            i++;
        }
        ll pathsum = getdq(dq, n, m, s, n - 1, m - 1, 0);

        if (pathsum != CRASH)
        {
            cout << "Passable" << endl;
            cout << pathsum << endl;
            deque<pair<int, int>> res;
            i = n - 1;
            j = m - 1;
            k = s - 1;
            int bound_x = i;
            int bound_y = i;
            bool found = 1;
            // ll dp_past = pathsum - getmap(map, n, m, i, j);
            // res.push_front({i + 1, j + 1});
            // while (i > 0 || j > 0)
            // {
            //     if (i < 0 || j < 0)
            //         system("pause");
            //     found = 0;

            //     for (ll x = 0; x <= s; x++)
            //     {
            //         if (found)
            //             break;
            //         for (ll y = 0; y <= s - x; y++)
            //         {
            //             if (found)
            //                 break;
            //             if (x == 0 && y == 0)
            //                 continue;
            //             if (getdq(dq, n, m, s, i - x, j - y, 0) == dp_past)
            //             {
            //                 i = i - x;
            //                 j = j - y;
            //                 res.push_front({i + 1, j + 1});
            //                 dp_past -= getmap(map, n, m, i, j);
            //                 found = 1;
            //             }
            //         }
            //     }
            // }

            // if (res.front().first != 1 || res.front().second != 1)
            //     res.push_front({1, 1});
            while (i >= 0 && j >= 0)
            {
                found = getdq(dq, n, m, s, i, j, k) == getdq(dq, n, m, s, i, j, 0) ? 1 : 0;
                if (found)
                {
                    k = s - 1;
                    // store pt
                    res.push_front({i + 1, j + 1});
                    // 看上方跟左方的k-1
                    (getdq(dq, n, m, s, i - 1, j, k) >= getdq(dq, n, m, s, i, j - 1, k)) ? i-- : j--;
                }
                else
                {
                    k--;
                    (getdq(dq, n, m, s, i - 1, j, k) >= getdq(dq, n, m, s, i, j - 1, k)) ? i-- : j--;
                }
            }
            cout << res.size() << endl;
            for (auto it : res)
                cout << it.first << ' ' << it.second << endl;
        }

        else
            cout << "Impassable" << endl;
    }
}
