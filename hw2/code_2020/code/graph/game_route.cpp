#include <bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define ll long long 
const int maxn = 1e5+10;
const int mod = 1e9+7;
int n, m;
vector<int > g[maxn], vis(maxn, 0), s, dp(maxn, 0);

void topological_sort(int start){
	if(start == n)
		return;
	vis[start] = 1;
	for(auto &i: g[start]){
		if(!vis[i])
			topological_sort(i);
	}
	s.push_back(start);
	return;
}

int main(){
	fast;
	cin >> n >> m;
	for(int i = 0; i < m; i ++){
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
	}
	for(int i = 1; i <= n; i ++){
		if(!vis[i])
			topological_sort(i);
	}
	dp[n] = 1;

	for(auto &i : s){
		for(auto &j : g[i])
			dp[i] = (dp[i] + dp[j]) % mod;
	}
	cout << dp[1] << endl;
	return 0;
}