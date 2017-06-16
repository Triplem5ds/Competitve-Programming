#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define MP make_pair
#define ll long long
int X[500005];
int Save[500005];
int ans2[500005];
vector<pair<int,ll> >V;
vector<vector<pair<int,ll> > >adj;
void dfs(int node,int p){
    if(V.size()){
        int lo=0,hi=V.size()-1;
        while(lo < hi){
            int md = lo+(hi-lo)/2;
            ll acc= V.back().S;
            if(md!=0)acc-=(V[md-1].S);
            if(acc<=X[node])hi=md;
            else lo=md+1;
        }
        int acc=V.back().S;
        if(lo!=0)acc-=V[lo-1].S;

        if(acc<=X[node]){
            Save[node]++;
            Save[V[lo].F]--;
        }
    }
    for(auto v:adj[node])if(p!=v.F){
        if(V.size()==0)
            V.push_back(MP(node,v.S));
        else
            V.push_back(MP(node,v.S+(V.back().S)));
        dfs(v.F,node);
        V.pop_back();
    }
}
int dfs2(int node, int p){
    int ans=0;
    for(auto v:adj[node])if(p!=v.F){
        ans+=dfs2(v.F,node);
    }
    ans2[node]=ans;
    ans+=Save[node];
return ans;}
int main(){
    freopen("car.in","r",stdin);
int t;scanf("%d",&t);
while (t--){
    memset(ans2,0,sizeof(ans2));
    memset(Save,0,sizeof(Save));
    int n;
    scanf("%d",&n);
    for (int i = 0; i<n; i++){
        cin >> X[i];
    }
    adj.clear();
    adj.resize(n);
    int u, v;
    ll w;
    for(int i = 0; i<n-1; i++){
        scanf("%d%d%lld",&u,&v,&w);
        u-- , v--;
        adj[u].push_back(MP(v,w));
        adj[v].push_back(MP(u,w));
    }
    dfs(0,-1);
    dfs2(0,-1);
    for(int i = 0; i < n  ; i++)
        cout << ans2[i] << (i==n-1?'\n':' ');
}
return 0;}
