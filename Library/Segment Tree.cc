#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int t[N << 2];
int lz[N << 2];
void push(int node, int s, int e) {
	if (s != e) {
	}
}
void mrg(int a, int b) {

}
void build(int node, int s, int e) {
	if (s == e) {
		return;
	}
	int md = (s + e) >> 1;
	build(node << 1, s, md);
	build(node << 1 | 1, md + 1, e);
	t[node] = mrg(t[node << 1], t[node << 1 | 1]);
}
void upd(int node, int s, int e, int l, int r, int v) {
	push(node, s, e);
	if (r < s || e < l) {
		push(node, s, e);
		return;
	}
	int md = (s + e) >> 1;
	upd(node << 1, s, md, l, r, v);
	upd(node << 1 | 1, md + 1, e, l, r, v);
	t[node] = mrg(t[node << 1], t[node << 1 | 1]);
}
void updI(int node, int s, int e, int idx, int v) {
	if (s == e) {
		return;
	}
	int md = (s + e) >> 1;
	if (idx <= md)
		updI(node << 1, s, md, idx, v);
	else
		updI(node << 1 | 1, md + 1, e, idx, v);
	t[node] = mrg(t[node << 1], t[node << 1 | 1]);
}
int qry(int node, int s, int e, int l, int r) {
	push(node, s, e);
	if (l <= s && e <= r) {
		return t[node];
	}
	int md = (s + e) >> 1;
	if (r <= md)
		return qry(node << 1, s, md, l, r);
	else if (l > md)
		return qry(node << 1 | 1, md + 1, e, l, r);
	auto x = qry(node << 1, s, md, l, r);
	auto y = qry(node << 1 | 1, md + 1, e, l, r);
	return mrg(x, y);
}
int main() {

}
