#include <bits/stdc++.h>
#define FOR(x, n) for (int x = 0; x < n; ++x)

// 124建
using namespace std;

// typedef priority_queue<int, vector<int>, greater<int>> PQ;

// void DFS_visit(vector<vector<int>> &adj_list, vector<bool> &dfs_wh, int start)
// {
//     dfs_wh[start] = 1;
//     cout << start << " ";
//     // sort(adj_list[start].begin(), adj_list[start].end());
//     FOR(i, adj_list[start].size())
//     {
//         if (dfs_wh[adj_list[start][i]] == 0)
//             DFS_visit(adj_list, dfs_wh, adj_list[start][i]);
//     }
// }

// void DFS(vector<vector<int>> &adj_list, vector<bool> &dfs_wh)
// {
//     vector<bool>::iterator dfs_it = dfs_wh.begin();
//     while ((dfs_it = find(dfs_it, dfs_wh.end(), 0)) != dfs_wh.end())
//     {
//         DFS_visit(adj_list, dfs_wh, dfs_it - dfs_wh.begin());
//     }
// }
inline void read(int &x)
{
    x = 0;
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
}
char outputbuf[15];

inline void write(unsigned int x)
{
    if (x == 0)
        putchar('0');
    else
    {
        int p = 0;
        while (x)
        {
            outputbuf[p++] = x % 10;
            x /= 10;
        }

        for (int i = p - 1; i >= 0; i--)
            putchar('0' + outputbuf[i]);
    }
}

int main()
{
    // cin.sync_with_stdio(false), cin.tie(NULL);

    int N, M;
    read(N);
    read(M);
    // cin >> N >> M;

    vector<bool> dfs_wh(N + 1, 0);
    dfs_wh[0] = 1;
    vector<bool> bfs_wh(N + 1, 0);
    bfs_wh[0] = 1;
    register unsigned i;

    vector<vector<unsigned>> adj_list(N + 1, vector<unsigned>());

    // input adj_list
    for (i = 0; i < M; i++)
    {
        int a, b;
        read(a);
        read(b);
        // cin >> a >> b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
        // a < b ? adj_list[a].push_back(b) : adj_list[b].push_back(a);
    }

    // sort vec
    vector<unsigned> Size_adj(N + 1, 0);
    for (i = 1; i <= N; i++)
    {
        sort(adj_list[i].begin(), adj_list[i].end());
        Size_adj[i] = adj_list[i].size();
    }

    // DFS
    vector<size_t> dfs_pt(N + 1, 0);
    deque<unsigned> dfs_dq;

    vector<bool>::iterator dfs_it = dfs_wh.begin();
    // DFS(adj_list, dfs_wh);
    register unsigned start;
    while ((dfs_it = find(dfs_it, dfs_wh.end(), 0)) != dfs_wh.end())
    {
        start = dfs_it - dfs_wh.begin();
        dfs_dq.push_back(start);
        dfs_wh[start] = 1;
        write(start);
        putchar(' ');
        // cout << start << " ";
        // push elements into deque
        while (1)
        {
            // no edge in single vertice
            if (dfs_pt[start] == Size_adj[start])
            {
                dfs_dq.pop_back();
                if (dfs_dq.empty())
                    break;
                else
                {
                    start = dfs_dq.back();
                }
            }
            else
            {
                // not seen
                if (dfs_wh[adj_list[start][dfs_pt[start]]] == 0)
                {
                    int found = adj_list[start][dfs_pt[start]];
                    ++dfs_pt[start];
                    start = found;
                    write(start);
                    putchar(' ');
                    // cout << start << " ";
                    dfs_dq.push_back(start);
                    dfs_wh[start] = 1;
                }
                else
                {
                    ++dfs_pt[start];
                }
            }
        }
    }
    putchar('\n');
    // cout << endl;
    // BFS
    
    deque<unsigned> bfs_queue;
    vector<size_t> bfs_pt(N + 1, 0);
    // vector<bool>::iterator bfs_it = bfs_wh.begin();
    // int to_pop_sz;

    // while ((bfs_it = find(bfs_it, bfs_wh.end(), 0)) != bfs_wh.end())
    // {
    //     int start = bfs_it - bfs_wh.begin();
    //     bfs_queue.push_back(start);
    //     bfs_wh[start] = 1;
    //     to_pop_sz = 1;
    //     do
    //     {
    //         FOR(i, to_pop_sz)
    //         {
    //             while (bfs_pt[start] < adj_list[start].size())
    //             {
    //                 if (bfs_wh[adj_list[start][bfs_pt[start]]] == 0)
    //                 {
    //                     bfs_queue.push_back(adj_list[start][bfs_pt[start]]);
    //                     bfs_wh[adj_list[start][bfs_pt[start]]] = 1;
    //                 }
    //                 bfs_pt[start]++;
    //             }
    //             cout << start << " ";
    //             bfs_queue.pop_front();
    //             if (!bfs_queue.empty())
    //                 start = bfs_queue.front();
    //         }
    //         if (!bfs_queue.empty())
    //         {
    //             sort(bfs_queue.begin(), bfs_queue.end());
    //             to_pop_sz = bfs_queue.size();
    //             start = bfs_queue.front();
    //         }
    //     } while (!bfs_queue.empty());
    // }

    start = 1;
    bfs_queue.push_back(start);
    bfs_wh[start] = 1;

    while (!bfs_queue.empty())
    {
        unsigned sz = bfs_queue.size();
        for (unsigned j = 0; j < sz; ++j)
        {
            start = bfs_queue.front();
            bfs_queue.pop_front();
            write(start);
            putchar(' ');
            // cout << start << " ";
            // vector<unsigned> list = adj_list[start];
            unsigned lsz = adj_list[start].size();
            for (i = 0; i < lsz; ++i)
            {
                if (bfs_wh[adj_list[start][i]] == 0)
                {
                    bfs_wh[adj_list[start][i]] = 1;
                    bfs_queue.push_back(adj_list[start][i]);
                }
            }
        }
        if (sz != 1)
            sort(bfs_queue.begin(), bfs_queue.end());
    }
    putchar('\n');
    // cout << endl;
    return 0;
}