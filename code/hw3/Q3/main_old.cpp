#include <bits/stdc++.h>
#include <stdio.h>
#define F(a, b) for (int(a) = 0; (a) < (b); ++(a))
#define Fi(a, x, b) for (int(a) = (x); (a) <= (b); ++(a))
typedef long long ll;

using namespace std;

class Node
{
public:
    int V_idx;
    int neighbor;
    int E_idx;
    int w; //weight
    int cost;
    Node(){};
    Node(int in_V_idx, int in_neigh, int in_idx, int in_w) : V_idx(in_V_idx),
                                                             neighbor(in_neigh),
                                                             E_idx(in_idx),
                                                             w(in_w),
                                                             cost(in_w){};
    Node(int in_V_idx, int in_neigh, int in_idx, int in_w, int in_cost) : V_idx(in_V_idx),
                                                                          neighbor(in_neigh),
                                                                          E_idx(in_idx),
                                                                          w(in_w),
                                                                          cost(in_cost){};

    ~Node(){};
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
        adj_list[a].push_back(Node(a, b, i, c));
        adj_list[b].push_back(Node(b, a, i, c));
    }

    // spt dijkistra
    int start = 1;

    priority_queue<Node, vector<Node>, mycmpSPT> pq_spt;

    bool visited[N + 1] = {0};
    vector<int> distance(N + 1, INT32_MAX);
    distance[1] = 0;
    visited[1] = 1;
    bool final_edge[N + 1] = {0};
    int spt_weight = 0;
    // start from 1
    int sz = adj_list[1].size();
    int cnt = 1;
    F(i, sz)
    {
        distance[adj_list[1][i].neighbor] = adj_list[1][i].cost;
        pq_spt.push(adj_list[1][i]);
    }

    while (cnt < N)
    {
        Node u = pq_spt.top();
        pq_spt.pop();
        visited[u.neighbor] = 1;
        final_edge[u.E_idx] = 1;
        spt_weight += u.w;
        sz = adj_list[u.neighbor].size();
        F(i, sz)
        {
            if (!visited[adj_list[u.neighbor][i].neighbor])
            {
                if (distance[adj_list[u.neighbor][i].neighbor] > distance[u.neighbor] + adj_list[u.neighbor][i].cost)
                {
                    distance[adj_list[u.neighbor][i].neighbor] = distance[u.neighbor] + adj_list[u.neighbor][i].cost;

                    Node tmp = adj_list[u.neighbor][i];
                    tmp.cost = distance[adj_list[u.neighbor][i].neighbor];
                    pq_spt.push(tmp);
                }
                else if (distance[adj_list[u.neighbor][i].neighbor] == (distance[u.neighbor] + adj_list[u.neighbor][i].cost))
            }
        }

        while (!pq_spt.empty() && visited[pq_spt.top().neighbor])
        {
            pq_spt.pop();
        }
        cnt++;
    }

    Fi(i, 1, N)
    {
        if (final_edge[i])
            printf("%d ", i);
    }
    printf("\n");

    return 0;
}