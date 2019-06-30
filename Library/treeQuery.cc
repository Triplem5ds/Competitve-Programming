const int N = 1e5 + 5;
const int LG = 18;

vector<int> adj[N];
int pa[N][LG], lvl[N];
int in[N], out[N], timer;
void dfs(int u, int p){
  in[u] = timer++;
  for(int k = 1; k < LG; k++)
    pa[u][i] = pa[pa[u][i-1]][i-1];
  for(auto v : adj[u])
    if(v != p){
       lvl[v] = lvl[u] + 1;
       pa[v][0] = u;
       dfs(v, u);
     }
  out[u] = timer++;
}
int LCA(int u, int v){
  if(lvl[u] > lvl[v])
    swap(u,v);
   int d = lvl[v] - lvl[u];
   for(int k = 0; k < LG; k++)
    if(d >> k & 1)
      v = pa[v][k];
   if(u == v)return u;
   for(int i = LG - 1; i >= 0; --i)
    if(pa[u][i] != pa[v][i]){
      u = pa[u][i];
      v = pa[v][i];
    }
  return pa[u][0];
}
