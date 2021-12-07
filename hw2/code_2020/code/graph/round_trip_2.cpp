#include <bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define ll long long 
#define pb push_back
const int maxn = 1e5+10;
int n, m;
vector<int > g[maxn], par(maxn, 0), vis(maxn, 0);

void dfs(int start){
	vis[start] = 1;
	for(auto &i : g[start]){
		if(!vis[i])
			dfs(i);
		else if(vis[i] == 1){
			vector<int > ans;
			ans.pb(i);
			int cur = i;
			par[start] = i;
			while(par[cur] != i){
				ans.pb(par[cur]);
				cur = par[cur];
			}
			ans.pb(i);
			cout << ans.size() << endl;
			for(auto &s : ans)
				cout << s << " ";
			exit(0);
		}
	}
	vis[start] = 2;
	return;
}

int main(){
	fast;
	cin >> n >> m;
	for(int i = 0; i < m; i ++){
		int u, v;
		cin >> u >> v;
		if(u == v){
			cout << 2 << endl;
			cout << u << v << endl;
		}
		g[u].pb(v);
	}
	for(int i = 1; i <= n; i ++)
		if(!vis[i])
			dfs(i);
	cout << "IMPOSSIBLE" << endl;
	return 0;
} 