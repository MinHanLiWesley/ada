#include<bits/stdc++.h>
using namespace std;

#define ll long long 
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
const int maxn = 2e5+10;
int n, q, kind;
ll num, change_num;
vector<ll > ans(maxn, 0);
char op[10];
struct people{
	int kind, start_time;
	ll num;
}p[maxn];
deque<people > dq;

int main(){
	fast;
	cin >> n >> q;
	for(int i = 0; i < q; i ++){
		cin >> op >> num >> p[i].kind >> change_num;
		p[i].start_time = i;
		p[i].num = num + change_num;
		int head = -1;
		if(op[0] == 'f'){
			while(change_num){
				people tmp = dq.front();
				if(tmp.kind != head){
					ans[tmp.kind] += tmp.num * (i - tmp.start_time);
					if(tmp.num > change_num){
						dq.pop_front();
						tmp.num -= change_num;
						tmp.start_time = i;
						dq.push_front(tmp);
						break;
					}
					else{
						change_num -= tmp.num;
						dq.pop_front();
					}
				}
			}
			dq.push_front(p[i]);
		}
		else{
			while(change_num){
				people tmp = dq.back();
				if(tmp.kind != head){
					ans[tmp.kind] += tmp.num * (i - tmp.start_time);
					if(tmp.num > change_num){
						dq.pop_back();
						tmp.num -= change_num;
						tmp.start_time = i;
						dq.push_back(tmp);
						break;
					}
					else{
						change_num -= tmp.num;
						dq.pop_back();
					}
				}
			}
			dq.push_back(p[i]);
		}
	}
	while(!dq.empty()){
		ans[dq.front().kind] += dq.front().num * (q - dq.front().start_time);
		dq.pop_front();
	}
	for(int i = 1; i <= n; i ++)
		cout << ans[i] << ' ';
	return 0;
}