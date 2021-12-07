#include<bits/stdc++.h>
using namespace std;

#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define ll long long 
#define pb push_back
#define pil pair<int ,ll >
#define maxn 500010

int n;
vector<ll > ans[maxn];
vector<pil > g[maxn];
priority_queue<ll > pq;
vector<int > cnt[maxn];

bool is_leaf(int v){
	if(cnt[v] == 1)
		return true;
	return false;
}



int main(){
	fast;
	cin >> n;
	for(int i = 0; i < n; i ++){
		int u, v;
		ll d;
		cin >> u >> v >> d;
		total += d;
		cnt[u] ++, cnt[v] ++;
		g[u].pb({v, d});
		g[v].pb({u, d});
	}
	int leaf_num = 0;
	for(int i = 1; i <= n; i ++)
		if(is_leaf(i))
			leaf_num++;
	for(int i = leaf_num; i <= n; i ++)
		ans[i] = total;

	for(int i = 1; i <= n; i ++)
		cout << ans[i] << ' ';
	return 0;
}