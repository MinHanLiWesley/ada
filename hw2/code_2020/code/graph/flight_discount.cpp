#include <bits/stdc++.h> 
using namespace std;
#define ll long long
#define maxn 100005
#define pll pair<int, ll>
#define f first
#define s second

struct item{
	int node;
	ll cost;
	bool discount;
	inline const bool operator<(const item &other) const {
		if (discount == other.discount)
			return cost > other.cost;
		return discount > other.discount;
	}
};

ll dis[maxn][2];
bool vis[maxn][2];
vector<pll > adj[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i ++){
		int u, v;
		ll price;
		cin >> u >> v >> price;
		--u, --v;
		adj[u].push_back({v, price});
	}
	for(int i = 0; i < n; i ++)
		dis[i][0] = dis[i][1] = 1e18;
	priority_queue<item> pq;
	pq.push({0, 0, false});
	while(!pq.empty()){
		item cur = pq.top();
		pq.pop();
		if(cur.node == n-1 && cur.discount){
			cout << cur.cost << endl;
			return 0;
		}
		for (pll nxt : adj[cur.node]){
			if(dis[nxt.first][cur.discount] > cur.cost + nxt.second){
				dis[nxt.first][cur.discount] = cur.cost + nxt.second;
				pq.push({nxt.first, dis[nxt.first][cur.discount], cur.discount});
			}
			if(!cur.discount)
				if(dis[nxt.first][1] > cur.cost + nxt.second / 2){
					dis[nxt.first][1] = cur.cost + nxt.second / 2;
					pq.push({nxt.first, dis[nxt.first][1], true});
				}
		}
	}
}