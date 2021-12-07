#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define nax 100005
vector<ll> g[nax], rg[nax], vis1(nax,0), vis2(nax,0), val(nax),
 scc_tree[nax], dp(nax,0), vis3(nax,0), gr(nax);
int group_num, n, m;
ll sum;
stack<int > s;
void dfs_g(int v){
	vis1[v] = 1;
	for(auto &i: g[v]){
		if(!vis1[i])
			dfs_g(i);
	}
	s.push(v);
	return;
}

void dfs_gt(int v){
	vis2[v] = 1;
	gr[v] = group_num;
	sum += val[v];
	for(auto &i : rg[v]){
		if(!vis2[i])
			dfs_gt(i);
	}
	return;
}

void scc(){
	for(int i = 1; i <= n; i ++)
		if(!vis1[i])
			dfs_g(i);
	while(!s.empty()){
		if(!vis2[s.top()]){
			sum = 0;
			group_num ++;
			dfs_gt(s.top());
			dp[group_num] = sum;
		}
		s.pop();
	}
	return;
}

void work(int v){
	vis3[v] = 1;
	ll mx = 0;
	for(auto &i: scc_tree[v]){
		if(!vis3[i])
			work(i);
		mx = max(mx, dp[i]);
	}
	dp[v] += mx;
	return;
}

int main(){
	fast;
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> val[i];
	for(int i = 1; i <= m; i ++){
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		rg[v].pb(u);
	}
	scc();
	for(int i = 1; i <= n; i++){
		for(auto &j : g[i])
			if(gr[i] != gr[j]) scc_tree[gr[i]].pb(gr[j]);
	}
	for(int i = 1; i <= group_num; i ++){
		if(!vis3[i])
			work(i);
	}
	ll ans = 0;
	for(int i = 1; i <= group_num; i ++)
		ans = max(ans, dp[i]);
	cout << ans << endl;
}