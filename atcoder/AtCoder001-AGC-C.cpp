#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 2e3 + 5;
const int mod = 998244353;

/*
 * thinking about it
 * if dist(u,v) > k they can't be in the same graph
 * however if dist(u,v) <= k they can be in the same graph
 * so now it just becomes a problem of finding the maximal clique
 * in a graph where there is an edge between u and v if dist(u,v) <= k
 * one problem NP-Complete :"D this is an O(2 ^ N)
 * lol a really easier solution would be to try all the diameters then
 * choose all nodes with max(dist[u][x], dist[v][x]) <= k
 * so let's iterate on all nodes u and get nodes where dist[u][x] <= k
 * now iterate over them i need to know which nodes in the list have
 * distance > k this an O(N^3) solution
 * so now i have Set(u) and Set(v) i have to find the maximum SetIntersection
 * i can speed it up to O(N^3/32) using BIT Sets let's try it XD
 * note my solution passed in exactly 71ms not sure what to think of that
 */

bitset<2005> bt[N];
vector<int>adj[N];
vector<int>to[N];
int cnt = 0;
void dfs(int u, int p, int master, int lft){
	cnt++;
	bt[master][u] = 1;
	if(lft == 0){
		to[master].push_back(u);
		return;
	}
	for(auto v : adj[u])
		if(v != p)
			dfs(v,u,master,lft-1);
}
int main() {
#ifdef ONLINE_JUDGE
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif

	int n, k;
	cin >> n >> k;

	for(int i = 1, u, v; i < n; i++){
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int mn = n;
	for(int i = 1; i <= n; i++){
		cnt = 0;
		dfs(i,i,i,k);
		mn = min(mn,cnt);
	}

	if(mn == n){
		cout << 0 << '\n';
		return 0;
	}

	int ans = 0;
	for(int i = 1; i <= n; i++)
		for(auto j : to[i])if(i < j){
//			cout << i << ' ' << j << ' ' << ((bt[i]&bt[j]).count()) << '\n';
			ans = max(ans,(int) (bt[i]&bt[j]).count());
		}
	cout << n-ans << '\n';



	return 0;
}
