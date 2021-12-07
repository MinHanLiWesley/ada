#include <bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define ll long long 
#define pb push_back
const int maxn = 1e5+5;
int n, m;
vector<int > g[maxn], par(maxn, -1), vis(maxn, 0);

void dfs(int start, int parent){
	par[start] = parent;
	vis[start] = 1;
	for(auto &i : g[start]){
		if(!vis[i])
			dfs(i, start);
		else if(i != parent){
			vector<int > cycle;
			int cur = start;
			cycle.pb(cur);
			while(par[cur] != i){
				cur = par[cur];
				cycle.pb(cur);
			}
			cycle.pb(i);
			cycle.pb(start);
			cout << cycle.size() << endl;
			for(auto &ans : cycle)
				cout << ans << " ";
			exit(0);
		}
	}
}

int main(){
	fast;
	cin >> n >> m;
	for(int i = 0; i < m; i ++){
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	for(int i = 1; i <= n; i ++)
		if(!vis[i])
			dfs(i, -1);
	cout << "IMPOSSIBLE" << endl;
	return 0;
} 