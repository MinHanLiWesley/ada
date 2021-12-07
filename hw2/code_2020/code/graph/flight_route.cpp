#include<bits/stdc++.h>
using namespace std;
 
#define ff first
#define ss second
#define ll long long
#define pb push_back
#define pii pair<ll, ll >
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define maxn 100010

vector<pii> g[maxn];
vector<ll> node(maxn, 0);

int main(){
	int n, m, k;
	cin >> n >> m >> k;
	for(int i = 0; i < m; i ++){
		ll a, b, c;
		cin >> a >> b >> c;
		g[a].pb({b, c});
	}
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, 1});
	int cnt = 0;
	while(!pq.empty()){
		pii p = pq.top();
		pq.pop();
		node[p.ss] ++;
		if(node[p.ss] > k) continue;
		if(p.ss == n){
			cnt ++;
			cout << p.ff << ' ';
			if(cnt == k)
				return 0;
		} 
		for (auto &i : g[p.ss]){
			if(node[i.ff] < k)
				pq.push({p.ff + i.ss, i.ff});
		}
	}
}