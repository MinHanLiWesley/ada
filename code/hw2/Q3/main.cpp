#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Task
{
private:
    /* data */
public:
    ll start;
    ll end;
    ll unit;
    ll p;
    bool finish;
    Task(ll b, ll c, ll d, ll e) : start(b), end(c), unit(d), p(e){};
    Task() : start(0), end(0), unit(0), p(0){};
};

struct cmp_start
{
    bool operator()(const Task &a, const Task &b)
    {
        return a.start < b.start;
    }
};

struct cmp_end
{
    bool operator()(const Task &a, const Task &b)
    {
        return a.end > b.end;
    }
};

struct cmp_p
{
    bool operator()(const Task &a, const Task &b)
    {

        return a.p > b.p;
    }
};

ll cal_workload(vector<Task> &raw_arr, ll k)
{
    vector<Task> arr;
    for (ll i = 0; i <= k; i++)
    {
        arr.push_back(raw_arr[i]);
    }
    ll ans = 0;
    // sort start
    sort(arr.begin(), arr.end(), cmp_start());
    // time pointer
    ll currtime = arr[0].start;
    ll n = arr.size();
    // ll currtime = 0;
    ll curridx = 0;
    ll limit = 0;
    ll worktime = 0;
    priority_queue<Task, vector<Task>, cmp_end> pq;
    // finish all tasks
    while (curridx < n || !pq.empty())
    {
        ll start = arr[curridx].start;
        // push tasks that could be done immediately
        while (pq.empty() || (currtime >= start && curridx < n && arr[curridx].start == start))
        {
            // pq.emplace(arr[curridx].idx, arr[curridx].start, arr[curridx].end, arr[curridx].unit, arr[curridx].p);
            pq.push(arr[curridx]);
            curridx++;
        }

        Task urgent = pq.top();
        pq.pop();
        if (urgent.start > currtime)
            currtime = urgent.start;
        limit = urgent.end;
        if (curridx != n)
            limit = min(urgent.end, arr[curridx].start - 1);

        // max time curr task could take
        worktime = limit - currtime + 1;
        // add real worktime
        worktime = min(worktime, urgent.unit);
        ans += worktime;
        // doesn't finish the work
        if (urgent.unit - worktime > 0)
        {
            urgent.unit -= worktime;
            pq.push(urgent);
        }

        // update currtime
        currtime += worktime;
        while (!pq.empty() && pq.top().end < currtime)
            pq.pop();
        // cout << "loop\n";
    }

    return ans;
}

int main()
{
    ll N;
    cin >> N;
    vector<Task> arr(N);

    for (ll i = 0; i < N; i++)
    {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        arr[i].start = a;
        arr[i].end = b;
        arr[i].unit = c;
        arr[i].p = d;
    }
    // sort p
    sort(arr.begin(), arr.end(), cmp_p());
    ll prev_worload = arr[0].unit;
    ll curr_workload = 0;
    ll total_p = arr[0].unit * arr[0].p;
    for (ll i = 1; i < N; i++)
    {
        curr_workload = cal_workload(arr, i);
        total_p += (curr_workload - prev_worload) * arr[i].p;
        prev_worload = curr_workload;
    }
    cout << total_p << endl;
    return 0;
}