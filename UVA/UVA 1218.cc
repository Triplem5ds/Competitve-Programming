/*
    dp[node][state];
    state 0 : the node before me is a server
    state 1 : the node before me isn't a server but it's covered by a server
    state 2 : the node before me is a server but it's not covered by a server
*/
#include <bits/stdc++.h>

using namespace std;

using ii = pair<int,int>;
using ll = long long;

inline void fmin(int &x, int y){if(x > y)x=y;}
inline void fmax(int &x, int y){if(x < y)x=y;}

const int mod = 1e9 + 7;
const int N = 1e4+5;

vector<int>adj[N];
int dp[N][3], n;
int vis[N][3], cas;
int solve(int node, int p, int state){

    int &ret = dp[node][state];
    if(vis[node][state] == cas)
        return ret;
    vis[node][state] = cas;
    ret = N;
    ///put this node as a server
    if(state != 1 || node == 1){
        int sum1 = 0;
        for(auto v : adj[node])if(v!=p){
            sum1 += solve(v,node,0);
        }
        ret = min(ret,1 + sum1);
    }
//    if(node==1)cout << ret << '\n';

    ///don't put this node as a server
    if(state != 2){
        if(state!=1||(adj[node].size()-(node!=p) > 0)){
        int sum2 = 0;
        for(auto v : adj[node])if(v != p){
            sum2 += solve(v,node,state+1);
        }
        ret = min(ret, sum2);}
    }

    return ret;
}
int main(){
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE

    while(cin >> n){
        for(int i = 0; i <= n; i++)adj[i].clear();
        for(int i = 0; i <  n - 1; i++){
            int u, v;   cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }   ++cas;
        cout << solve(1,1,1) << '\n';
        int skip;   cin >> skip;
        if(~skip)continue;
        break;
    }


    return 0;
}
