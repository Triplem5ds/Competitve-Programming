#include <bits/stdc++.h>
using namespace std;

const int MX = 5e4 + 5;

/*
  the idea is to create a minimum spanning tree this way you know that all nodes are connected using only 
  the minimum edges and since this is a tree we can use LCA between two nodes and binary raise to find the
  distance between that LCA and theses cities. 

*/
int n, u, v, m, w;


struct dsu{
  vector<int>par, rnk;

  dsu(int N){
    rnk.assign(N, 1);
    par.resize(N);
    for(int i = 0; i < N; i++)
      par[i] = i;
  }
  int get(int i){return i == par[i]? i : par[i] = get(par[i]);}

  void merge(int u, int v){
    u = get(u);
    v = get(v);

    if(u == v)return;

    if(rnk[u] > rnk[v])swap(u, v);

    rnk[v] += rnk[u];

    par[u] = v;

  }


};
vector<pair<int, int> >adj[MX];
vector<pair<int, pair<int, int> > >edges;

void MST(){

  sort(edges.begin(), edges.end());

  dsu store = dsu(n);

  for(int i = 0; i < edges.size(); i++){

    u = edges[i].second.first;
    v = edges[i].second.second;
    w = edges[i].first;

    u = store.get(u);
    v = store.get(v);


    if(u == v)continue;

    adj[u].push_back({v, w});
    adj[v].push_back({u, w});

    store.merge(u, v);
  }
}



int ST[MX][16];
int ST2[MX][16];
int par[MX], lvl[MX];

void dfs(int u, int p){


  for(auto v : adj[u]){
    if(v.first == p)continue;
    lvl[v.first] = lvl[u] + 1;
    par[v.first] = ST[v.first][0] = u;
    ST2[v.first][0] = v.second;
    dfs(v.first, u);
  }



}

void build(){
  memset(ST, -1, sizeof ST);
  memset(par, -1, sizeof par);
  memset(lvl, 0, sizeof lvl);

  dfs(0, -1);

  for(int j = 1; (1 << j) < n; j++)
    for(int i = 0; i < n; i++)
      if(ST[i][j-1] != -1)
        ST[i][j] = ST[ST[i][j-1]][j-1],
          ST2[i][j] = max(ST2[i][j-1], ST2[ST[i][j-1]][j-1]);

}
int LCA(int p, int q){
  if(lvl[p] < lvl[q])swap(p, q);
  int log;

  for(log = 1; 1 << log <= lvl[p]; log++);

  log--;

  for(int i = log; i >= 0; i--)
    if(lvl[p] - (1 << i) >= lvl[q])
      p = ST[p][i];
  if(p == q)return p;
  for(int i = log; i>= 0; i--){
    if(ST[p][i] != -1 && ST[p][i] != ST[q][i])
      p = ST[p][i], q = ST[q][i];
  }
  return par[p];
}

int kth(int u, int pth){

  int ret = 0;

  for(int i = 25; i>=0;i--){
    if(pth - (1<<i) >=0){
      ret = max(ret, ST2[u][i]);
      u = ST[u][i];
      pth -= (1 << i);

    }
  }
  return ret;
}

int main(){

    bool f = false;

    while(scanf("%d%d", &n, &m) == 2){

    edges.clear();

    if(f)puts("");

    f = true;

    for(int i = 0; i < n; i++)
      adj[i].clear();

    while(m--){
      scanf("%d%d%d", &u, &v, &w);
      u--, v--;
      edges.push_back({w, {u, v}});
    }


    MST();



    int q, s, t;

    scanf("%d", &q);

    build();

    while(q--){

      scanf("%d%d", &s, &t);

      s--, t--;

      int lca = LCA(s, t);

      int k1 = lvl[s] - lvl[lca];
      int k2 = lvl[t] - lvl[lca];

      cout << max(kth(s, k1),kth(t, k2)) << '\n';

    }


  }
  return 0;
}
