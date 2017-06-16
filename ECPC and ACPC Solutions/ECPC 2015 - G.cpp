#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
ll OO = 1e9+9 ;
ll cost[100005] ;
struct s
{
    ll n , wis ;
    bool operator <(const s &z) const
    {
        return cost[n] > cost[z.n] ;
    }
};
struct f
{
    ll c , w;
};
unordered_map < int , unordered_map<int , f> > ma ;
vector < vector<int> > a;
ll n , m , k ;
bool dijkstra(int maxi)
{
    for(int i = 1 ; i <= n+5 ; i++)
        cost[i] = OO;
    priority_queue<s> q;
    cost[1] = 0 ;
    q.push({1,0});
    while(q.size())
    {
        s ne = q.top();
        q.pop();
        if(ne.n == n) break ;
        for(int i = 0 ; i < a[ne.n].size() ; i++)
        {
            int j = a[ne.n][i] ;
            if(cost[j] > cost[ne.n]+ma[ne.n][j].c && max(ne.wis,ma[ne.n][j].w) <= maxi)
            {
                cost[j] = cost[ne.n]+ma[ne.n][j].c;
                q.push({j,max(ne.wis,ma[ne.n][j].w)});
            }
        }
    }
    if(cost[n] < k) return 1;
    else return 0;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--)
    {
        ma.clear();
        a.clear();
        int s = 0 , e = 0 ;
        cin >> n >> m >> k ;
        a.resize(n+5);
        for(int i = 0 ; i < m ; i++)
        {
            int u ,f,o,p ;
            cin>>u>>f>>o>>p;
            ma[u][f].c = o ;
            ma[u][f].w = p ;
            ma[f][u].c = o ;
            ma[f][u].w = p ;
            e = max(e,p);
            a[f].push_back(u);
            a[u].push_back(f);
        }
        bool ans = 0 ;
        while(s <= e)
        {
            int mid = s+(e-s)/2 ;
            if(dijkstra(mid))ans = 1 , e = mid-1 ;
            else s = mid+1;
        }
        if(!ans) cout << "-1\n";
        else cout << s << "\n" ;
    }
}
