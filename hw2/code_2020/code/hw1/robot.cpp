#include <bits/stdc++.h> 
using namespace std;
#define ll long long 
ll weight[501][501]; 
ll dp[11][501][501]; //dp[i][j][k], (i, j) = (x, y), k = jump times
ll largest[11][3]; // largest[][0], largest[][1] = (x, y), largest[][2] = value
stack<vector<int> > st;

ll findMax(int i, int j, ll k, ll c){
   ll ans;
   if(k == 0){
      if(i > 0 && j > 0)
         ans = max(dp[k][i][j-1], dp[k][i-1][j]) + weight[i][j];
      else if(i > 0)
         ans = dp[k][i-1][j] + weight[i][j];
      else if(j > 0)
         ans = dp[k][i][j-1] + weight[i][j];
      else
         ans = weight[i][j];
   }
   else{
      if (i > 0 && j > 0)
         ans = max({dp[k][i-1][j], dp[k][i][j-1], largest[k-1][2]}) + (weight[i][j] - c * k);
      else if(i > 0)
         ans = max(dp[k][i-1][j], largest[k-1][2]) + (weight[i][j] - c * k);
      else if(j > 0)
         ans = max(dp[k][i][j-1], largest[k-1][2]) + (weight[i][j] - c * k);
      else 
         ans = largest[k-1][2] + (weight[i][j] - c * k);
   }
   return ans;
}  

int main(){
   ll n, m, l, c;
   scanf("%lld %lld %lld %lld", &n, &m, &l, &c);
   for(int i = 0; i < n; i ++)
      for(int j = 0; j < m; j ++)
         scanf("%lld", &weight[i][j]);
   for (int i = 0; i < l+1; ++i)
      largest[i][2] = LLONG_MIN;
   ll ans;
   int id = 0;
   for(ll k = 0; k < l+1; ++k){
      for(int i = 0; i < n; ++i){
         for(int j = 0; j < m; ++j){
            dp[k][i][j] = findMax(i, j, k, c);
            if(dp[k][i][j] > largest[k][2]){
               largest[k][2] = dp[k][i][j];
               largest[k][0] = i;
               largest[k][1] = j;
            } 
         }
      }
      if(k == 0)
         ans = dp[k][n-1][m-1];
      if(k != 0){
         if(dp[k][n-1][m-1] > ans){
            ans = dp[k][n-1][m-1];
            id = k;
         }
         else
            break;
      }
   }
   int cnt = 0;
   int i = n - 1, j = m - 1;
   ll k = id;
   while(i != 0 || j != 0 || k != 0){
      cnt += 1;
      st.push({i, j, k});
      dp[k][i][j] -= (weight[i][j] - k * c);
      if(i != 0 && dp[k][i][j] == dp[k][i-1][j])
         i -= 1;
      else if(j != 0 && dp[k][i][j] == dp[k][i][j-1])
         j -= 1;
      else
         i = largest[k-1][0], j = largest[k-1][1], k -= 1;
   }
   printf("%lld\n%d\n", ans, cnt);
   k = 0;
   while(!st.empty()){
      if(st.top()[2] == k)
         printf("Move %d %d\n", st.top()[0], st.top()[1]);
      else{
         k = st.top()[2];
         printf("Jump %d %d\n", st.top()[0], st.top()[1]);
      }
      st.pop();
   }
   return 0;
}