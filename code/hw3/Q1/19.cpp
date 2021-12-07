#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define ll long long
#define MAXN 1<<18

using namespace std;

//非常感謝 b06303131 沈家睿 的幫忙!

ll N;
vector<vector<ll>> adjL(MAXN, vector<ll>({}));
vector<int> visited(MAXN, 0);
vector<ll> visRecord;
vector<ll> parentRecord(MAXN, -1);
vector<ll> diameter;
vector<ll> branch(MAXN, 0);
vector<ll> inversebranch(MAXN, 0);
queue<ll> q;
ll farthestCity, maxDist;

ll BFS(ll start, int flag){ //flag: 是否為第一次找直徑
    visited[start] = 1;
    q.push(start);
    ll len, idx, num;
    ll dist = 0;
    while(!q.empty()){
        num = q.size();
        for(int i = 0; i < num; i++){
            idx = q.front(); q.pop();
            len = adjL[idx].size();
            for(int j = 0; j < len; j++){
                if(!visited[adjL[idx][j]]){
                    visited[adjL[idx][j]] = 1;
                    q.push(adjL[idx][j]);
                }
            }
            visRecord.push_back(idx);//caution
        }
        dist++;
    }
    if(dist > maxDist){
        maxDist = dist;
        farthestCity = idx;
    }
    len = visRecord.size();
    for(int i = 0; i < len; i++)
        visited[visRecord[i]] = 0;
    
    if(flag){
        visRecord.clear(); dist = 0;
        visited[farthestCity] = 1;
        q.push(farthestCity);
        while(!q.empty()){
            num = q.size();
            for(int i = 0; i < num; i++){
                idx = q.front(); q.pop();
                len = adjL[idx].size();
                for(int j = 0; j < len; j++){
                    if(!visited[adjL[idx][j]]){
                        visited[adjL[idx][j]] = 1;
                        q.push(adjL[idx][j]);
                        parentRecord[adjL[idx][j]] = idx;
                        // printf("===idx: %lld\n", idx);
                    }
                }
                visRecord.push_back(idx);//caution
            }
            dist++;
        }
        if(dist >= maxDist){
            maxDist = dist;
            farthestCity = idx;
        }
        len = visRecord.size();
        for(int i = 0; i < len; i++)
            visited[visRecord[i]] = 0;
    }
    return dist;
}

int main(){
    scanf("%lld", &N);
    ll a, b;
    for(int i = 0; i < N-1; i++){
        scanf("%lld %lld", &a, &b);
        adjL[a].push_back(b);
        adjL[b].push_back(a);
    }
    maxDist = -1; farthestCity = -1;
    ll dist = BFS(1, 1), cur = farthestCity;
    for(int i = 0; i < dist; i++){
        // printf("cur: %lld\n", cur);
        if(cur != -1){
            diameter.push_back(cur);
            cur = parentRecord[cur];
            // visited[cur] = 1;
        }
    }
    // for(int i = 0; i < dist; i++)
    //     printf("===diameter[%d] = %lld\n", i, diameter[i]);
    ll len, tmpdist; dist = -1;
    for(int i = 0; i < maxDist; i++){
        len = adjL[diameter[i]].size();
        if(len > 2){
            branch[diameter[i]] = BFS(diameter[i], 0);
            if(branch[diameter[i]] < dist)
                branch[diameter[i]] = dist;
            dist = branch[diameter[i]];
        }
    }
    dist = -1;
    for(int i = maxDist-1; i >= 0; i--){
        inversebranch[diameter[i]] = branch[diameter[i]];
        if(inversebranch[diameter[i]] < dist)
            inversebranch[diameter[i]] = dist;
        dist = inversebranch[diameter[i]];
    }
    // for(int i = 0; i < maxDist; i++){
    //     printf("===Branch[%d] = %lld\n===InverseBranch[%d] = %lld\n", i, branch[i], i, inversebranch[i]);
    // }
    ll ans=10000000000, tmpans;
    for(int i = 0; i < maxDist; i++){
        tmpans = max({branch[i]+i-1, inversebranch[i]+(maxDist-i-1), (branch[i]+i-1+1)/2 + (inversebranch[i]+(maxDist-1-i)+1)/2 + 1});
        ans = min(ans, tmpans);
    }
    printf("%lld\n", ans);

    
    return 0;
}