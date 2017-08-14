#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 5;

int a[N], n;

int tree[N << 2];
int laz[N << 2];

void build(int node, int s, int e){

  if(s == e){
    tree[node] = a[s];
    return;
  }

  int md = (s + e) >> 1;

  build(node << 1, s, md);
  build(node << 1 | 1, md + 1, e);

  tree[node] = min(tree[node << 1], tree[node << 1 | 1]);


}


int qry(int node, int s, int e, int l, int r){

  if(r < s || e < l)return INT_MAX;

  if(l <= s && e <= r)return tree[node];

  int md = (s + e) >> 1;

  return min(qry(node <<1, s, md, l, r),
      qry(node << 1 | 1, md + 1, e, l, r)
  );

}

int main(){

  while(scanf("%d", &n) && n){

    for(int i = 0; i < n; i++)
      scanf("%d", a + i);

    for(int i = n; i < n + n; i++)
      a[i] = a[i - n];

    for(int i = 1; i < n + n; i++)
      a[i] += a[i - 1];

    int ans = 0;

    int bck = 0;

    n <<= 1;

    build(1, 0, n - 1);

    for(int i = 0; i < (n >> 1); i++){


      if(qry(1, 0, n - 1, i, i + (n >> 1) - 1) - bck >= 0)ans++;

      if(i)bck += (a[i] - a[i-1]);
      else bck += a[i];

    }

    printf("%d\n", ans);



  }




}
