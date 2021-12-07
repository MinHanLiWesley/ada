#include <bits/stdc++.h> 
using namespace std;
#include "helper.h"
int damage[100001];
struct all{
	int type;
	int l, r;
	int attack, cost;
	int id;
	bool operator<(all &a){
		if(attack == a.attack)
			return type < a.type;
		return attack < a.attack;
	}
}All[100001], tmp[100001];

void cdq(int l, int r){
	if(l == r)
		return;
	int mid = (l + r) / 2;
	cdq(l, mid);
	cdq(mid + 1, r);
	int p1 = mid, p2 = r;
	int cur = r;
	while(p1 >= l && p2 >= mid + 1){
		if(All[p1] < All[p2]){
			if(All[p2].type == 1)
				Memory::add(All[p2].l, All[p2].r, All[p2].cost);
			tmp[cur--] = All[p2--];
		}
		else{
			if(All[p1].type == 0)
				damage[All[p1].id] += Memory::get(All[p1].l);
			tmp[cur--] = All[p1--];
		}
	}
	while(p1 >= l){
		if(All[p1].type == 0)
			damage[All[p1].id] += Memory::get(All[p1].l);
		tmp[cur--] = All[p1--];
	}
	int p3 = r;
	while(p3 > p2){
		if(All[p3].type == 1)
			Memory::add(All[p3].l, All[p3].r, -All[p3].cost);
		p3--;
	}
	while(p2 >= mid + 1)
		tmp[cur--] = All[p2--];
	for(int i = l; i < r + 1; ++i)
		All[i] = tmp[i];
	return;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, index = 0;
	cin >> n >> m;
	char c;
	for(int i = 0; i < m; ++i){
		cin >> c;
		if(c == 'A'){
			All[i].type = 1;
			cin >> All[i].l >> All[i].r >> All[i].attack >> All[i].cost; 
		}
		else{
			All[i].type = 0;
			All[i].id = index++;
			cin >> All[i].l >> All[i].attack;
		}
 	}
 	cdq(0, m-1);
 	for(int i = 0; i < index; ++i)
 		printf("%d\n", damage[i]);
	return 0;
}
