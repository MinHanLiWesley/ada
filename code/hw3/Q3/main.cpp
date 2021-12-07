#include <bits/stdc++.h>
#include <stdio.h>
#define F(a, b) for (int(a) = 0; (a) < (b); ++(a))
#define Fi(a, x, b) for (int(a) = (x); (a) <= (b); ++(a))
typedef long long ll;

using namespace std;

class Node
{
public:
    int neighbor;
    int E_idx;
    ll w; //weight
    ll cost;
    Node(){};
    Node(int in_neigh, int in_idx, ll in_w) : neighbor(in_neigh),
                                              E_idx(in_idx),
                                              w(in_w),
                                              cost(in_w){};
    Node(int in_neigh, int in_idx, ll in_w, ll in_cost) : neighbor(in_neigh),
                                                          E_idx(in_idx),
                                                          w(in_w),
                                                          cost(in_cost){};

    ~Node(){};
};

class Distance
{
public:
    ll cost;
    ll w;
    Distance(){};
    Distance(ll i_cost, ll i_w) : cost(i_cost), w(i_w){};
    ~Distance(){};
};

inline void Read(int &x)
{
    x = 0;
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
}

void Write(ll x)
{
    if (x >= 10)
        Write(x / 10);
    putchar(x % 10 + '0');
}
struct mycmpSPT
{
    bool operator()(Node const &p1, Node const &p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        if (p1.cost == p2.cost)
            return p1.w > p2.w;
        else
            return p1.cost > p2.cost;
    }
};

struct mycmpMST
{
    bool operator()(Node const &p1, Node const &p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1.w > p2.w;
    }
};
int main()
{
    int N, M;
    Read(N);
    Read(M);

    vector<Node> adj_list[N + 1];

    Fi(i, 1, M)
    {
        int a, b, c;
        Read(a), Read(b), Read(c);
        adj_list[a].push_back(Node(b, i, c));
        adj_list[b].push_back(Node(a, i, c));
    }

    // spt dijkistra
    int start = 1;

    priority_queue<Node, vector<Node>, mycmpSPT> pq_spt;

    bool visited[N + 1] = {0};
    vector<Distance> distance(N + 1, Distance(INT64_MAX, INT64_MAX));
    distance[1].cost = 0;
    distance[1].w = 0;
    visited[1] = 1;
    bool final_edge[M + 1] = {0};
    ll spt_weight = 0;
    // start from 1
    int sz = adj_list[1].size();
    int cnt = 1;
    F(i, sz)
    {
        distance[adj_list[1][i].neighbor].cost = adj_list[1][i].cost;
        distance[adj_list[1][i].neighbor].w = adj_list[1][i].w;
        pq_spt.push(adj_list[1][i]);
    }

    while (cnt < N)
    {
        Node u = pq_spt.top();
        pq_spt.pop();
        // if (visited[u.neighbor])
        //     continue;
        visited[u.neighbor] = 1;
        final_edge[u.E_idx] = 1;
        spt_weight += u.w;
        sz = adj_list[u.neighbor].size();
        F(i, sz)
        {
            if (!visited[adj_list[u.neighbor][i].neighbor])
            {
                if (distance[adj_list[u.neighbor][i].neighbor].cost > distance[u.neighbor].cost + adj_list[u.neighbor][i].cost)
                {
                    distance[adj_list[u.neighbor][i].neighbor].cost = distance[u.neighbor].cost + adj_list[u.neighbor][i].cost;
                    distance[adj_list[u.neighbor][i].neighbor].w = adj_list[u.neighbor][i].w;
                    Node tmp = adj_list[u.neighbor][i];
                    tmp.cost = distance[adj_list[u.neighbor][i].neighbor].cost;
                    pq_spt.push(tmp);
                }
                else if (distance[adj_list[u.neighbor][i].neighbor].cost == (distance[u.neighbor].cost + adj_list[u.neighbor][i].cost) &&
                         distance[adj_list[u.neighbor][i].neighbor].w > adj_list[u.neighbor][i].w)
                {
                    distance[adj_list[u.neighbor][i].neighbor].w = adj_list[u.neighbor][i].w;
                    Node tmp = adj_list[u.neighbor][i];
                    tmp.cost = distance[adj_list[u.neighbor][i].neighbor].cost;
                    pq_spt.push(tmp);
                }
            }
        }

        while (!pq_spt.empty() && visited[pq_spt.top().neighbor])
        {
            pq_spt.pop();
        }
        cnt++;
    }
    distance.clear();

    // prims mst

    priority_queue<Node, vector<Node>, mycmpMST> pq_mst;
    vector<ll> distance_mst(N + 1, INT64_MAX);
    memset(visited, 0, N + 1);
    visited[1]=1;
    ll mst_weight = 0;
    cnt = 1;
    sz = adj_list[1].size();
    F(i, sz)
    {
        distance_mst[adj_list[1][i].neighbor] = adj_list[1][i].w;

        pq_mst.push(adj_list[1][i]);
    }

    while (!pq_mst.empty())
    {
        Node u = pq_mst.top();
        pq_mst.pop();

        if (visited[u.neighbor])
            continue;
        
        visited[u.neighbor] = 1;
        mst_weight += u.w;
        sz = adj_list[u.neighbor].size();
        F(i, sz)
        {
            if (!visited[adj_list[u.neighbor][i].neighbor])
            {
                if (distance_mst[adj_list[u.neighbor][i].neighbor] > adj_list[u.neighbor][i].w)
                {
                    distance_mst[adj_list[u.neighbor][i].neighbor] = adj_list[u.neighbor][i].w;
                    Node tmp = adj_list[u.neighbor][i];
                    tmp.w = distance_mst[adj_list[u.neighbor][i].neighbor];
                    pq_mst.push(tmp);
                }
            }
        }

        // while (!pq_mst.empty() && visited[pq_mst.top().neighbor])
        // {
        //     pq_mst.pop();
        // }
        // cnt++;
    }

    if (mst_weight == spt_weight)
    {
        putchar('Y');
        putchar('e');
        putchar('s');
        putchar('\n');
        Fi(i, 1, M)
        {
            if (final_edge[i])
                Write(i),putchar(' ');
                // printf("%d ", i);
        }
    }
    else
    {
                putchar('N');
        putchar('o');
        putchar('\n');
        // printf("No\n");
    }

    return 0;
}