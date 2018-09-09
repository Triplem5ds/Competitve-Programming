#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
const int mod = 1e9 + 7;

int n, q;
vector<int>adj[N];
int in[N], out[N];
int sz[N], head[N], par[N];
int timer;

void dfs(int u){
  sz[u] = 1;
  for(auto & v : adj[u]){
    par[v] = u;
    dfs(v);
    sz[u] += sz[v];
    if(sz[v] > sz[adj[u][0]])
      swap(v,adj[u][0]);
  }
}

void dfsHLD(int u){

  in[u] = ++timer;

  if(adj[u].size()){
    head[adj[u][0]] = head[u];
    dfsHLD(adj[u][0]);
  }

  for(auto v : adj[u])if(v != adj[u][0]){

    head[v] = v;
    dfsHLD(v);

  }

  out[u] = timer;

}
int lz[N<<2];
struct node{
  int sum, mx;
  node(int sum = -n * 2, int mx = -n * 2) : sum(sum), mx(mx){}
}tree[N<<2];

node merge(node L, node R){
  if(L.sum == -n * 2)return R;
  if(R.sum == -n * 2)return L;
  return node(L.sum + R.sum, max(R.mx,L.mx + R.sum));
}

void build(int o, int s, int e){
  if(s==e){
    tree[o] = node(-1,-1);
  } else {
    int md = (s+e) >> 1;
    build(o<<1,s,md);
    build(o<<1|1,md+1,e);
    tree[o] = merge(tree[o<<1], tree[o<<1|1]);
  }
}
void push(int o, int s, int e){
  if(!lz[o])return;
  tree[o] = node(-(e-s+1), -1);
  if(s!=e){
    lz[o<<1] = lz[o<<1|1]= 1;
  }
  lz[o] = 0;
}
void upd(int o, int s, int e, int l, int r){
  push(o,s,e);
  if(r<s||e<l)return;
  if(l<=s&&e<=r){
    lz[o] = 1;
    push(o,s,e);
  } else {
    int md = (s+e)>>1;
    upd(o<<1,s,md,l,r);
    upd(o<<1|1,md+1,e,l,r);
    tree[o] = merge(tree[o<<1], tree[o<<1|1]);
  }
}
void updIdx(int o, int s, int e, int idx, int v){
  push(o,s,e);
  if(idx < s || e < idx)return;
  if(s==e){
    tree[o].sum += v;
    tree[o].mx += v;
    return;
  }
  int md = (s + e) >> 1;
  updIdx(o<<1,s,md,idx,v);
  updIdx(o<<1|1,md+1,e,idx,v);
  tree[o] = merge(tree[o<<1], tree[o<<1|1]);
}
node qry(int o, int s, int e, int l, int r){
  push(o,s,e);
  if(r<s||e<l)return node();
  if(l<=s&&e<=r){
    return tree[o];
  }
  int md = (s+e)>> 1;
  return merge(qry(o<<1,s,md,l,r),
               qry(o<<1|1,md+1,e,l,r));
}
node get(int u){
  node ret = node();
  while(head[u] != 1){
    ret = merge(qry(1,1,n,in[head[u]], in[u]), ret);
    u = par[head[u]];
  }
  ret = merge(qry(1,1,n,1,in[u]), ret);
  return ret;
}
