#include<bits/stdc++.h>
using namespace std;
#define lp(x,n) for(int x=0;x<n;x++)
#define OO 1e9
typedef long long ll;
int n;
int main(){
    cin>>n;
    vector<vector<ll> >adj(n,vector<ll>(n));
    lp(i,n)lp(j,n)cin>>adj[i][j];
    vector<bool>vis(n,0);
    vector<ll>ans(n),rev(n);
    for(int i=n-1;i>=0;i--)cin>>rev[i];
    lp(i,n){
        int tmp=rev[i]-1;
        vis[tmp]=1;
        ll res=0;
        lp(j,n)lp(k,n)adj[j][k]=min(adj[j][k],adj[j][tmp]+adj[tmp][k]),res+=(adj[j][k]*(vis[j]&vis[k]));
        ans[n-i-1]=res;
    }
    for(ll i:ans)cout<<i<<' ';



return 0;}
