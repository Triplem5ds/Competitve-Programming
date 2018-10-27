#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 100005;
const int mod = 1000000007;

/*
 * okay operation 2 basically says that we sort the integers
 * on odd and even positions independently from each other
 * now to think about the operation 1 takes an integer and
 * will swap it until it goes into it's position
 * so i want to use operation 2 to make the sum of differences between
 * the sorted array and the real array as small as possible
 */

vector<int>odds,evens;
vector<int> compress(vector<int> a){
	vector<int> ord = a;
	sort(ord.begin(),ord.end());
	for(auto & x : a)
		x = lower_bound(ord.begin(),ord.end(), x) - ord.begin();
	return a;
}
int main() {
#ifdef ONLINE_JUDGE
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif

	int n;	cin >> n;
	vector<int>a(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];

	a = compress(a);

	for(int i = 0; i < n; i++)
		if(i&1)odds.push_back(a[i]);
		else evens.push_back(a[i]);

	sort(odds.begin(),odds.end());
	sort(evens.begin(),evens.end());
	a.clear();
	int ans = 0;
	for(int i = 0; i < n; i++){
		if(i&1)a.push_back(odds[i>>1]);
		else a.push_back(evens[i>>1]);
		if((i&1)!=(a[i]&1))ans++;
	}

	cout << (ans>>1) <<'\n';


	return 0;
}
