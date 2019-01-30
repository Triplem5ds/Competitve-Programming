struct gauss {
	vector<ll> setOfXors;
	void ins(ll x) {
		for (auto v : setOfXors)
			x = min(x, x ^ v);
		if (x)
			setOfXors.push_back(x);
	}
	ll qry(ll x) {
		for (auto v : setOfXors)
			x = max(x, x ^ v);
		return x;
	}
};
