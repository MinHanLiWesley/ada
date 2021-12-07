#include <bits/stdc++.h> 
using namespace std;
#define maxn 100005 
int n, m;
vector<int> g[maxn], visited(maxn, 0);

void dfs(int n){
	visited[n] = 1;
	for( auto &i : g[n]){
		if(!visited[i])
			dfs(i);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	cin >> n >> m;
	for(int i = 0; i < m; i ++){
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	vector<int> ans;
	for(int i = 1; i <= n; i ++){
		if(!visited[i]){
			ans.push_back(i);
			dfs(i);
		}
	}
	int num = ans.size() - 1;
	cout << num << endl;
	for(int i = 0; i < num; i ++)
		cout << ans[i] << ' ' << ans[i + 1] << endl;
	return 0;
}