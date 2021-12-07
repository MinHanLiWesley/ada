#include<bits/stdc++.h>
using namespace std;

#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define ll long long 
#define pb push_back
#define pil pair<int , ll>
#define maxn 500010

int n, m, group_num;
ll w, sum, ans;
vector<ll> gr(maxn), val(maxn), dp(maxn, 0);
vector<bool > vis1(maxn, 0), vis2(maxn, 0), vis3(maxn, 0);
vector<pil> g[maxn], rg[maxn], scc_tree[maxn];
stack<int > s;

void dfs(int start){
	vis1[start] = true;
	for(pil nxt: g[start])
		if(!vis1[nxt.first])
			dfs(nxt.first);
	s.push(start);
	return;
}

void dfs_gt(int start){
	vis2[start] = true;
	gr[start] = group_num;
	for(pil nxt : rg[start])
		if(!vis2[nxt.first])
			dfs_gt(nxt.first);
	return;
}

void scc(){
	for(int i = 1; i <= n; i ++)
		if(!vis1[i])
			dfs(i);
	while(!s.empty()){
		if(!vis2[s.top()]){
			group_num ++;
			dfs_gt(s.top());
		}
		s.pop();
	}
	return;
}

void work(int start){
	vis3[start] = true;
	ll mx = 0;
	for(pil nxt: scc_tree[start]){
		if(!vis3[nxt.first])
			work(nxt.first);
		mx = max(mx, dp[nxt.first] + nxt.second);
	}
	dp[start] += mx;
	return;
}

int main(){
	fast;
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> val[i];
	for(int i = 0; i < m; i ++){
		int u, v;
		cin >> u >> v >> w;
		g[u].pb({v, w});
		rg[v].pb({u, w});
	}
	scc(); // build scc_tree
	for(int i = 1; i <= n; i ++){ //count each tree
		dp[gr[i]] += val[i];
		for(pil j : g[i]){
			if(gr[i] == gr[j.first]){
				dp[gr[i]] += j.second;
			}
		}
	}
	for(int i = 1; i <= n; i++){ // connect all scc_tree
		for(pil j : g[i])
			if(gr[i] != gr[j.first]) scc_tree[gr[i]].pb({gr[j.first], j.second});
	}
	for(int i = 1; i <= group_num; i ++){ // topological_sort with dp[]
		if(!vis3[i])
			work(i);
	}
	for(int i = 1; i <= group_num; i ++)
		ans = max(ans, dp[i]);
	cout << ans << endl;
	return 0;
}