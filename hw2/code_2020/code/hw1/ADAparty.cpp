#include <bits/stdc++.h> 
using namespace std;
#define ll long long 
#define MAXN 500010
ll MINF, ans;
int k, num[MAXN], prefix[MAXN], left_max[MAXN], right_max[MAXN], left_min[MAXN], right_min[MAXN], mp[MAXN];
void prefix_function(int size){
	for(int i = 1; i <= size; ++i){
		prefix[i] = prefix[i - 1] + num[i - 1];
		if(prefix[i] >= k)
			prefix[i] %= k;
	}
	return;
}
void divide_and_conquer(int l, int r){
	if(r == l)
		return;
	if(r - l == 1){
		++ans;
		return;
	}
	if(r - l == 2)
		if(prefix[r + 1] - prefix[l] - max({num[r], num[r-1], num[l]}) - min({num[r], num[r-1], num[l]}) % k == 0){
			++ans;
			return;
		}
	if(r - l < 10){
		for(int i = l; i < r; ++i){
			ll cur_min = min(num[i], num[i + 1]), cur_max = max(num[i], num[i + 1]);
			for (int j = i + 1; j <= r; ++j){
				if(num[j] > cur_max) cur_max = num[j];
				if(num[j] < cur_min) cur_min = num[j];
				if((prefix[j + 1] - prefix[i] - cur_max - cur_min) % k == 0) ++ans;
			}
		}
		return;
	}
	int mid = (l + r) / 2;
	divide_and_conquer(l, mid);
	divide_and_conquer(mid + 1, r);
	right_min[mid] = left_min[mid] = right_max[mid] = left_max[mid] = num[mid];
	right_min[mid + 1] = left_min[mid + 1] = right_max[mid + 1] = left_max[mid + 1] = num[mid + 1];
	for(int i = mid + 2; i <= r; ++i){
		right_min[i] = min(num[i], right_min[i - 1]);
		right_max[i] = max(num[i], right_max[i - 1]);
	}
	for(int i = mid - 1; i >= l; --i){
		left_min[i] = min(num[i], left_min[i + 1]);
		left_max[i] = max(num[i], left_max[i + 1]);
	}
	// lmin and lmax
	for(int i = mid, j = mid + 1; i >= l; --i){
		while(j <= r && left_max[i] > right_max[j] && left_min[i] <= right_min[j])
			mp[(MINF + prefix[++j] - prefix[mid + 1]) % k]++;
		int endpoint = (MINF - (prefix[mid + 1] - prefix[i] - left_min[i] - left_max[i])) % k;
		ans += mp[endpoint];
	}
	for(int i = mid + 1; i <= r; ++i)
		mp[(MINF + prefix[i + 1] - prefix[mid + 1]) % k] = 0;
	// rmin and rmax
	for(int i = mid + 1, j = mid; i <= r; ++i){
		while(j >= l && right_max[i] >= left_max[j] && right_min[i] < left_min[j])
			++mp[(MINF + prefix[mid + 1] - prefix[j--]) % k];
		int endpoint = (MINF - (prefix[i + 1] - prefix[mid + 1] - right_max[i] - right_min[i])) % k;
		ans += mp[endpoint];
	}
	for(int i = l; i <= mid; ++i)
		mp[(MINF + prefix[mid + 1] - prefix[i]) % k] = 0;
	// lmin and rmax
	int ptr = mid + 1;
	for(int i = mid, j = mid + 1; i >= l; --i){
		while(j <= r && right_min[j] >= left_min[i])
			++mp[(MINF + prefix[j + 1] - prefix[mid + 1] - right_max[j++]) % k];
		while(ptr < j && right_max[ptr] < left_max[i])
			--mp[(MINF + prefix[ptr + 1] - prefix[mid + 1] - right_max[ptr++]) % k];
		int endpoint = (MINF - (prefix[mid + 1] - prefix[i] - left_min[i])) % k;
		ans += mp[endpoint];
	}
	for(int i = ptr - 1; i <= r; ++i)
		mp[(MINF + prefix[i + 1] - prefix[mid + 1] - right_max[i]) % k] = 0;
	// lmax and rmin
	ptr = mid + 1;
	for(int i = mid, j = mid + 1; i >= l; --i){
		while(j <= r && right_max[j] < left_max[i])
			++mp[(MINF + prefix[j + 1] - prefix[mid + 1] - right_min[j++]) % k];
		while(ptr < j && right_min[ptr] >= left_min[i])
			--mp[(MINF + prefix[ptr + 1] - prefix[mid + 1] - right_min[ptr++]) % k];
		int endpoint = (MINF - (prefix[mid + 1] - prefix[i] - left_max[i])) % k;
		ans += mp[endpoint];
	}
	for(int i = ptr - 1; i <= r; ++i) 
		mp[(MINF + prefix[i + 1] - prefix[mid + 1] - right_min[i]) % k] = 0;
	return;
} 
int main(){
	int n;
	scanf("%d%d", &n, &k);
	MINF = 2000000009LL;
	for(int i = 0; i < n; i ++){
		scanf("%d", &num[i]);
		left_min[i] = right_min[i] = left_max[i] = right_max[i] = num[i];
	}
	prefix_function(n);
	divide_and_conquer(0, n - 1);
	printf("%lld\n", ans);
	return 0;
}