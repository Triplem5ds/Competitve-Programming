#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5 +5;
const int M = 2 * N;
const int blk = 2155;
const int mod = 1e9 + 7;
struct Query{
  int l, r, t, idx;
  Query(int a = 0,int b = 0,int c = 0,int d = 0){l=a,r=b,t=c,idx = d;}
  bool operator < (Query o){
    if(r / blk == o.r / blk && l / blk == o.l / blk)return t < o.t;
    if(r / blk == o.r / blk)return l < o.l;
    return r < o.r;
  }
} Q[N];

int a[N], b[N];
int cnt1[M], cnt2[N];
int L = 0, R = -1, K = -1;
void add(int x){
//  cout << x << '\n';
  cnt2[cnt1[x]]--;
  cnt1[x]++;
  cnt2[cnt1[x]]++;
}
void del(int x){
  cnt2[cnt1[x]]--;
  cnt1[x]--;
  cnt2[cnt1[x]]++;
}
map<int,int>id;
int cnt;
int ans[N];
int p[N], nxt[N];
int prv[N];
void upd(int idx){
  if(p[idx] >= L && p[idx] <= R)
    del(a[p[idx]]), add(nxt[idx]);
  a[p[idx]] = nxt[idx];
}
void err(int idx){
  if(p[idx] >= L && p[idx] <= R)
    del(a[p[idx]]), add(prv[idx]);
  a[p[idx]] = prv[idx];
}
int main(){

  int n, q, l, r, tp;

  scanf("%d%d", &n, &q);

  for(int i = 0; i < n; i++){
    scanf("%d", a + i);
    if(id.count(a[i]) == 0)
      id[a[i]] = cnt++;
    a[i] = id[a[i]];
    b[i] = a[i];
  }
  int qIdx = 0;
  int ord = 0;
  while(q--){

    scanf("%d", &tp);
    if(tp == 1){
      /// ADD Query
      scanf("%d%d", &l, &r);  --l, --r;
      Q[qIdx] = Query(l,r,ord-1,qIdx); qIdx++;
    } else{
      /// ADD Update
      scanf("%d%d",p + ord, nxt + ord); --p[ord];
      if(id.count(nxt[ord]) == 0)
        id[nxt[ord]] = cnt++;
      nxt[ord] = id[nxt[ord]];
      prv[ord] = b[p[ord]];
      b[p[ord]] = nxt[ord];
      ++ord;
    }

  }
  sort(Q,Q+qIdx);
  for(int i = 0; i < qIdx; i++){
    while(L < Q[i].l)del(a[L++]);
    while(L > Q[i].l)add(a[--L]);
    while(R < Q[i].r)add(a[++R]);
    while(R > Q[i].r)del(a[R--]);
    while(K < Q[i].t)upd(++K);
    while(K > Q[i].t)err(K--);
    ///Solve Query I
  }
  for(int i = 0; i < qIdx; i++)
    printf("%d\n", ans[i]);


  return 0;
}
