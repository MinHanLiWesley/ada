#include <bits/stdc++.h>
#include <stdio.h>
#define F(a, b) for (int(a) = 0; (a) < (b); ++(a))
#define long long ll

using namespace std;

/*
step 1. 找直徑
step 2. 標色跟註記直徑跟支鍊的連法
    a. 直徑上的點: 1
    b. 直徑旁的點: 0
    c. 其他點： -1

step 3. 算支鏈的直徑
step 4. 順逆向求出子樹直徑
step 5. 算兩顆樹的半徑+1的最大值 如果沒有大於它的話就output原本的直徑


*/

typedef struct Branch
{
    int diameter;
    int parent;
} Branch;

typedef struct Diameter
{
    int forward;
    int backward;
} Diameter;

inline void Read(int &x)
{
    x = 0;
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
}

int Find(vector<int> &parent, vector<int> &backbone, vector<int> &color, int i)
{
    backbone.push_back(i);
    color[i] = 1;
    if (parent[i] == -1)
        return i;
    return Find(parent, backbone, color, parent[i]);
}

int bfs_find_diameter_fir(vector<vector<int>> &adj_list, int start)
{
    int N = adj_list.size();
    deque<int> bfs_queue;
    vector<int> diset(N + 1, -1);
    vector<bool> bfs_wh(N + 1, 0);
    vector<int> diameter(N + 1, 0);
    vector<int>::iterator it = diameter.begin();
    bfs_queue.push_back(start);
    bfs_wh[start] = 1;
    while (!bfs_queue.empty())
    {

        start = bfs_queue.front();
        bfs_queue.pop_front();
        vector<int> list = adj_list[start];
        unsigned lsz = list.size();
        for (int i = 0; i < lsz; ++i)
        {
            if (bfs_wh[list[i]] == 0)
            {
                diset[list[i]] = start;
                bfs_wh[list[i]] = 1;
                diameter[list[i]] += diameter[start] + 1;
                bfs_queue.push_back(list[i]);
            }
        }
    }

    return int(max_element(it + 1, it + N + 1) - it);
}

int bfs_find_diameter_sec(vector<vector<int>> &adj_list, int start, vector<int> &backbone_lst, vector<int> &color)
{
    int N = adj_list.size();
    deque<int> bfs_queue;
    vector<int> diset(N + 1, -1);
    vector<bool> bfs_wh(N + 1, 0);
    vector<int> diameter(N + 1, 0);
    vector<int>::iterator it = diameter.begin();
    bfs_queue.push_back(start);
    bfs_wh[start] = 1;
    int max_dia = 0;
    while (!bfs_queue.empty())
    {

        start = bfs_queue.front();
        bfs_queue.pop_front();
        vector<int> list = adj_list[start];
        unsigned lsz = list.size();
        for (int i = 0; i < lsz; ++i)
        {
            if (bfs_wh[list[i]] == 0)
            {
                diset[list[i]] = start;
                bfs_wh[list[i]] = 1;
                diameter[list[i]] += diameter[start] + 1;
                bfs_queue.push_back(list[i]);
            }
        }
    }
    Find(diset, backbone_lst, color, start);

    return *max_element(it + 1, it + N + 1);
}

int bfs_find_diameter_br(vector<vector<int>> &adj_list,vector<bool>& bfs_wh, vector<int>& diameter,int start, int backbone)
{
    int N = adj_list.size();
    deque<int> bfs_queue;
    diameter[start]=0;
    vector<int>::iterator it = diameter.begin();
    bfs_queue.push_back(start);
    bfs_wh[start] = 1;
    int max_dia=0;
    while (!bfs_queue.empty())
    {

        start = bfs_queue.front();
        bfs_queue.pop_front();
        vector<int> list = adj_list[start];
        unsigned lsz = list.size();
        for (int i = 0; i < lsz; ++i)
        {
            if (list[i] == backbone)
                continue;
            if (bfs_wh[list[i]] == 0)
            {
                bfs_wh[list[i]] = 1;
                diameter[list[i]] += diameter[start] + 1;
                max_dia = max(max_dia, diameter[list[i]]);
                bfs_queue.push_back(list[i]);
            }
        }
    }

    return max_dia;
}

