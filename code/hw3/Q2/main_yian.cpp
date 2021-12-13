#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define DEBUG
#define WHITE 0
#define BLACK 1

class vertex_t
{
public:
    vertex_t()
    {
        in_deg = 0;
        out_deg = 0;
        d = 0;
        f = 0;
        color = WHITE;
        root = 0;
    }
    int in_deg, out_deg;
    int d, f;
    int color;
    int root;
};

class graph_t
{
public:
    graph_t(int n)
    {
        N = n;
        num_scc = 0;
        vertex.resize(n + 1);
        adj_list.resize(n + 1);
        adj_list_T.resize(n + 1);
        v_stack.resize(0);
        scc.resize(n + 1);
    }
    int N;
    int num_scc;
    vector<vertex_t> vertex;
    vector<int> scc;
    vector<int> v_stack;
    vector<vector<int> > adj_list;
    vector<vector<int> > adj_list_T;
    graph_t condensation();
    void init_color();
#ifdef DEBUG
    void output_time();
    void output_graph_info();
#endif
};

void graph_t::init_color()
{
    for (int i = 0; i <= N; i++)
    {
        vertex[i].color = WHITE;
    }
}

#ifdef DEBUG
void graph_t::output_time()
{
    cerr << "idx, d, f" << endl;
    for (int i = 1; i <= N; i++)
    {
        cerr << i << ", " << vertex[i].d << ", " << vertex[i].f << endl;
    }
}

void graph_t::output_graph_info()
{
    cerr << "There are " << num_scc << " SCCs in this graph." << endl;
    cerr << "idx, d, f, scc, scc_root" << endl;
    for (int i = 1; i <= N; i++)
    {
        cerr << i << ", " << vertex[i].d << ", " << vertex[i].f << ", " << scc[i] << ", " << vertex[i].root << endl;
    }
}

void output_vertex_type(graph_t &G, vector<pair<int, int> > &wcc_chain, vector<int> &isolate, vector<int> &leftover_sink, vector<int> &leftover_src)
{
    cerr << "wcc_chain.size() = " << wcc_chain.size() << endl;
    for (int i = 0; i < wcc_chain.size(); i++)
    {
        cerr << wcc_chain[i].first << "(" << G.vertex[wcc_chain[i].first].root << "), " << wcc_chain[i].second << "(" << G.vertex[wcc_chain[i].second].root << ")" << endl;
    }
    cerr << "--------------------------------------" << endl;
    cerr << "isolate.size() = " << isolate.size() << endl;
    for (int i = 0; i < isolate.size(); i++)
    {
        cerr << isolate[i] << "(" << G.vertex[isolate[i]].root << ")" << endl;
    }
    cerr << "--------------------------------------" << endl;
    cerr << "leftover_src.size() = " << leftover_src.size() << endl;
    for (int i = 0; i < leftover_src.size(); i++)
    {
        cerr << leftover_src[i] << "(" << G.vertex[leftover_src[i]].root << ")" << endl;
    }
    cerr << "--------------------------------------" << endl;
    cerr << "leftover_sink.size() = " << leftover_sink.size() << endl;
    for (int i = 0; i < leftover_sink.size(); i++)
    {
        cerr << leftover_sink[i] << "(" << G.vertex[leftover_sink[i]].root << ")" << endl;
    }
    cerr << "--------------------------------------" << endl;
}
#endif

graph_t graph_t::condensation()
{
    graph_t scc_G(num_scc);
    scc_G.num_scc = num_scc;
    for (int u = 1; u <= N; u++)
    {
        scc_G.vertex[scc[u]].root = vertex[u].root;
        for (int i = 0; i < adj_list[u].size(); i++)
        {
            if (scc[u] != scc[adj_list[u][i]])
            {
                scc_G.adj_list[scc[u]].push_back(scc[adj_list[u][i]]);
                scc_G.adj_list_T[scc[adj_list[u][i]]].push_back(scc[u]);
                scc_G.vertex[scc[u]].out_deg++;
                scc_G.vertex[scc[adj_list[u][i]]].in_deg++;
            }
        }
    }
    return scc_G;
}

