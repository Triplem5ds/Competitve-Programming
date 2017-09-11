#include "bits/stdc++.h"
using namespace std;

#define F first
#define S second
#define mp(x, y) make_pair(x, y)
#define ios ios_base::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define all(x) x.begin(), x.end()
#define fill(a, n, x) fill(a, a + n, x);
#define max(x, y) (x > y? x : y)
#define min(x, y) (x < y? x : y)
#define rall(x) x.rbegin(), x.rend()

typedef long long ll;
typedef pair<int, int> ii;
typedef long double db;
typedef vector<int> vi;

const int N = 1e3 + 5;
const ll mod = 1e9 + 7;

int dist[50005], a[5005], n;

int main(){

	scanf("%d", &n);

	for(int i = 0; i < n; i++)
		scanf("%d", a + i);

	fill(dist, a[0], (INT_MAX/2 - 1));

	dist[0] = 0;

	set<ii>st;
	st.insert(ii(0, 0));

	while(st.size()){

		ii cur = *st.begin();
		st.erase(cur);

		for(int i = 0; i < n; i++){

			int x = cur.F + a[i];
			int y = (cur.S + a[i])%a[0];

			if(x < dist[y]){
				st.erase(ii(dist[y], y));
				dist[y] = x;
				st.insert(ii(dist[y], y));
			}


		}

	}

	int q; scanf("%d", &q);

	while(q--){

		int x; scanf("%d", &x);

		puts(dist[x%a[0]] <= x ? "TAK" : "NIE");



	}

}
