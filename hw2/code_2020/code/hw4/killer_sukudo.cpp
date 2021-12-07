#include<bits/stdc++.h>
#include "helper.h"
using namespace std;

#define ll long long 
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);

string pos[10];
int ans[10][10], constraints[100], cur, cnt, target;
char type[100];
typedef pair<int, int> P;
vector<vector<pair<int, int >>> color(150);

vector<int > Decoder(int rr){
	vector<int > ret;
	ret.push_back(rr % 9 + 1);
	rr /= 9;
	ret.push_back(rr % 9);
	rr /= 9;
	ret.push_back(rr % 9);
	return ret;
}

vector<vector<int>> result;
vector<int> com;
void help(int k,int rsum,int index){
    if(rsum == 0 && v.size() == k) {
    	result.push_back(v);
    	return;
    }
    if(com.size() >= k || rsum <= 0) 
    	return;
	for(int i = index; i <= 9; i ++)    {
    	com.push_back(i);
    	help(k, rsum - i, i + 1);
    	com.pop_back();   
	}
}
vector<vector<int > > combinationSum(int k, int n) {
    target = n;
    help(k,n,1);
    return result;
}

int main(){
	fast;
	for(int i = 0; i < 9; i ++){
		cin >> pos[i];
		for(int j = 0; j < 9; j ++){
			color[pos[i][j]].push_back(P({i, j}));
		}
	}
	for(int i = 33; i < 126; i ++)
		if(!color[i].empty())
			cur ++;
	while(cnt < cur){
		cin >> type[cnt] >> constraints[cnt];
		cnt ++;
	} 
	DLX::Init(324 + 9 * cnt + 1);
	for(int r = 0; r < 9; r ++) {
		for(int c = 0; c < 9; c ++) {
			for(int n = 1; n < 10; n ++) {
				int p[4];
				p[0] = r * 9 + n;
				p[1] = 81 + c * 9 + n;
				p[2] = 162 + ((r / 3) + (c / 3) * 3) * 9 + n;
				p[3] = 244 + r * 9 + c;
				vector<int > new_row;
				for(int i = 0; i < 4; i ++)
					new_row.push_back(p[i]);
				for(int i = 0; i < cur; i ++) {
					if(pos[r][c] == type[i]){
						new_row.push_back(324 + i * 9 + n);
						break;
					}
				}
				for(int i = 0; i < 5; i ++)
					cout << new_row[i] << ' ';
				cout << endl;
				DLX::AddRow(r * 81 + c * 9 + n - 1, new_row);
			}
		}
	}
	for(int i = 0; i < cnt; i ++){
		int cage_size = color[type[i]].size();
		vector<vector<int > > result = combinationSum(9 - cage_size, 45 - constraints[i]);
		for(vector<int > v: result){
			vector<int > add;
			for(int l: v){
				l += 324 + i * 9;
				cout << l << ' ';
				add.push_back(l);
			}
			cout << endl;
			DLX::AddRow(729 + cur, add);
			cur++;
		}
	}
	vector<int > sol = DLX::Solver();
	for(int rr: sol){
		if(rr > 729)
			continue;
		vector<int > ret = Decoder(rr);
		ans[ret[2]][ret[1]] = ret[0];
	}
	for(int i = 0; i < 9; i ++){
		for(int j = 0; j < 9; j ++){
			cout << ans[i][j];
		}
		cout << endl;
	}
	return 0;
}