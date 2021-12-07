#include<bits/stdc++.h>
using namespace std;
 
#define ff first
#define ss second
#define ll long long
#define pb push_back
#define pii pair< int,int >
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
const int nax = 5e2+5;
const ll inf = 1e15;


ll dp[nax][nax];
 
void  floyd_warshall(int n){
	for(int i = 1; i <= n; i ++)
		dp[i][i] = 0;
	for(int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j++)
			for(int k = 1; k <= n; k ++)
				dp[j][k] = min(dp[j][k], dp[j][i] + dp[i][k]);
}
int main(){
	fast;
	int n, m, q;
	cin >> n >> m >> q;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++){
			dp[i][j] = inf;
		}
	}
	for(int i = 0; i < m; i ++){
		int u, v;
		ll w;
		cin >> u >> v >> w;
		dp[u][v] = min(dp[u][v], w);
		dp[v][u] = min(dp[v][u], w);
	}
	floyd_warshall(n);
	int u[q], v[q];
	for(int i = 0; i < q; i ++)
		cin >> u[i] >> v[i];
	for(int i = 0; i < q; i ++){
		if(dp[u[i]][v[i]] == inf)
			cout << -1 << endl;
		else
			cout << dp[u[i]][v[i]] << endl;
	}
	return 0;
}