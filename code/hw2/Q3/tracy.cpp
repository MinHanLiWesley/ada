#include<bits/stdc++.h>
#include<vector>
#include<iostream>
#include<algorithm>
#include <queue>
#define ll long long
using namespace std;
/*
inclue: B06303131沈家睿
*/
bool cmp2(vector<ll> &a, vector<ll> &b)
{
  if (a[0]<b[0]) return true;
  if (a[0]>b[0]) return false;

  if (a[1]<b[1]) return true;
  if (a[1]>b[1]) return false;
  return false;
}

struct cmp {
    bool operator()(vector<ll> &a, vector<ll> &b) {
      return a[1] > b[1];
    }
};

// bool cmp2(const pair<int, ll> &l,const pair<int, ll> &r) {
//     return l.first < r.first;
// }
//task : s, e, x ,p
ll solve(vector<vector<ll>> &tasks){
  int n = tasks.size();
  // //sort by start time;
  sort(tasks.begin(),tasks.end(),cmp2);
  priority_queue<vector<ll>, vector<vector<ll>>, cmp> pq;
  vector<ll> cur, job;
  ll units = 0;
  ll curtime=tasks[0][0], nextstart, s, end;
  int p = 0;
  while(p<n || !pq.empty()){
    
    s = tasks[p][0];

    //cout <<endl;
    while((p<n && tasks[p][0]==s&&curtime>=s) || pq.empty()){
      pq.push(tasks[p]);
      cout <<"push"<<tasks[p][0]<<','<<tasks[p][1]<<','<<tasks[p][2]<<','<<tasks[p][3]<<endl;
      p++;
    }
    //cout <<"p: "<<p<<endl;
    job = pq.top();
    pq.pop();
    cout <<"job"<< job[0]<<','<<job[1]<<','<<job[2]<<','<<job[3]<<endl;

    if (p<n)
      end = min(tasks[p][0]-1, job[1]);
    else
      end = job[1];

    curtime = (job[0]>curtime)? job[0]: curtime;

    if (end-curtime+1 >= job[2]){
      units+= job[2];
      curtime += job[2];
    }
    else{
      units += end-curtime+1;
      job[2] -= end-curtime+1;
      curtime += end-curtime+1;
      //cout << job[2]<<endl;
      if (job[2]>0)
        pq.push(job);
    }
    cout << curtime<<' '<<end<<endl;
    //cout <<"job"<< job[0]<<','<<job[1]<<','<<job[2]<<','<<job[3]<<endl;

    while(!pq.empty()&& pq.top()[1]<curtime){
      cout <<"k"<<endl;
      pq.pop();
    }
  }

  cout << units << endl;

  return 0;

}

int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  cin >> n;
  vector<vector<ll>> tasks(n, vector<ll>(4));
  ll s,e,x,p;
  for (int i =0; i<n; ++i){
    cin >> s >> e >> x >>p;
    tasks.at(i) = {s,e,x,p};
  }

  solve(tasks);

  return 0;
}