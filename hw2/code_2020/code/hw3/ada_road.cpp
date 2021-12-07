#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pb push_back
#define pii pair<ll, ll >
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
 
const int nax = 3e5+5;
const ll inf = 1e15;
vector<pii> g[nax] ;
vector<ll > dist(nax , inf);
vector<int > vis(nax, 0), p(nax, 0), used(nax, 0);
int n, m, s, t;

struct Edge{
    int u, v;
    ll w;
}edge[nax];

bool cmp1(Edge a, Edge b){
    return a.w < b.w;
}

int find(int x){
    return x == p[x] ? x : (p[x] = find(p[x]));
}

void Union(int x, int y){
    int X = find(x);
    int Y = find(y);
    p[X] = Y;
}

void kruskal(){
    ll prev_w = -1;
    int start = 0, end = 0, cur = 0;
    while(cur < m){
        if(edge[cur].w != prev_w){
            prev_w = edge[cur].w;
            end = cur;
            for(int i = start; i < end; i ++)
                if(find(edge[i].u) != find(edge[i].v))
                    used[i] = 1;
            for(int i = start; i < end; i ++)
                if(used[i] == 1)
                    Union(edge[i].u, edge[i].v);
            start = cur;
        }
        cur ++;
    }
    for(int i = start; i < m; i ++)
        if(find(edge[i].u) != find(edge[i].v))
            used[i] = 1;
    for(int i = start; i < m; i ++)
        if(used[i] == 1)
            Union(edge[i].u, edge[i].v);
}
 
void dijkstra(int start){
    priority_queue< pii , vector<pii> , greater<pii >> Q;
    dist[start] = 0;
    Q.push({0, start});
    while(!Q.empty()){
        pii p = Q.top();
        Q.pop();
        if(vis[p.second]) continue;
        vis[p.second] = 1;
        for(auto &i : g[p.second]){
            if(!vis[i.first]){
                if(dist[i.first] > p.first + i.second){
                    dist[i.first] = p.first + i.second;
                    Q.push({dist[i.first], i.first});
                }
            }
        }
    }
}
 
int main(){
    fast;
    cin >> n >> m >> s >> t;
    for(int i = 0; i < m; ++i)
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    sort(edge, edge + m, cmp1);
    for(int i = 1; i <= n; ++i)
        p[i] = i;
    kruskal();
    for(int i = 0; i < m; ++i)
        if(used[i]){
            g[edge[i].u].pb({edge[i].v, edge[i].w});
            g[edge[i].v].pb({edge[i].u, edge[i].w});
        }
    dijkstra(s);
    cout << dist[t] << endl;
    return 0;
}