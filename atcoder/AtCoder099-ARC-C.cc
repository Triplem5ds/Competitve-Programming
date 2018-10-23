#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 705;
const int mod = 1e9 + 7;

/*
 * IDEA : if u and v has no edge between them they can't be in the same set
 * so i build a complement graph and check that it's bipartite and for every component
 * in the graph i can add either the white or the black nodes
 * then i minimize calc(i) + calc(n-i)
 * O(N^2)
 */

bool mat[N][N];
int n, m;
int cntParity[2];
void kill(){cout << -1 << '\n';	exit(0);}
vector<int> g[N];
int col[N];
void dfs(int x, int c){
	if(col[x] != -1){
		if(col[x] != c)
			kill();
		return;
	}
	col[x] = c;
	cntParity[c]++;
	for(auto v : g[x])
		dfs(v,1-c);
}
int calc(int x){return x * (x-1) / 2;}
int main(){
#ifdef ONLINE_JUDGE
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif // ONLINE_JUDGE

	cin >> n >> m;

	for(int i = 0, u, v; i < m; i++){
		cin >> u >> v;
		mat[u][v] = mat[v][u] = 1;
	}

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(i != j && !mat[i][j])
				g[i].push_back(j);

	vector<pair<int,int>> vp;	memset(col,-1,sizeof col);

	for(int i = 1; i <= n; i++)
		if(col[i] == -1){
			cntParity[0] = cntParity[1] = 0;
			dfs(i,0);
			vp.push_back({cntParity[0], cntParity[1]});
		}

	vector<int> vals = {0};

	for(auto x : vp){

		vector<int>nxt;

		for(auto v : vals)
			nxt.push_back(v + x.first),
			nxt.push_back(v + x.second);

		sort(nxt.begin(), nxt.end());
		nxt.resize(unique(nxt.begin(), nxt.end()) - nxt.begin());
		vals = nxt;
	}

	int ans = n * n;

	for(auto v : vals)
		ans = min(ans, calc(v) + calc(n - v));

	cout << ans << '\n';

	return 0;
}
