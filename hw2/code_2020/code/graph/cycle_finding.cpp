#include<bits/stdc++.h>
using namespace std;
 
#define ff first
#define ss second
#define ll long long
#define pb push_back
#define pii pair<ll, ll >
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define maxn 100010
#define inf 1e18
vector<pii> g[maxn];
vector<ll> dis(maxn, 0);
void bellman_ford(){
	for(int i = 0; i < n; i ++)
		
}

int main(){
	fast;
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i ++){
		int u, v;
		ll w;
		cin >> u >> v >> w;
		g[u].pb({v, w});
	}
	for(int i = 1; i <= n; i ++)
		dis[i] = inf;
	bellman_ford();
	return 0;
}