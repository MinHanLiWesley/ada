#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;


int main(){
	int n;
	cin >> n;
	auto num = vector<int>(n);
	for(int i = 0;i < n;i++)
		cin >> num[i];
	
	auto min_subarray_pos = vector<int>(n);
	auto min_subarray_neg = vector<int>(n);
	auto left = vector<int>(n);
	auto right = vector<int>(n);
	min_subarray_pos[0] = num[0];
	min_subarray_neg[n-1] = num[n-1];
	int cur_min = num[0];
	int ans_min = num[0];
	int total = num[0];
	int min_pos_start = 0;
	int min_pos_end = 0;
	

	for(int i = 1;i < n;i++){
		left[i] = ans_min;
		total += num[i];
		if(num[i] < cur_min + num[i])
			min_pos_start = i;
		cur_min = min(cur_min + num[i], num[i]);
		min_subarray_pos[i] = cur_min;
		if(cur_min < ans_min)
			min_pos_end = i;
		ans_min = min(cur_min, ans_min);
		
	}
	for(auto it : left)
		cout << it << ' ';
	cout << '\n';
	cur_min = ans_min = num[n-1];
	int min_neg_start = n-1;
	int min_neg_end = n-1;
	for(int i = n-2;i >= 0;i--){
		right[i] = ans_min;
		if(num[i] < cur_min + num[i])
			min_neg_start = i;
		cur_min = min(cur_min + num[i], num[i]);
		min_subarray_neg[i] = cur_min;
		if(cur_min < ans_min)
			min_neg_end = i;
		ans_min = min(cur_min, ans_min);
	}
	for(auto it : right)
		cout << it << ' ';
	cout << '\n';
	auto final_res = vector<int>(n);
	ans_min = 99999;
	
	for(int i = 0;i < n;i++){
		final_res[i] = min(num[i] + ((left[i] < 0)? left[i] : 0), num[i] + ((right[i] < 0)? right[i] : 0));
		ans_min = min(final_res[i], ans_min);
	}
	for(auto it : final_res)
		cout << it << ' ';
	cout << '\n' << '\n';
	cout << total - ans_min;
	/* cout << "neg start : " << min_neg_start << " neg end : " << min_neg_end << '\n';
	cout << "neg ans_min : " << ans_min <<'\n'; */
	
	// for(int i = 0;i < n;i++)
		// cout << "num[i] : " << num[i] << " min subarray : " << min_subarray_pos[i] << '\n';
}