#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 1e6 + 5;
const int mod = 998244353;

int lvl[N];
int par[N][22];
int lca(int u, int v){
	if(lvl[u] > lvl[v])
		swap(u,v);
	int d = lvl[v] - lvl[u];
	for(int i = 0; i < 22; i++)
		if(d>>i&1)
			v = par[v][i];
	if(u==v)return u;
	for(int i = 21; i >= 0; --i)
		if(par[u][i] != par[v][i])
			u = par[u][i], v = par[v][i];
	return par[v][0];
}
int main() {
#ifdef ONLINE_JUDGE
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif

	lvl[2] = lvl[3] = lvl[4] = 1;
	par[2][0] = par[3][0] = par[4][0] = 1;
	int n = 4;
	int q;	cin >> q;
	int out = 2;
	int x=2,y=3;
	while(q--){
		int k;	cin >> k;
		lvl[n+1] = lvl[n+2] = lvl[k] + 1;	n+=2;
		par[n-1][0] = par[n][0] = k;
		for(int i = 1; i < 22; i++){
			par[n-1][i] = par[par[n-1][i-1]][i-1];
			par[n][i] = par[par[n][i-1]][i-1];
		}
		if(lvl[n] + lvl[x] - 2 * lvl[lca(n,x)] > out)
			y=n,out++;
		if(lvl[n] + lvl[y] - 2 * lvl[lca(n,y)] > out)
			x=n,out++;
		cout << out << '\n';
	}

	return 0;
}
