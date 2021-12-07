#include<bits/stdc++.h>
using namespace std;

#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define ll long long 
#define pb push_back
#define pil pair<int , ll>
#define nax 500010

int n, m, u, v, dis_time = 1, tree_no;
ll w, ans;
vector<int > disc(nax, 0), low(nax, 0), scctree(nax), gr(nax, 0);
vector<ll > val(nax), dp(nax, 0);
vector<pil > g(nax);
bool on_stack[nax]; 


void tarjan(int u){
	static stack<int > s;
	disc[u] = low[u] = dis_time++;
	s.push(u);
	on_stack[u] = true;
	for(pil i: g[u]){
		if(!disc[i.first]){
			tarjan(i.first);
			low[u] = min(low[u], low[i.first]);
		}
		else if(on_stack[i.first])
			low[u] = min(low[u], disc[i.first]);
	}
	if(disc[u] == low[u]){
		while(1){
			int v = s.top();
			gr[v] = u;
			s.pop();
			on_stack[v] = false;
			scctree[tree_no].pb(v);
			if(u == v)
				break;
		}
		++tree_no;
	}
}

int main(){
	fast;
	cin >> n >> m;
	for(int i = 1; i <= n; i ++)
		cin >> val[i];
	for(int i = 0; i < m; i ++){
		cin >> u >> v >> w;
		g[u].pb({v, w});
		g[v].pb({u, w});
	}
	for(int i = 1; i <= n; i ++)
		if(!disc[i])
			tarjan(i);
	for (int i = 1; i <= n; ++i){
		dp[gr[i]] += val[i];
		for(pil j: g[i])
			if(gr[i] == gr[j.first])
				dp[gr[i]] += j.second;
	}
	/*for(){

	}
	for(){

	}*/
	for(int i = 1; i <= tree_no; i ++)
		ans = max(ans, dp[i]);
	cout << ans << endl;
	return 0;
}

