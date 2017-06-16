#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define MP make_pair
#define TripleM ios_base::sync_with_stdio(0);cin.tie(0);
#define clr(x,y) memset(x,y,sizeof(x,y))
#define F first
#define S second
#define pb push_back
#define sz size()
typedef long long ll;
ll N,E;
vector<vector<pair<ll,ll> > > adj;
vector<ll>ans;
void dfs(ll node,ll time){
    if(adj[node].size()==0)ans.push_back(time);
    sort(adj[node].begin(),adj[node].end());
    for(int i=0;i<adj[node].size();i++){
        pair<ll,ll>child=adj[node][i];
        if(i==0)
            dfs(child.S,time+child.F);
        else
            dfs(child.S,time+adj[node][0].F+(2*(child.F-adj[node][0].F)));
    }
}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        scanf("%I64d",&N);
        E=(N-1);
        adj.clear();
        ans.clear();
        adj.resize(N+1);
        for(ll i=0;i<E;i++){
            ll P,C;scanf("%I64d%I64d",&P,&C);
            adj[P].push_back(MP(C,i+2));
        }dfs(1,0);
        sort(ans.begin(),ans.end());

        long long Q;scanf("%I64d",&Q);
        while(Q--){
            ll x;scanf("%I64d",&x);
            int lo=0,hi=ans.size();
            while(lo!=hi){
                int mid=(lo+hi)/2+1;
                if(ans[mid-1]>x)hi=mid-1;
                else lo=mid;
            }
            printf("%I64d\n",hi);
        }

    }
return 0;}
