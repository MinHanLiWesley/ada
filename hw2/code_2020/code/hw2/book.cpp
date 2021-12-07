#include <bits/stdc++.h> 
using namespace std;
#define ll long long 
#define maxn 100001
int n, type, cnt[maxn], beautiful[maxn], beautiful2[maxn], simple[maxn], simple2[maxn];
ll ans, ans1 = LLONG_MAX;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	cin >> n;
	for(int i = 0; i < n; ++i){
		cin >> cnt[i];
		beautiful2[i] = beautiful[i] = simple[i] = simple2[i] = cnt[i];
	}
	cin >> type;
	int ptr1 = 0, ptr2 = n - 1;
	while(simple[ptr1] == 0)
		ptr1 ++;
	while(simple[ptr2] == 0)
		ptr2 --;
	if(ptr1 == ptr2){
		ans = cnt[ptr2] - 1;
		cout << ans << endl;
		if(ptr2 == 0){
			cnt[ptr2+1] = ans;
			if(type){
				while(cnt[ptr2+1]){
					cout << (ptr2 + 1) << ' ' << (ptr2 + 2) << ' ';
					--cnt[ptr2 + 1];
				}
				cout << (ptr2 + 1) << endl;
			}
		}
		else{
			cnt[ptr1-1] = ans;
			if(type){
				while(cnt[ptr1-1]){
					cout << (ptr1+1) << ' ' << ptr1 << ' ';
					--cnt[ptr1 - 1];
				}
				cout << (ptr1 + 1) << endl;
			}
		}
		return 0;
	}
	for(int i = ptr1; i < ptr2 - 1; ++i){
		if(simple[i] > simple[i + 1]){
			ans += (simple[i] - simple[i+1]);
			beautiful[i + 1] += (simple[i] - simple[i+1]);
			simple[i + 1] = simple[i] = 1;
		}
		else {
			simple[i + 1] -= (simple[i] - 1);
			simple[i] = 1;
		}
	}
	if(ptr2 != 0){
		if(simple[ptr2-1] - simple[ptr2] > 1){
			ans += (simple[ptr2 - 1] - simple[ptr2] - 1);
			beautiful[ptr2] += (simple[ptr2 - 1] - simple[ptr2] - 1);
			simple[ptr2] = 1, simple[ptr2-1] = 2;
		}
		else if(simple[ptr2] - simple[ptr2 - 1] >= 1){
			ans += (simple[ptr2] - simple[ptr2 - 1]);
			beautiful[ptr2-1] += (simple[ptr2] - simple[ptr2 - 1]);
			simple[ptr2] = simple[ptr2 - 1] = 1;
		}
		else{
			int minus = min(simple[ptr2], simple[ptr2 - 1]);
			simple[ptr2] -= (minus - 1);
			simple[ptr2 - 1] -= (minus - 1);
		}
	}
	if(ptr1 != n - 1 && simple2[ptr1 + 1] != 0){
		ans1 = 0;
		simple2[ptr1 + 1] -= 1;
		for(int i = ptr1; i < ptr2 - 1; ++i){
			if(simple2[i] > simple2[i + 1]){
				ans1 += (simple2[i] - simple2[i+1]);
				beautiful2[i + 1] += (simple2[i] - simple2[i+1]);
				simple2[i + 1] = simple2[i] = 1;
			}
			else {
				simple2[i + 1] -= (simple2[i] - 1);
				simple2[i] = 1;
			}
		}
		if(ptr2 != 0){
			if(simple2[ptr2-1] - simple2[ptr2] > 1){
				ans1 += (simple2[ptr2 - 1] - simple2[ptr2] - 1);
				beautiful2[ptr2] += (simple2[ptr2 - 1] - simple2[ptr2] - 1);
				simple2[ptr2] = 1, simple2[ptr2-1] = 2;
			}
			else if(simple2[ptr2] - simple2[ptr2 - 1] >= 1){
				ans1 += (simple2[ptr2] - simple2[ptr2 - 1]);
				beautiful2[ptr2-1] += (simple2[ptr2] - simple2[ptr2 - 1]);
				simple2[ptr2] = simple2[ptr2 - 1] = 1;
			}
			else{
				int minus = min(simple2[ptr2], simple2[ptr2 - 1]);
				simple2[ptr2] -= (minus - 1);
				simple2[ptr2 - 1] -= (minus - 1);
			}
		}
	}
	
	if(ans < ans1){
		cout << ans << endl;
		if(type){
			while(ptr1 < ptr2 - 1){
				while(beautiful[ptr1] != 1){
					cout << (ptr1 + 1) << ' ' << (ptr1 + 2) << ' ';
					--beautiful[ptr1];
					--beautiful[ptr1+1];
				}
				cout << (ptr1 + 1) << ' ';
				++ptr1;
			}
			if(simple[ptr2 - 1] == 2){
				cout << (ptr2) << ' ';
				--beautiful[ptr2 - 1];
				while(beautiful[ptr2]){
					cout << (ptr2 + 1) << ' ' << ptr2 << ' ';
					--beautiful[ptr2];
				}
				cout << endl;
			} 
			else{
				while(beautiful[ptr2]){
					cout << ptr2 << ' ' << (ptr2 + 1) << ' ';
					--beautiful[ptr2];
				}
				cout << endl;
			}
		}
	}
	else{
		cout << ans1 << endl;
		if(type){
			cout << (ptr1 + 2) << ' ';
			--beautiful2[ptr1 + 1];
			while(ptr1 < ptr2 - 1){
				while(beautiful2[ptr1] != 1){
					cout << (ptr1 + 1) << ' ' << (ptr1 + 2) << ' ';
					--beautiful2[ptr1];
					--beautiful2[ptr1+1];
				}
				cout << (ptr1 + 1) << ' ';
				++ptr1;
			}
			if(simple2[ptr2 - 1] == 2){
				cout << (ptr2) << ' ';
				--beautiful2[ptr2 - 1];
				while(beautiful2[ptr2]){
					cout << (ptr2 + 1) << ' ' << ptr2 << ' ';
					--beautiful2[ptr2];
				}
				cout << endl;
			} 
			else{
				while(beautiful2[ptr2]){
					cout << ptr2 << ' ' << (ptr2 + 1) << ' ';
					--beautiful2[ptr2];
				}
				cout << endl;
			}
		}
	}
	
	return 0;
}