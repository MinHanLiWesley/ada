#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define maxn 200010

ll k, v, nums[maxn], bit[maxn], out[maxn], ans, choose, b;
int n, m, cur;
bool flag;
struct seg{
	int left, right, idx;
	ll num;
}s[maxn];

int lowbit(int x){
	return x & (-x);
}

bool cmp1(seg s1, seg s2){
	if(s1.left != s2.left)
		return s1.left < s2.left;
	return s1.right < s2.right;
}

struct cmp2{
	bool operator()(const seg &a, const seg &b){
		if(a.right != b.right)
			return a.right < b.right; 
		return a.left > b.left; 
	}
};

priority_queue<seg, vector<seg>, cmp2> p;

void add_interval(int pos, ll val){
	while(pos > 0){
		bit[pos] += val;
		pos -= lowbit(pos);
	}
}

ll find(int pos){
	ll sum = 0;
	while(pos <= m){
		sum += bit[pos];
		pos += lowbit(pos);
	}
	return sum;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m >> k;
	for(int i = 0; i < n; ++i){
		s[i].idx = i;
		cin >> s[i].left >> s[i].right >> s[i].num;
		s[i].left += 1;
	}
	sort(s, s + n, cmp1);
	ll min_v = 0, max_v = k;
	while(min_v <= max_v){
		flag = true, cur = 0, choose = 0;
		v = (max_v - min_v) / 2 + min_v;
		for(int i = 1; i <= m; ++i){
			while(cur < n && s[cur].left <= i){
				nums[s[cur].idx] = s[cur].num;
				p.push(s[cur]);
				cur ++;
			}
			b = find(i);
			while(b < v && !p.empty() && p.top().right >= i){
				if(nums[p.top().idx] > (v - b)){
					add_interval(p.top().left - 1, -(v - b));
					add_interval(p.top().right, (v - b));
					choose += (v - b);
					nums[p.top().idx] -= (v - b);
					b = v;
				}
				else{
					add_interval(p.top().left - 1, -nums[p.top().idx]);
					add_interval(p.top().right, nums[p.top().idx]);
					b += nums[p.top().idx];
					choose += nums[p.top().idx];
					p.pop();
				}
			}
			if(b < v){
				flag = false;
				break;
			}
			if(choose > k){
				flag = false;
				break;
			}
		}
		for(int i = 0; i <= m; ++i)
			bit[i] = 0;
		p = priority_queue<seg, vector<seg>, cmp2>();
		if(flag){
			min_v = v + 1;
			if(ans < v)
				ans = v;
		}
		else
			max_v = v - 1;

	}
	cout << ans << endl;
	cur = 0;
	for(int i = 1; i <= m; ++i){
		while(cur < n && s[cur].left <= i){
			out[s[cur].idx] = nums[s[cur].idx] = s[cur].num;
			p.push(s[cur]);
			cur ++;
		}
		b = find(i);
		while(b < ans && !p.empty() && p.top().right >= i){
			if(nums[p.top().idx] > (v - b)){
				add_interval(p.top().left - 1, -(v - b));
				add_interval(p.top().right, (v - b));
				nums[p.top().idx] -= (v - b);
				b = v;
			}
			else{	
				add_interval(p.top().left - 1, -nums[p.top().idx]);
				add_interval(p.top().right, nums[p.top().idx]);
				b += nums[p.top().idx];
				nums[p.top().idx] = 0;
				p.pop();
			}
		}
	}
	for(int i = 0; i < n; ++i)
		cout << out[i] - nums[i] << ' ';
	cout << endl;
	return 0;
}