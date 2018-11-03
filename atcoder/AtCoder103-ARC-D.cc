#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 200005;
const int mod = 924844033;

int main() {
#ifdef ONLINE_JUDGE
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif

	int n;
	cin >> n;
	vector<pair<ll,ll>> vp(n);
	int mask = 0;
	for (auto & x : vp) {
		cin >> x.first >> x.second;
		mask |= (1 << ((abs(x.first) + abs(x.second)) & 1));
	}

	if (mask == 3) {
		cout << "-1\n";
		return 0;
	}

	vector<ll> v;

	for (int i = 31; i >= 0; i--)
		v.push_back(1ll << i);

	if ((abs(vp[0].first) + abs(vp[0].second)) & 1 ^ 1) {
		v.push_back(1);
	}
	cout << v.size() << '\n';
	for (auto x : v)
		cout << x << ' ';
	cout << '\n';

	for (auto & x : vp) {
		for (auto val : v) {
			if (abs(x.first) >= abs(x.second)) {
				if (x.first >= 0) {
					cout << 'R';
					x.first -= val;
				} else {
					cout << 'L';
					x.first += val;
				}
			} else {
				if (x.second >= 0) {
					cout << 'U';
					x.second -= val;
				} else {
					cout << 'D';
					x.second += val;
				}
			}
		}
		assert(max(abs(x.first),abs(x.second)) == 0);
		cout << '\n';
	}

	return 0;
}
