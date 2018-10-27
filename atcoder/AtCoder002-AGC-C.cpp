#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 2e3 + 5;
const int mod = 1000000007;

/*
 * i can't really think up top
 * however i can think down low
 * let's say all of the pieces at the beginning are
 * apart i can connect pieces i and i + 1 if and only if
 * their size[i] + size[j] >= L
 * and it doesn't matter the order of connections
 * so for every string i need it's left most index it's right most index
 * and it's total
 */

set<pair<ll,pair<int,int>>>st;

map<int, pair<int,ll>>getByL;	///L : (R,val)
map<int, pair<int,ll>>getByR;

int main() {
#ifdef ONLINE_JUDGE
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif

	int n, L;

	cin >> n >> L;

	vector<int>a(n);

	for(int i = 0; i < n; i++){
		cin >> a[i];
		if(i)
			st.insert({a[i]+a[i-1], make_pair(i-1,i)});
		getByL[i] = getByR[i] = {i,a[i]};
	}
	vector<int>ans;
	while(st.size() && st.rbegin()->first >= L){
		auto it = *st.rbegin();
		st.erase(it);
		ll val = it.first;
		int L = it.second.first, R = it.second.second;
		ans.push_back(L);
		///XABY
		///L->the R of Range A
		///R->the L of Range B
		/// Delete Range B with Range Y
		if(getByL.upper_bound(R) != getByL.end()){
			auto nxt = (*getByL.upper_bound(R)).second;
			st.erase({nxt.second+getByL[R].second,make_pair(getByL[R].first,getByR[nxt.first].first)});
		}
		/// Delete Range A with Range X
		if(getByR.find(L) != getByR.begin()){
			auto prv = (*(--getByR.find(L))).second;
			st.erase({prv.second+getByR[L].second,make_pair(getByL[prv.first].first,getByR[L].first)});
		}
		pair<ll, pair<int,int>> newRange = {val, make_pair(getByR[L].first,getByL[R].first)};
		getByL.erase(getByR[L].first);
		getByR.erase(L);
		getByR.erase(getByL[R].first);
		getByL.erase(R);
		getByL[newRange.second.first] ={newRange.second.second,newRange.first};
		getByR[newRange.second.second] ={newRange.second.first,newRange.first};
		if(getByL.find(newRange.second.first) != getByL.begin()){
			auto prv = (*(--getByL.find(newRange.second.first))).second;
			st.insert({prv.second+newRange.first,make_pair(prv.first,newRange.second.first)});
		}
		if(getByR.upper_bound(newRange.second.second) != getByR.end()){
			auto nxt = (*(getByR.upper_bound(newRange.second.second))).second;
			st.insert({nxt.second+newRange.first,make_pair(newRange.second.second,nxt.first)});
		}
	}
	if(st.size()){
		cout << "Impossible\n";
		return 0;
	}
	cout << "Possible\n";
	reverse(ans.begin(),ans.end());

	for(auto x : ans)
		cout << x+1 <<'\n';



	return 0;
}
