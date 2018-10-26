/*
 * some Observations for
 * increasing sequence of Ls the answer is increasing
 * and the farthest leaf for every node doesn't change
 * first let's find the farthest leaf
 * getting the farthest leaf inside my sub tree is easy
 * it's dp[u] = max(dp[v] + w) where v is connected to u
 * getting the max out of it's subtree is check your parent
 * if your parent your answer is either ans[p] + w
 * or your parent's max or second max if you are equal to max
 * so i just noticed that q <= 50
 * now i have an idea if i dfs from node with the smallest dp[i]
 * so i can basically for each node binary search the highest parent it can reach
 * and do a little partial sum and that's it
 * O(qNlgN)
 */

#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 1e5 + 5;
const int mod = 998244353;

ll maxInside[N], secondMax[N];
ll maxOutside[N];

vector<pair<int,int>>adj[N];
int n, q, ans, t;
ll L;
void dfs0(int u, int p){

	for(auto e : adj[u])if(e.first != p){
		int v = e.first;
		int w = e.second;
		dfs0(v,u);
		ll to = w + maxInside[v];
		if(to > maxInside[u]){
			secondMax[u] = maxInside[u];
			maxInside[u] = to;
		}	else{
			secondMax[u] = max(secondMax[u], to);
		}
	}

}
void dfs1(int u, int p){
	for(auto e : adj[u])if(e.first != p){
		int v = e.first;
		int w = e.second;
		ll to = w + maxOutside[u];
		if(maxInside[v] + w != maxInside[u])
			to = max(to, maxInside[u] + w);
		else
			to = max(to, secondMax[u] + w);
		maxOutside[v] = to;
		dfs1(v,u);
	}
}
int in[N];
int sv[N];
ll val[N];
int sum[N];
void dfs(int u, int p){
	in[++t] = u;
	sv[u] = 0;

	int lo= 1, hi = t;
//	for(int i = 1; i <=t; i++)
//		cout << val[in[i]] + L << ' ';
//	cout << '\n';
	while(lo < hi){
		int md = lo + (hi-lo)/2;
		if(val[in[md]] + L >= val[u])
			hi=md;
		else
			lo=md+1;
	}

	sv[in[lo]]++;
	sum[u] = 1;

	for(auto v : adj[u])
		if(v.first != p){
			dfs(v.first,u);
			sum[u] += sum[v.first];
		}

	ans = max(ans, sum[u]);
	sum[u] -= sv[u];
	t--;
}
int main() {
#ifdef ONLINE_JUDGE
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif

	cin >> n;

	for(int i = 0, u, v, w; i < n-1; i++){
		cin >> u >> v >> w;
		adj[u].push_back(ii(v,w));
		adj[v].push_back(ii(u,w));
	}

	int r = 0;

	for(int i = 1; i <= n; i++)
		if(adj[i].size() == 1)
			r = i;

	assert(r);

	dfs0(r,r);
	dfs1(r,r);

	for(int i = 1; i <= n; i++)
		val[i] = max(maxInside[i], maxOutside[i]);

//	for(int i = 1; i <= n; i++)
//		cout << max(maxInside[i],maxOutside[i]) << '\n';

	pair<ll, int> p = {val[1], 1};

	for(int i = 2; i <= n; i++)
		p = min(p, pair<ll,int>{val[i], i});

	cin >> q;
	while(q--){
		cin >> L ; ans = t = 0;
		dfs(p.second,p.second);
		cout << ans << '\n';
	}

	return 0;
}
