#include <bits/stdc++.h>
using namespace std;

/*
  we walk on the v line as if it is an axis if we collide with a worker with a certain skill we update his range
  from v to r as when we query we if the range intersects at any point of those we can take the worker
  and when we collide with an L we erase that worker all done using segment tree and lazy propagation
  then we have our answer the two l and r that we need we just need to find check if these ranges fit.

*/


const int N = 3e5 + 5;
struct worker{
  int l, r, v;

  bool operator < (const worker x) const{
    if(l == x.l)return r < x.r;
    return l < x.l;
  }

}a[N];
int n;
istream &operator >> (istream &is, worker &x){
  return is >> x.l >> x.v >> x.r;
}
pair<int, int> tree[4*N];
int laz[4*N];
void build(int node, int s, int e){
  if(s == e){
    tree[node].second =  s;
    return;
  }
  int md = (s + e) >> 1;
  build(node << 1, s, md);
  build(node << 1 | 1, md + 1, e);
  tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
}
void laz_out(int node, int s, int e){
  tree[node].first += laz[node];
  if(s != e){
    laz[node << 1] += laz[node];
    laz[node << 1 | 1] += laz[node];
  }
  laz[node] = 0;
}
void update(int node, int s, int e, int l, int r, int val){
  laz_out(node, s, e);

  if(r < s || e < l || l > r)
    return;

  if(l <= s && e <= r){
    laz[node] += val;
    laz_out(node, s, e);
    return;
  }

  int md = (s + e) >> 1;
  update(node << 1,s, md, l, r, val);
  update(node << 1 | 1, md + 1, e, l, r, val);

  tree[node] = max(tree[node << 1], tree[node << 1 | 1]);

}
pair<int, int>qry(int node, int s, int e, int l, int r){
  if(r < s || e < l || l > r)return {-1e9, -1e9};
  if(l <= s && e <= r)
    return tree[node];
  int md = (s + e) >> 1;
  return max(qry(node << 1, s, md, l, r),qry(node << 1 | 1, md + 1, e, l, r));
}
vector<int>upd[N];
vector<int>go_to[N];
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;

  worker b[n];

  for(int i = 0; i < n; i++){
    cin >> a[i];
    upd[a[i].v].push_back(i);
    go_to[a[i].l].push_back(i);
  }

  build(1, 1, N-1);

  int ans = 0;
  int idx = -1;
  int idx2 = -1;
  for(int i = N - 1; i > 0; i--){
    for(auto v : upd[i]){
      update(1, 1, N -1,a[v].v, a[v].r, 1);
    }
    int cur = qry(1, 1, N -  1, i , N - 1).first;
    if(cur > ans){
      ans = cur;
      idx = i;
      idx2 = qry(1, 1, N - 1, i, N - 1).second;
    }
    for(auto v : go_to[i]){
      update(1, 1, N - 1,a[v].v, a[v].r,-1);
    }
  }

  cout << ans << '\n';

  for(int i = 0; i < n; i++){
    if(a[i].l <= idx && a[i].r >= idx2 && a[i].v <= idx2 && a[i].v >= idx)
      cout << i + 1 << " \n"[i+1==n];
  }



}
