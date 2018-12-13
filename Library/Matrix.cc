struct Matrix {
	ll a[105][105];
	int n;
	Matrix(int N) {
		n = N;
		memset(a, 0, sizeof a);
	}
	Matrix operator *(const Matrix & o) const {
		Matrix ret(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					ret.a[i][j] = (ret.a[i][j] + a[i][k] * o.a[k][j] % mod)
							% mod;
		return ret;
	}
	void addEdge(int u, int v) {
		a[u][v]++;
	}
	Matrix I() {
		Matrix ret(n);
		for (int i = 0; i < n; i++)
			ret.a[i][i] = 1;
		return ret;
	}
	Matrix fast(ll p) {
		if (!p)
			return I();
		Matrix ret = fast(p >> 1);
		ret = ret * ret;
		if (p & 1)
			ret = ret * (*this);
		return ret;
	}

};
