#include <bits/stdc++.h>
#include <stdio.h>
#define F(a, b) for (int(a) = 0; (a) < (b); ++(a))
#define Fi(a, x, b) for (int(a) = (x); (a) <= (b); ++(a))
#define NIL -1
typedef long long ll;

using namespace std;

inline void Read(int &x)
{
    x = 0;
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
}

void Write(int x)
{
    if (x >= 10)
        Write(x / 10);
    putchar(x % 10 + '0');
}

class DAG
{
public:
    vector<vector<int>> Raw_adj;
    vector<unordered_set<int>> scc_adj_set;
    vector<vector<int>> scc_adj;
    vector<int> scc_to_vertex;
    vector<int> vertex_to_scc;
    vector<int> src;
    vector<int> sink;
    vector<pair<int, int>> chain;
    vector<int> isolate;
    vector<int> left;
    vector<bool> indegree;         // ssc
    vector<bool> outdegree;        // ssc
    vector<bool> scc_visited;      // ssc
    vector<bool> condense_visited; // condensation
    int N;
    int M;
    int scc_cnt;
    // for tarjan
    vector<int> disc;
    vector<int> low;
    vector<bool> inStack;
    stack<int> st;
    int time;
    int scc_id;
    int minimum_edge_cnt = 0;

    DAG(int N_in, int M_in);
    void Tarjan(int u);
    void Condense_dfs(int u);
    void src_sink_pair();
    void DAG_dfs(int u);
    void reset();
};

DAG::DAG(int N_in, int M_in)
{
    this->N = N_in + 1;
    this->M = M_in;
    this->Raw_adj.resize(N);
    this->disc.resize(N, NIL);
    this->low.resize(N, 0);
    this->inStack.resize(N, false);
    this->condense_visited.resize(N, false);
    this->vertex_to_scc.resize(N);
    int a, b;
    this->time = 0;
    this->scc_id = 0;
    F(i, M)
    {
        Read(a);
        Read(b);
        this->Raw_adj[a].push_back(b);
    }
    Fi(i, 1, N)
    {
        if (disc[i] == NIL)
            this->Tarjan(i);
    }
    // condensation
    this->scc_cnt = scc_id;
    this->indegree.resize(this->scc_cnt, false);
    this->outdegree.resize(this->scc_cnt, false);
    this->scc_adj_set.resize(this->scc_cnt);
    Fi(i, 1, N)
    {
        if (condense_visited[i] == false)
            this->Condense_dfs(i);
    }

    this->scc_adj.resize(this->scc_cnt);
    // find src and sink
    F(i, scc_cnt)
    {
        if (!indegree[i] && !outdegree[i])
            isolate.push_back(i);
        else if (outdegree[i] && !indegree[i])
            src.push_back(i);
        else if (indegree[i] && !outdegree[i])
            sink.push_back(i);
    }
    minimum_edge_cnt = max(src.size(), sink.size());
}

void DAG::src_sink_pair()
{
    this->scc_visited.resize(this->scc_cnt, false);
    F(i, scc_cnt)
    {
        if (this->scc_visited[i] == false)
            DAG_dfs(i);
    }
}
void DAG::Tarjan(int u)
{

    disc[u] = low[u] = ++time;
    st.push(u);
    inStack[u] = true;

    for (auto it = Raw_adj[u].begin(); it != Raw_adj[u].end(); ++it)
    {
        int v = *it;

        if (disc[v] == NIL)
        {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (inStack[v] == true)
            low[u] = min(low[u], disc[v]);
    }

    int w = 0;
    if (low[u] == disc[u])
    {
        while (st.top() != u)
        {
            w = st.top();
            st.pop();
            inStack[w] = false;
            vertex_to_scc[w] = scc_id;
        }
        w = st.top();
        inStack[w] = false;
        st.pop();
        vertex_to_scc[w] = scc_id;
        scc_to_vertex.push_back(w);
        ++scc_id;
    }
}

void DAG::DAG_dfs(int u)
{
    scc_visited[u] = true;

    // for (auto v :)
}

void DAG::Condense_dfs(int u)
{
    scc_visited[u] = true;

    for (auto v : Raw_adj[u])
    {
        int u_sccid = vertex_to_scc[u];
        int v_sccid = vertex_to_scc[v];
        outdegree[u_sccid] = 1;
        indegree[v_sccid] = 1;
        if (u_sccid != v_sccid)
            scc_adj_set[u_sccid].insert(v_sccid);
        if (condense_visited[v] == false)
            Condense_dfs(v);
    }
}
int main(void)
{
    int T, flag;
    Read(T);
    Read(flag);

    while (T--)
    {
        if (!flag)
        {
            int N,M;
            Read(N);
            Read(M);
            DAG dag(N,M);
            Write(dag.minimum_edge_cnt);
            putchar('\n');
        }
    }
    return 0;
}