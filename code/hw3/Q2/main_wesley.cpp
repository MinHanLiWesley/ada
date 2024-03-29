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
    vector<int> scc_to_vertex;
    vector<int> vertex_to_scc;
    unordered_set<int> src_lst;
    unordered_set<int> sink_lst;
    vector<pair<int, int>> chain;
    vector<int> isolate;
    vector<int> left_src_lst;
    vector<int> left_sink_lst;
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
    // for dag_traverser
    int find_pair;
    DAG(int N_in, int M_in);
    void Tarjan(int u);
    void Condense_dfs(int u);
    void src_sink_pair();
    void connect();
    int DAG_dfs(int src, int u);
    void reset();
};

void DAG::reset()
{

    for (auto it : Raw_adj)
    {
        it.clear();
    }

    Raw_adj.clear();
    disc.clear();
    low.clear();
    inStack.clear();
    while (!st.empty())
    {
        st.pop();
    }
    condense_visited.clear();
    scc_to_vertex.clear();
    vertex_to_scc.clear();
    time = 0;
    scc_id = 0;
    scc_cnt = 0;
    indegree.clear();
    outdegree.clear();
    for (auto it : scc_adj_set)
    {
        it.clear();
    }
    scc_adj_set.clear();
    minimum_edge_cnt = 0;
    isolate.clear();
    src_lst.clear();
    sink_lst.clear();
    find_pair = 0;

    left_src_lst.clear();
    left_sink_lst.clear();
    chain.clear();
    scc_visited.clear();
}

DAG::DAG(int N_in, int M_in)
{
    this->N = N_in;
    this->M = M_in;
    this->Raw_adj.resize(N + 1);
    this->disc.resize(N + 1, NIL);
    this->low.resize(N + 1, 0);
    this->inStack.resize(N + 1, false);
    this->condense_visited.resize(N + 1, false);
    this->vertex_to_scc.resize(N + 1);
    int a, b;
    this->time = 0;
    this->find_pair = 0;
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
    if (scc_cnt == 1)
        minimum_edge_cnt = 0;
    else
    {
        // find src and sink
        F(i, scc_cnt)
        {
            if (!indegree[i] && !outdegree[i])
                isolate.push_back(i);
            else if (outdegree[i] && !indegree[i])
                src_lst.insert(i);
            else if (indegree[i] && !outdegree[i])
                sink_lst.insert(i);
            minimum_edge_cnt = max(src_lst.size(), sink_lst.size()) + isolate.size();
        }
    }
}

void DAG::src_sink_pair()
{
    this->scc_visited.resize(this->scc_cnt, false);
    int src_sz = src_lst.size();
    // 這裡應該處理好srcleft 跟 chain
    for (auto it : src_lst)
    {
        if (this->scc_visited[it] == false)
        {
            find_pair = 0;
            int it_sink = DAG_dfs(it, it);
            // 有找到pair
            if (it_sink != NIL)
            {
                chain.push_back(make_pair(it, it_sink));
            }
            // 殘餘的
            else
            {
                left_src_lst.push_back(it);
            }
        }
    }

    // 假設有 sink left
    if (!sink_lst.empty())
    {
        for (auto it : sink_lst)
        {
            left_sink_lst.push_back(it);
        }
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

int DAG::DAG_dfs(int src, int u)
{

    scc_visited[u] = true;
    for (auto v : scc_adj_set[u])
    {
        if (!scc_visited[v])
        {
            scc_visited[v] = true;
            // find sink => do pair
            if (sink_lst.count(v))
            {
                sink_lst.erase(v);
                return v;
            }
            else
            {
                int v_tmp = DAG_dfs(src, v);
                if (v_tmp != NIL)
                    return v_tmp;
            }
        }
    }
    return NIL;
}

void DAG::Condense_dfs(int u)
{
    condense_visited[u] = true;

    for (auto v : Raw_adj[u])
    {
        int u_sccid = vertex_to_scc[u];
        int v_sccid = vertex_to_scc[v];

        if (u_sccid != v_sccid)
        {
            outdegree[u_sccid] = 1;
            indegree[v_sccid] = 1;
            scc_adj_set[u_sccid].insert(v_sccid);
        }
        if (condense_visited[v] == false)
            Condense_dfs(v);
    }
}

void DAG::connect()
{
    int ans_cnt = 0;
    int dummy = NIL;

    // 先接chain
    int chain_sz = chain.size();
    if (chain_sz)
    {
        dummy = chain.front().first;

        F(i, chain_sz - 1)
        {
            printf("%d %d\n", scc_to_vertex[chain[i].second], scc_to_vertex[chain[i + 1].first]);
            ans_cnt++;
        }
    }

    // chain 跟 孤立 可能沒孤立 or 沒chain
    int isolate_sz = isolate.size();
    // 有孤立 先接孤立
    if (isolate_sz > 0)
    {
        if (dummy == NIL)
        {
            dummy = isolate.front();
        }
        F(i, isolate_sz - 1)
        {
            printf("%d %d\n", scc_to_vertex[isolate[i]], scc_to_vertex[isolate[i + 1]]);
            ans_cnt++;
        }
    }

    // 孤立接完 如果沒有鏈 就自己街自己 不然就跟鏈街
    if (isolate_sz>0)
    {
        // 有鏈
        if (!chain.empty())
        {
            printf("%d %d\n", scc_to_vertex[chain.back().second], scc_to_vertex[isolate.front()]);
            printf("%d %d\n", scc_to_vertex[isolate.back()], scc_to_vertex[chain.front().first]);
            ans_cnt++;
            ans_cnt++;
        }
        // 無鏈
        else
        {
            printf("%d %d\n", scc_to_vertex[isolate.back()], scc_to_vertex[isolate.front()]);
            ans_cnt++;
        }
    }
    else
    {
        // 如果沒有孤立 就鏈自己接
        if (chain_sz > 0)
        {
            ans_cnt++;
            printf("%d %d\n", scc_to_vertex[chain.back().second], scc_to_vertex[chain.front().first]);
        }
    }

    // 處理ˋleft

    int left_sz_min = min(left_sink_lst.size(), left_src_lst.size());
    F(i, left_sz_min)
    {
        ans_cnt++;

        printf("%d %d\n", scc_to_vertex[left_sink_lst[i]], scc_to_vertex[left_src_lst[i]]);
    }

    if (left_sink_lst.size() > left_sz_min)
    {
        for (int i = left_sz_min; i < left_sink_lst.size(); ++i)
        {
            ans_cnt++;
            printf("%d %d\n", scc_to_vertex[left_sink_lst[i]], scc_to_vertex[dummy]);
        }
    }

    if (left_src_lst.size() > left_sz_min)
    {
        for (int i = left_sz_min; i < left_src_lst.size(); ++i)
        {
            ans_cnt++;
            printf("%d %d\n", scc_to_vertex[dummy], scc_to_vertex[left_src_lst[i]]);
        }
    }
}

int main(void)
{
    int T, flag;
    Read(T);
    Read(flag);

    while (T--)
    {
        int N, M;
        Read(N);
        Read(M);
        DAG dag(N, M);
        Write(dag.minimum_edge_cnt);
        putchar('\n');
        if (flag == 1 && dag.minimum_edge_cnt != 0)
        {
            dag.src_sink_pair();
            dag.connect();
        }
        dag.reset();
    }
    return 0;
}