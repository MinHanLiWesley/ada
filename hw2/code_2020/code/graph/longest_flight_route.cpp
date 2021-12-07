#include<bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define maxn 100005

vector<int > g[maxn], rg[maxn], vis(maxn, 0), dis(maxn, 0), par(maxn, 0);
stack<int > s;
void toposort(int start){
	vis[start] = 1;
	for(auto &i : g[start]){
		if(!vis[i]){
			dis[i] = dis[start] + 1;
			par[i] = start;
			toposort(i);
		}
	}
	s.push(start);
	return;
}

int main(){
	fast;
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i ++){
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		rg[v].push_back(u);
	}
	toposort(1);
	if(!vis[n]){
		cout << "IMPOSSIBLE" <<	endl;
		return 0;
	}
	while(!s.empty()){
		int cur = s.top();
		s.pop();
		for(auto &i: rg[cur]){
			if(dis[cur] < dis[i] + 1){
				dis[cur] = dis[i] + 1;
				par[cur] = i;
			}
		}
	}
	cout << dis[n] + 1 << endl;
	stack<int > ans;
	ans.push(n);
	int parent = par[n];
	while(parent!= 0){
		ans.push(parent);
		parent = par[parent];
	}
	while(!ans.empty()){
		cout << ans.top() << " ";
		ans.pop();
	}
	return 0;
}