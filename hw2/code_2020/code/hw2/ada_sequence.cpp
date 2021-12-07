#include <bits/stdc++.h> 
using namespace std;
#define ll long long
ll cost[201],dp[601][201][201]; 
int n, k , d, op, choose, chosen[201], num[201], s[201], final, opt[201][2];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> k >> d;
	for(int i = 1; i <= n; ++i)
		cin >> num[i];
	for(int i = 1; i <= n; ++i)
		cin >> cost[i];
	for(int i = 1; i <= n; ++i)
		cin >> s[i];
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			for(int l = 0; l <= 3 * n; ++l)
				dp[l][i][j] = INT_MAX - 10;
	for(int i = 1; i <= n; ++i){
		dp[s[i]][i][i] = 0;
		if(i < n && abs(num[i] - num[i + 1]) <= d){
			dp[s[i] + s[i + 1]][i][i+1] = 0;
		}
		else if(i < n){
			dp[s[i] + s[i + 1]][i][i + 1] = min(cost[i], cost[i + 1]);
			dp[s[i]][i][i + 1] = 0;
			dp[s[i + 1]][i][i + 1] = 0;
		}
	}
	for(int i = n; i > 0; --i){
		for(int j = i + 2; j <= n; ++j){
			for(int l = 0; l <= 3 * (j - i + 1); ++l){
				ll a = LLONG_MAX;
				if(l >= s[i] + s[j]){
					if(abs(num[i] - num[j]) > d)
						a = dp[l-s[i]-s[j]][i+1][j-1] + min(cost[i], cost[j]);
					else
						a = dp[l-s[i]-s[j]][i+1][j-1];
				}
				dp[l][i][j] = min({a, dp[l][i+1][j], dp[l][i][j-1]});
			}
		}
	}
	for(int i = (3 * n); i >= 0; --i){
		if(dp[i][1][n] <= k){
			final = i;
			break;
		}
	}
	cout << final << endl;
	int left = 1, right = n;
	while(left <= right){
		if(left == right){
			chosen[choose++] = left;
			break;
		}
		if(dp[final][left+1][right] == dp[final][left][right])
			++left;
		else if(dp[final][left][right-1] == dp[final][left][right])
			--right;
		else {
			final -= (s[left] + s[right]);
			chosen[choose++] = left;
			chosen[choose++] = right;
			if(abs(num[left] - num[right]) > d){	
				if(cost[left] > cost[right]){
					opt[op][0] = right;
					opt[op++][1] = num[left];
				}
				else{
					opt[op][0] = left;
					opt[op++][1] = num[right];
				}
			}
			++left;
			--right;
		}
	}
	cout << op << endl;
	for(int i = 0; i < op; ++i)
		cout << opt[i][0] << ' ' << opt[i][1] << endl;
	cout << choose << endl;
	sort(chosen, chosen + choose);
	for(int i = 0; i < choose; ++i)
		cout << chosen[i] << ' ';
	cout << endl;
	return 0;
}