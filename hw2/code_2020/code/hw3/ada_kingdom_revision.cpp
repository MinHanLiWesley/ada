#include<bits/stdc++.h>
using namespace std;

#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define ll long long 
#define pb push_back
#define pil pair<int ,ll >
#define maxn 500010

int n, cur = 1, u, v, leaf;
ll d, max_dis = 0, max_leaf;
vector<ll > ans(maxn), dis(maxn, 0), dis1(maxn, 0), path;
vector<int > cnt(maxn, 0), vis(maxn, 0), vis1(maxn, 0);
vector<pil > g[maxn], par(maxn);

void dfs(int v){
	vis[v] = 1;
	for(pil i: g[v]){
		if(!vis[i.first]){
			dis[i.first] = dis[v] + i.second;
			if(dis[i.first] > max_dis){
				max_dis = dis[i.first];
				max_leaf = i.first;
			}
			dfs(i.first);
		}
	}
}

void find_path(int v){
	vis1[v] = 1;
	for(pil i: g[v]){
		if(!vis1[i.first]){
			par[i.first].first = v;
			par[i.first].second = i.second;
			find_path(i.first);
		}
	}
	if(dis1[par[v].first] < dis1[v] + par[v].second){
		if(dis[par[v].first] != 0)
			path.pb(dis1[par[v].first]);
		dis1[par[v].first] = par[v].second + dis1[v];
	}
	else
		path.pb(dis1[v] + par[v].second);
}

int main(){
	fast;
	cin >> n;
	for(int i = 0; i < n - 1; ++i){
		cin >> u >> v >> d;
		cnt[u] ++, cnt[v] ++;
		g[u].pb({v, d});
		g[v].pb({u, d});
	}
	for(int i = 0; i < n; ++i)
		if(cnt[i] == 1){
			leaf = i;
			break;
		}
	dfs(leaf);
	find_path(max_leaf);
	ans[cur] = dis1[max_leaf];
	sort(path.begin(), path.end(), greater<ll>());
	for(auto v: path){
		cur ++;
		ans[cur] = v + ans[cur - 1];
	}
	ll tmp = ans[cur];
	while(cur < n)
		ans[cur++] = tmp;
	for(int i = 0; i < n; ++i)
		cout << ans[i] << ' ';
	return 0;
}