#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define ll long long

ll M[3005];
ll ans[3005];

struct task
{
    ll start;
    ll end;
    ll unit;
    ll bonus;
};

bool sort_by_start(task a, task b)
{
    return a.start < b.start;
}

struct sort_by_end
{
    bool operator()(task a, task b) const
    {
        return a.end > b.end;
    }
};

bool sort_by_bonus(task a, task b)
{
    if (a.bonus == b.bonus)
    {
        return a.start < b.start;
    }
    return a.bonus > b.bonus;
}

vector<task> T;

ll max_unit(int a)
{
    ll output = 0;
    vector<task> v;
    priority_queue<task, vector<task>, sort_by_end> pq;
    for (ll i = 0; i <= a; i++)
    {
        v.push_back(T[i]);
    }
    sort(v.begin(), v.end(), sort_by_start);
    unsigned int n = 0;
    ll next_start = v[0].start;
    while (!pq.empty() || n < v.size())
    {
        ll cur = v[n].start;

        ll interval;
        if (n == v.size())
        {
            while (!pq.empty())
            {
                interval = min(pq.top().end - next_start + 1,pq.top().unit);
                if (pq.top().unit == interval)
                {
                    output += pq.top().unit;
                    next_start += pq.top().unit;
                }
                else
                {
                    output += interval;
                    next_start += interval;
                }
                pq.pop();
            }
        }
        else
        {
            while (pq.empty() || (n < v.size() && cur == v[n].start && next_start >= v[n].start))
            {
                pq.push(v[n]);
                n++;
            }
            if (!pq.empty())
            {
                interval = min(pq.top().end - next_start + 1, pq.top().unit);
                // interval = min(End - next_start + 1,Top.unit);
                if (pq.top().unit == interval)
                {
                    output += pq.top().unit;
                    next_start += pq.top().unit;
                    pq.pop();
                }
                else
                {
                    output += interval;
                    next_start += interval;
                    task temp = pq.top();
                    temp.unit -= interval;
                    pq.pop();
                    pq.push(temp);
                }
                // if(pq.empty()){
                // next_start +=v[n].start;
                next_start += interval;
                // }
            }
        }
        while (!pq.empty() && pq.top().end < next_start)
        {
            pq.pop();
        }
    }
    return output;
}

ll max_unit_m(int a)
{
    ll output = 0;
    vector<task> v;
    priority_queue<task, vector<task>, sort_by_end> pq;
    for (ll i = 0; i <= a; i++)
    {
        v.push_back(T[i]);
    }
    sort(v.begin(), v.end(), sort_by_start);

    ll next_start = v[0].start;
    ll n = 0;
    ll size = v.size();
    ll End = 0;
    while (!pq.empty() || n < size)
    {
        ll cur = v[n].start;
        while (pq.empty() || (n < size && cur == v[n].start && next_start >= cur))
        {
            pq.push(v[n]);
            n++;
        }
        ll interval;
        task Top = pq.top();
        pq.pop();
        next_start = max(Top.start, next_start);

        if (n < size)
            End = min(Top.end, v[n].start - 1);
        else
            End = Top.end;

        interval = min(End - next_start + 1, Top.unit);

        if (Top.unit > interval)
        {
            Top.unit -= interval;
            pq.push(Top);
        }
        next_start += interval;
        output += interval;
        while (!pq.empty() && pq.top().end < next_start)
        {
            pq.pop();
        }
    }
    return output;
}

int main()
{
    int N;
    ll s, e, x, p;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> s >> e >> x >> p;
        task temp;
        temp.start = s;
        temp.end = e;
        temp.unit = x;
        temp.bonus = p;
        T.push_back(temp);
    }
    sort(T.begin(), T.end(), sort_by_bonus);

    for (int i = 0; i < N; i++)
    {
        M[i] = max_unit(i);
    }
    ans[0] = M[0] * T[0].bonus;
    for (int i = 1; i < N; i++)
    {
        ans[i] = ans[i - 1] + (M[i] - M[i - 1]) * T[i].bonus;
    }
    cout << ans[N - 1] << endl;
    return 0;
}