void coloring(vector<vector<int>> &adj_list, vector<int> &backbone_lst, vector<int> &color, vector<Branch> &branch_lst, vector<int> &branch_lst_idx, vector<bool> &has_branch)
{
    for (int i = 0; i < backbone_lst.size(); ++i)
    {
        vector<int> lst = adj_list[backbone_lst[i]];
        for (int j = 0; j < lst.size(); ++j)
        {
            if (color[lst[j]] == 1)
                continue;
            color[lst[j]] = 0;
            has_branch[backbone_lst[i]] = 1;
            branch_lst[lst[j]].parent = backbone_lst[i];
            branch_lst_idx.push_back(lst[j]);
        }
    }
}

int main()
{

    int N;
    Read(N);
    // cin >> N;
    // Read(N);

    vector<vector<int>> adj_list(N + 1, vector<int>());
    vector<int> color(N + 1, -1);
    vector<Branch> branch_list(N + 1);
    vector<int> max_branch_diameter(N + 1);
    vector<bool> has_branch(N + 1);
    vector<int> backbone_lst;
    vector<int> branch_lst_idx;

    F(i, N - 1)
    {
        int a, b;
        Read(a), Read(b);
        // Read(a), Read(b);
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    /*step 1 找直徑，順便標直徑顏色*/

    int start = bfs_find_diameter_fir(adj_list, 1);
    bfs_find_diameter_sec(adj_list, start, backbone_lst, color);

    vector<Diameter> diameter_lst(backbone_lst.size());

    /*step 2 標其他點顏色*/

    coloring(adj_list, backbone_lst, color, branch_list, branch_lst_idx, has_branch);

    /*step 3 標支鍊子樹直徑*/
vector<bool> bfs_wh(N+1,0);
vector<int> diameter(N+1,0);
    for (int i = 0; i < branch_lst_idx.size(); ++i)
    {
        
        branch_list[branch_lst_idx[i]].diameter = bfs_find_diameter_br(adj_list,bfs_wh,diameter, branch_lst_idx[i], branch_list[branch_lst_idx[i]].parent);
        max_branch_diameter[branch_list[branch_lst_idx[i]].parent] = max(max_branch_diameter[branch_list[branch_lst_idx[i]].parent], branch_list[branch_lst_idx[i]].diameter);
    // fill(bfs_wh.begin()+1,bfs_wh.begin()+N+1,0);
    // fill(diameter.begin()+1,diameter.begin()+N+1,0);
    }

    /*step 4 遍歷算直徑*/

    // 順
    int sz = diameter_lst.size();
    diameter_lst[0].forward = 0;
    for (int i = 1; i < sz; ++i)
    {
        int idx = backbone_lst[i];
        if (has_branch[idx])
            diameter_lst[i].forward = max(diameter_lst[i - 1].forward, i + max_branch_diameter[idx] + 1);
        else
            diameter_lst[i].forward = max(diameter_lst[i - 1].forward, i);
    }
    int original_dia = diameter_lst[sz - 1].forward;
    //逆
    int update_dia = 1000000;
    diameter_lst[sz - 1].backward = 0;

    for (int i = sz - 2; i >= 0; --i)
    {
        int idx = backbone_lst[i];
        if (has_branch[idx])
            diameter_lst[i].backward = max(diameter_lst[i + 1].backward, sz - i - 1 + max_branch_diameter[idx] + 1);
        else
            diameter_lst[i].backward = max(diameter_lst[i + 1].backward, sz - i - 1);

        update_dia = min(update_dia, max({diameter_lst[i].forward, diameter_lst[i + 1].backward, 1 + diameter_lst[i].forward + diameter_lst[i + 1].backward - diameter_lst[i].forward / 2 - diameter_lst[i + 1].backward / 2}));
    }

    /*算最短直徑*/

    // for (int i = 1; i < sz; ++i)
    // {
    //     int rad_forward = diameter_lst[i - 1].forward - diameter_lst[i - 1].forward /2;
    //     int rad_backward = diameter_lst[i].backward - diameter_lst[i].backward /2;
    //     update_dia = min(update_dia,max({diameter_lst[i - 1].forward, diameter_lst[i].backward, 1 + rad_forward + rad_backward}));
    // }

    printf("%d\n", min(original_dia, update_dia));

    return 0;
}