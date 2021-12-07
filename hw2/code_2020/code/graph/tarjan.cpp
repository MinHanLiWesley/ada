#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pb push_back
#define pii pair<ll, ll >
#define maxn 1e5+5
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
typedef vector<int > vi;
typedef vector<vi > vii;

int n, m, discover_time = 1;
vvi graph, scc;
vi disc(maxn, -1), low(maxn, -1);
bool on_stack[maxn];

void tarjan(int v){
	static stack<int > st;
	disc[v] = low[v] = discover_time++;
	st.push(v);
	on_stack[v] = true;
	for(auto &i : graph[v]){
		if(disc[i] == -1){
			tarjan(i);
			low[v] = min(low[v], low[i]);
		}
		else if(on_stack[i])
			low[v] = min(low[v], disc[i]);
	}
	if(disc[v] == low[v]){
		vi scctem;
		while(1){
			int u = st.top();
			st.pop();
			on_stack[u] = false;
			scctem.pb(u);
			if(u == v)
				break;
		}
		scc.pb(scctem);	
	}
}