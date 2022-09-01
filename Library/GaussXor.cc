struct gauss {
	vector<ll> setOfXors;
	void ins(ll x) {	///Add X to Gaussian Basis
		for (auto v : setOfXors)
			x = min(x, x ^ v);
		if (x)
			setOfXors.push_back(x);
	}
	ll qry(ll x) { ///Get maximum subsequence XOR ^ x
		for (auto v : setOfXors)
			x = max(x, x ^ v);
		return x;
	}
};
