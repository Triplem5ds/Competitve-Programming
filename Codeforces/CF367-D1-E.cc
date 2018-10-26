#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 1e5 + 5;
const int mod = 1e9 + 7;

/*
 * okay so a little observation
 * n * m <= 10 ^ 5 that means that
 * min(n,m) is always <= 320
 * so i have an O(n * m * m) solution if m is the minimum
 * and if n is the minimum the answer is 0
 * now how to turn O(n * m * m) to O(n * n * m)
 * dp[i][l][r] where i is in the l->r interval
 */

int n, m, x;

void add(int &x, int y){x += y; if(x >= mod)x -= mod;}
int factN;
vector<int>dp[320][320][2];
int solve(int idx, int cur, int take , bool f){
	if(take > n || (idx>x && !f))
		return 0;
	if(idx==m){
		if(take != n || cur)
			return 0;
		return factN;
	}
	int &ret = dp[cur][take][f][idx];
	if(~ret)
		return ret;
	ret = solve(idx+1,cur,take,f);
	add(ret,solve(idx+1,cur+1,take+1,f|(idx==x)));
	add(ret,solve(idx+1,cur,take+1,f|(idx==x)));
	if(cur)
		add(ret,solve(idx+1,cur-1,take,f));
	return ret;
}

int main() {

	cin >> n >> m >> x; factN = 1;	--x;
	if(n > m){
		cout << 0 << '\n';
		return 0;
	}
	for(int i = 2; i <= n; i++)
		factN = factN * 1ll * i % mod;

	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			for(int k = 0; k < 2; k++)
				dp[i][j][k].assign(m,-1);

	cout << solve(0,0,0,0) << '\n';

	return 0;
}
