#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 5e5+5;
const int mod = 1e9 + 7;

/*
    IDEA
    if i walk on the array from left to right
    for each x if |(j,x)| >= min(j,x) and x <= i
    so |(j,i)| >= min(j,i) so once this state opens
    i don't need to open it again

*/

int n, k, a[N];
int dp[N], tdp[N], dp2[N], lvl[N], mx[N];
vector<int>adj[N];
void dfs(int u, int p){
    mx[u] = lvl[u];

    vector<pair<int,int>>to;
    vector<pair<int,int>>med;
    vector<pair<int,int>>path;
    for(auto v : adj[u])if(v != p){

        lvl[v] = lvl[u] + 1;
        dfs(v,u);
        mx[u] = max(mx[u], mx[v]);
        dp[u] = max(dp[u], dp[v]);
        tdp[u] = max(tdp[u], tdp[v]);
        dp2[u] = max(dp2[u], dp2[v]);

        to.emplace_back(mx[v], v);
        path.emplace_back(dp[v],v);
        med.emplace_back(tdp[v], v);

    }

    dp[u] = max(dp[u], mx[u] - lvl[u]);

    sort(to.rbegin(),to.rend());
    sort(path.rbegin(),path.rend());
    sort(med.rbegin(), med.rend());

    if(to.size() >= 2){

        dp[u] = max(dp[u], to[0].first + to[1].first - 2 * lvl[u]);
        dp2[u] = max(dp2[u], path[0].first + path[1].first);



        if(path[0].second != to[0].second)
            tdp[u] = max(tdp[u], path[0].first + to[0].first);
        if(path[0].second != to[1].second)
            tdp[u] = max(tdp[u], path[0].first + to[1].first);
        if(path[1].second != to[0].second)
            tdp[u] = max(tdp[u], path[1].first + to[0].first);
        if(path[1].second != to[1].second)
            tdp[u] = max(tdp[u], path[1].first + to[1].first);

        if(med[0].second != to[0].second)
            dp2[u] = max(dp2[u], med[0].first + to[0].first - 2 * lvl[u]);
        if(med[0].second != to[1].second)
            dp2[u] = max(dp2[u], med[0].first + to[1].first - 2 * lvl[u]);
        if(med[1].second != to[0].second)
            dp2[u] = max(dp2[u], med[1].first + to[0].first - 2 * lvl[u]);
        if(med[1].second != to[1].second)
            dp2[u] = max(dp2[u], med[1].first + to[1].first - 2 * lvl[u]);

    }

    if(to.size() >= 3){

        vector<int>a,b;
        for(int i = 0; i < min((int)to.size(),6); i++)
            b.push_back(to[i].second),
            a.push_back(path[i].second);

        for(auto v : a)
            for(auto x : b)
                for(auto y : b)if(x != y && v != x && v != y)
                    dp2[u] = max(dp2[u], dp[v] + mx[x] + mx[y] - 2 * lvl[u]);

        tdp[u] = max(tdp[u], to[0].first + to[1].first - 2 * lvl[u] + to[2].first);
    }
    if(to.size() >= 4){
        dp2[u] = max(dp2[u], to[0].first + to[1].first + to[2].first + to[3].first - 4 * lvl[u]);
    }



}
int main(){
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE

    cin >> n >> k;

    for(int i = 0; i < n - 1; i++){
        int u, v;   cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,1);


    if(k == 1)
        cout << 2 * (n - 1) - dp[1] + 1 << '\n';
    else
        cout << 2 * (n - 1) - max(dp[1]-1,dp2[1]-2)<< '\n';


    return 0;
}
