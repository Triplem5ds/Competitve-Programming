
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod=1e9+7;
ll dp[1005][1005];
ll a,b;
ll solve(ll n,ll k){
    if(n==a)return k==b;
    if(k>b)return 0;
    if(dp[n][k]!=-1)return dp[n][k];
      return dp[n][k]=(solve(n+1,k)*k+solve(n+1,k+1)*(b-k))%mod;
}
int main(){
    freopen("galactic.in","r",stdin);
    int t;cin>>t;
    while(t--){
            memset(dp,-1,sizeof(dp));
        cin>>a>>b;
        if(b>a){
            puts("0");
            continue;
        }
        cout<<solve(0,0)<<'\n';
    }
}
