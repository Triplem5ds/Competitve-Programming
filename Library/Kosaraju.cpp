#include "bits/stdc++.h"
using namespace std;

/*
  g :  Adjacency List of the original graph
  rg : Reversed Adjacency List
  vis : A bitset to mark visited nodes
  adj : Adjacency List of the super graph
  stk : holds dfs ordered elements
  cmp[i] : holds the component of node i
  go[i] : holds the nodes inside the strongly connected component i
*/

#define FOR(i,a,b) for(int i = a; i < b; i++)
#define pb push_back

const int N = 1e5+5;

vector<vector<int>>g, rg;
vector<vector<int>>go;
bitset<N>vis;
vector<vector<int>>adj;
stack<int>stk;
int n, m, cmp[N];
void add_edge(int u, int v){
  g[u].push_back(v);
  rg[v].push_back(u);
}
void dfs(int u){
  vis[u]=1;
  for(auto v : g[u])if(!vis[v])dfs(v);
  stk.push(u);
}
void rdfs(int u,int c){
  vis[u] = 1;
  cmp[u] = c;
  go[c].push_back(u);
  for(auto v : rg[u])if(!vis[v])rdfs(v,c);
}
int scc(){
  vis.reset();
  for(int i = 0; i < n; i++)if(!vis[i])
    dfs(i);
  vis.reset();
  int c = 0;
  while(stk.size()){
    auto cur = stk.top();
    stk.pop();
    if(!vis[cur])
      rdfs(cur,c++);

  }
  return c;
}

int main(){

  scanf("%d%d", &n, &m);

  g.resize(n+1);
  rg.resize(n+1);
  go.resize(n+1);

  FOR(i,0,m){
    int u , v;  scanf("%d%d", &u, &v);
    adj[u].pb(v);
  }

  int cnt = scc();
  go.resize(cnt+1);
  adj.resize(cnt+1);
  for(int i = 0; i < n; i++)
    for(auto v : g[i])if(cmp[i]!=cmp[v])
      adj[cmp[i]].push_back(cmp[v]);

 for(int i = 0; i < cnt; i++){
    sort(adj[i].begin(),adj[i].end());
    adj[i].resize(unique(adj[i].begin(),adj[i].end()) - adj[i].begin());
  }

}
