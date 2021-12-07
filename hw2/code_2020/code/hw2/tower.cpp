#include <bits/stdc++.h> 
using namespace std;
#define ll long long  
ll dp[2][100001], weight[100001], a, b, n, k, ans, layer_max, max_with_bonus;
	
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> k >> a >> b;
	for(int i = 0; i < n; ++i)
		cin >> weight[i];
	for(int j = 0; j < n; ++j){
		ans = max(ans, weight[j]);
		dp[0][j] = weight[j];
	}
	for(int i = 1; i < k; ++i){
		layer_max = dp[(i + 1) % 2][i - 1];
		max_with_bonus = dp[(i + 1) % 2][i - 1] + a * (b - 1);
		dp[i % 2][i] = max_with_bonus + weight[i];
		ans = max(ans, dp[i % 2][i]);
		for(int j = i + 1; j < n; ++j){
			layer_max = max(layer_max, dp[(i + 1) % 2][j - 1]);
			max_with_bonus = max(max_with_bonus - a, dp[(i + 1) % 2][j - 1] + a * (b - 1));
			dp[i % 2][j] = max(layer_max, max_with_bonus) + weight[j];
			ans = max(ans, dp[i % 2][j]);
		}
	}
	cout << ans << endl;
	return 0;
}