int T, flag;

void dfs_util_T(graph_t &G, int u, int scc_idx, int root)
{
    G.vertex[u].color = BLACK;
    for (int i = 0; i < G.adj_list_T[u].size(); i++)
    {
        if (G.vertex[G.adj_list_T[u][i]].color == WHITE)
        {
            G.scc[G.adj_list_T[u][i]] = scc_idx;
            G.vertex[G.adj_list_T[u][i]].root = root;
            dfs_util_T(G, G.adj_list_T[u][i], scc_idx, root);
        }
    }
    return;
}

int dfs_T(graph_t &G)
{
    G.init_color();
    int u;
    G.scc.push_back(0);
    while (!G.v_stack.empty())
    {
        if (G.vertex[G.v_stack.back()].color == BLACK)
        {
            G.v_stack.pop_back();
            continue;
        }
        G.num_scc++;
        u = G.v_stack.back();
        G.v_stack.pop_back();
        G.scc[u] = G.num_scc;
        G.vertex[u].root = u;
        dfs_util_T(G, u, G.num_scc, u);
    }
    return 0;
}

int dfs_util(graph_t &G, int u, int time)
{
    G.vertex[u].color = BLACK;
    G.vertex[u].d = time;
    time++;
    for (int i = 0; i < G.adj_list[u].size(); i++)
    {
        if (G.vertex[G.adj_list[u][i]].color == WHITE)
            time = dfs_util(G, G.adj_list[u][i], time);
    }
    G.vertex[u].f = time;
    G.v_stack.push_back(u);
    return ++time;
}

int dfs(graph_t &G)
{
    G.init_color();
    int time = 1;
    for (int i = 1; i <= G.N; i++)
    {
        if (G.vertex[i].color == WHITE)
            time = dfs_util(G, i, time);
    }
    return 0;
}

int dfs_connect(graph_t &G, int u)
{
    int v;
    G.vertex[u].color = BLACK;
    if (G.vertex[u].out_deg == 0)
        return u;
    for (int i = 0; i < G.adj_list[u].size(); i++)
    {
        if (G.vertex[G.adj_list[u][i]].color == WHITE)
        {
            if ((v = dfs_connect(G, G.adj_list[u][i])) != -1)
                return v;
        }
    }
    if (G.vertex[u].out_deg != 0)
        return -1;
    return u;
}

