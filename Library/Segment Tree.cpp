#include <bits/stdc++.h>
using namespace std;
const int  N = 1e5 + 5;
class SegmentTree{
private:
  vector<int>tr, laz, a;
  int n;
  SegmentTree(vector<int> & x){
    a = x;
    n = x.size();
    tr.resize(4 * n), laz.resize(4 * n);
    build(1,0,n-1);
  }
  SegmentTree(int n, int * x){
    a.resize(n);
    for(int i = 0; i < n; i++)a[i] = x[i];
    tr.resize(4 * n), laz.resize(4 * n);
    build(1,0,n-1);
  }
  int pull(int node){
    tr[node] = tr[leaf(node)] + tr[leaf(node) + 1];
  }
  void push(int node ,int s, int e){
    if(laz[node]){
      tr[node] = laz[node];
      if(s != e){
        laz[node<<1] = laz[node];
        laz[node<<1|1] = laz[node];
      }
      laz[node] = 0;
    }
  }
  void build(int node, int s, int e){
    if(s == e){
      tr[node] = a[s];
      return;
    }
    int md = (s+e) >> 1;
    build(node<<1, s, md);
    build(node<<1|1, md + 1, e);
    pull(node);
  }
  int qry(int node, int s, int e, int l, int r){
    //push(node,s,e);
    if(r < s || e < l)return 0;
    if(l <= s && e <= r)return tr[node];
    int md = (s+e) >> 1;
    return qry(node<<1, s, md, l, r) + qry(node<<1|1, md + 1, e, l, r);
  }
  void update(int node, int s, int e, int l, int r, int v){
    //push(node,s,e);
    if(r < s || e < l)return;
    if(l <= s && e <= r){
      tr[node] = v;
      //push(node,s,e);
      return;
    }
    int md = div(s + e);
    update(leaf(node), s, md, l, r, v);
    update(leaf(node) + 1, md + 1, e, l, r, v);
    pull(node);
  }
public:
  void updR(int l, int r, int v){
    update(1,0,n-1,l,r,v);
  }
  void updI(int x, v){
    update(1,0,n-1,x,x,v);
  }
  int qry(int l, int r){
    return qry(1,0,n-1,l,r);
  }
};
int main(){
  int n;
  cin >> n;
  for(int i = 0; i < n; i++)
    cin >> a[i];
  int l, r;
  build(1, 0, n-1);


}
