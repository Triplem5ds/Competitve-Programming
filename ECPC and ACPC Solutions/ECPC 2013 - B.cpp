#include <bits/stdc++.h>
using namespace std;
vector<vector<int> >adj;
vector<pair<int, pair<int, int> > >edges;
int sv[200005];

int n, m, u, v, w;


struct dsu{
  vector<int>rnk, par;

  dsu(int n = 0){
    rnk.assign(n, 1);
    par.assign(n, 0);
    for(int i = 0; i < n; i++)par[i] = i;
  }

  int get(int i){return i == par[i]? i : get(par[i]);}

  bool merge(int u, int v){

    u = get(u);
    v = get(v);

    if(u == v)return 0;

    if(rnk[u] > rnk[v])swap(u, v);

    par[u] = v;
    rnk[v] += rnk[u];

    return 1;

  }
}store;


int calc(int i){
    int ret = 0;
    while(i != store.par[i]){
      ret += sv[i];
      i = store.par[i];
    }
    return ret + sv[i];
}

int main(){
  
  freopen("road.in", "r", stdin);

  int t;

  scanf("%d", &t);

  int css = 0;

  while(t--){
    memset(sv, 0, sizeof sv);

    scanf("%d%d", &n, &m);

    edges.clear();
    
    while(m--){
      scanf("%d%d%d", &u, &v, &w);

      u--, v--;

      edges.push_back({w, {u, v}});

    }

    store = dsu(n);

    sort(edges.begin(), edges.end());


    memset(sv, 0, sizeof sv);

    for(int i = 0; i < edges.size(); i++){

      int u = edges[i].second.first;
      int v = edges[i].second.second;
      int w = edges[i].first;
      u = store.get(u), v = store.get(v);
      if(u != v){
         if(store.rnk[u] > store.rnk[v])swap(u, v);
          sv[u] += w * store.rnk[v];
          sv[v] += w * store.rnk[u];
          sv[u] -= sv[v];
          store.rnk[v] += store.rnk[u];
          store.par[u] = v;
      }
    }

    printf("Case %d:\n", ++css);

    for(int i = 0; i < n; i++)
      printf("%d\n", calc(i));

  }



  return 0;
}
