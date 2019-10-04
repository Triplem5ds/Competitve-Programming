/*
 Problem Link:https://www.codechef.com/APRIL19B/problems/SUBREM
 Concepts Used: DFS,greedy approach
 
 */



#include<bits/stdc++.h>
typedef long long int lli;
using namespace std;
const long long int INF = 0x3f3f3f3f;
lli n,x;

pair<lli,lli> maxi(pair<lli,lli> a,pair<lli,lli> b){

        if(a.first > b.first) return a;
        else if(b.first > a.first) return b;
        else{

             if(a.second < b.second) return a;
             else return b;

        }

}


void dfs(lli cur,auto tree,lli& ind,auto& order,auto& wt ,auto& subsum,auto &subsize,auto& v,auto& profit){

     v[cur] = 1;
     order[ind] = cur;
     ind++;
     subsum[cur] = wt[cur];
     subsize[cur] = 1;


     lli negsum = 0;
     lli penality = 0;
       lli childpro = 0;
     lli childpen = 0;
     for(auto i: tree[cur]){
          if(v[i] !=1){
            dfs(i,tree,ind,order,wt,subsum,subsize,v,profit);
            subsum[cur]+=subsum[i];
            subsize[cur]+=subsize[i];
            if(subsum[i] < -x) { negsum+=subsum[i];
                penality+=x;

            }
            childpro += profit[i].first;
            childpen += profit[i].second;

          }

     }

    profit[cur] = maxi(make_pair(-x,x),make_pair(subsum[cur],0));
    profit[cur] = maxi(profit[cur],make_pair(wt[cur] + childpro,childpen));
    if(negsum != 0) profit[cur] = maxi(profit[cur],make_pair(subsum[cur] - negsum - penality,penality));


}

lli dp[100005];

int main() {

        ios_base::sync_with_stdio(false);
        cin.tie(NULL);


  int t;
  cin >> t;

  while(t--){
      cin >> n >> x;
      vector<lli> tree[n+1];
      vector<lli> subsum(n+1);
      vector<lli> v(n+1);
      vector<lli> subsize(n+1);
      vector<lli> wt(n+1);
      vector<lli> order(n+1);
       vector<pair<lli,lli> > profit(n+1,{0,0});
      memset(dp,-1,sizeof(dp));
      for(lli i =1;i<=n;i++) cin >> wt[i];

      for(lli i = 0;i<n-1;i++){
              lli x,y;
              cin >> x >> y;
       tree[x].push_back(y);
       tree[y].push_back(x);
      }

     lli ind  =1;
     dfs(1,tree,ind,order,wt,subsum,subsize,v,profit);
    lli total = 0;
    lli i = 1;

    lli ans = profit[1].first;
    cout<<ans<<endl;


  }
}