int connect(graph_t &G)
{
    vector<pair<int, int> > wcc_chain(0); // .first (src) .second (sink)
    vector<int> isolate(0);
    vector<int> leftover_sink(0);
    vector<int> leftover_src(0);
    G.init_color();
    for (int i = 1; i <= G.N; i++)
    {
        if (G.vertex[i].in_deg == 0 && G.vertex[i].out_deg == 0) // isolate
        {
            // isolated SCC
            isolate.push_back(i);
            G.vertex[i].color = BLACK;
            continue;
        }
        if (G.vertex[i].in_deg == 0 && G.vertex[i].out_deg != 0) // source
        {
            // there exist a wcc chain
            int src = i;
            int sink = dfs_connect(G, i);
            if (sink == -1 || src == sink)
                // we can't go to the real sink, this source is leftover_src
                leftover_src.push_back(src);
            else
                wcc_chain.push_back(make_pair(src, sink));
        }
    }

    for (int i = 1; i <= G.N; i++)
    {
        if (G.vertex[i].color == WHITE)
        {
            if (G.vertex[i].out_deg == 0 && G.vertex[i].in_deg != 0)
            {
                leftover_sink.push_back(i);
                G.vertex[i].color = BLACK;
            }
        }
    }

#ifdef DEBUG
    output_vertex_type(G, wcc_chain, isolate, leftover_sink, leftover_src);
#endif

    // get start and end vertex
    vector<pair<int, int> > new_edges(0);

    // start connecting edge
    // 3 cases
    int dummy;
    if (wcc_chain.size() != 0 && isolate.size() == 0)
    {
        // Case1 : multiple WCC chain and no isolate SCC
        dummy = wcc_chain[0].first;
        for (int i = 1; i < wcc_chain.size(); i++)
            new_edges.push_back(make_pair(G.vertex[wcc_chain[i - 1].second].root, G.vertex[wcc_chain[i].first].root));
        new_edges.push_back(make_pair(G.vertex[wcc_chain.back().second].root, G.vertex[wcc_chain[0].first].root));
    }
    else if (wcc_chain.size() == 0 && isolate.size() != 0)
    {
        // Case2: no WCC chain and multiple isolate SCC
        dummy = isolate[0];
        for (int i = 1; i < isolate.size(); i++)
            new_edges.push_back(make_pair(G.vertex[isolate[i - 1]].root, G.vertex[isolate[i]].root));
        new_edges.push_back(make_pair(G.vertex[isolate.back()].root, G.vertex[isolate[0]].root));
    }
    else
    {
        // Case3: multiple WCC chain and multiple isolate SCC
        dummy = wcc_chain[0].first;
        // connect WCC chain
        for (int i = 1; i < wcc_chain.size(); i++)
            new_edges.push_back(make_pair(G.vertex[wcc_chain[i - 1].second].root, G.vertex[wcc_chain[i].first].root));
        // connect isolate SCC
        for (int i = 1; i < isolate.size(); i++)
            new_edges.push_back(make_pair(G.vertex[isolate[i - 1]].root, G.vertex[isolate[i]].root));
        // connet isolate SCCs and WCC chain
        new_edges.push_back(make_pair(G.vertex[isolate.back()].root, G.vertex[wcc_chain[0].first].root));
        new_edges.push_back(make_pair(G.vertex[wcc_chain.back().second].root, G.vertex[isolate[0]].root));
    }
    // connect paired leftover src and sink
    int paired_size = leftover_src.size() < leftover_sink.size() ? leftover_src.size() : leftover_sink.size();
    for (int i = 0; i < paired_size; i++)
    {
        new_edges.push_back(make_pair(G.vertex[leftover_sink.back()].root, G.vertex[leftover_src.back()].root));
        leftover_src.pop_back();
        leftover_sink.pop_back();
    }

    while (leftover_src.size() != 0)
    {
        new_edges.push_back(make_pair(G.vertex[dummy].root, G.vertex[leftover_src.back()].root));
        leftover_src.pop_back();
    }
    while (leftover_sink.size() != 0)
    {
        new_edges.push_back(make_pair(G.vertex[leftover_sink.back()].root, G.vertex[dummy].root));
        leftover_sink.pop_back();
    }
    // finish connecting
    cout << new_edges.size() << endl;
    if (flag == 1)
    {
        for (int i = 0; i < new_edges.size(); i++)
        {
            cout << new_edges[i].first << " " << new_edges[i].second << endl;
        }
    }
    return new_edges.size();
}

int solve()
{
    int N, M;
    cin >> N >> M;
    graph_t G(N);
    int u, v;
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        G.vertex[u].out_deg++;
        G.vertex[v].in_deg++;
        G.adj_list[u].push_back(v);
        G.adj_list_T[v].push_back(u);
    }
    dfs(G);
    dfs_T(G);
    if (G.num_scc <= 1)
    {
        cout << "0\n";
        return 0;
    }
#ifdef DEBUG
    G.output_graph_info();
#endif
    graph_t scc_G = G.condensation();
#ifdef DEBUG
    cerr << "Otutput Component Graph" << endl;
    scc_G.output_graph_info();
#endif
    connect(scc_G);
    return 0;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T >> flag;
    for (int i = 0; i < T; i++)
    {
        solve();
    }
    return 0;
}
