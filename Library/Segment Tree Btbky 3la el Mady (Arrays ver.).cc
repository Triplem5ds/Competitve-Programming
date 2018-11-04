int val[ N * 60 ], L[ N * 60 ], R[ N * 60 ], ptr, tree[N]; /// N * lgN
int upd(int root, int s, int e, int idx) {
	int ret = ++ptr;
	val[ret] = L[ret] = R[ret] = 0;
	if (s == e) {
		val[ret] = val[root] + 1;
		return ret;
	}
	int md = (s + e) >> 1;
	if (idx <= md) {
		L[ret] = upd(L[root], s, md, idx), R[ret] = R[root];
	} else {
		R[ret] = upd(R[root], md + 1, e, idx), L[ret] = L[root];
	}
	val[ret] = max(val[L[ret]], val[R[ret]]);
	return ret;
}
int qry(int node, int s, int e, int l, int r){
  if(r < s || e < l || !node)return 0; //Punishment Value
  if(l <= s && e <= r){
    return val[node];
  }
  int md = (s+e)>>1;
  return max(qry(L[node], s, md, l, r), qry(R[node],md+1,e,l,r));
}
