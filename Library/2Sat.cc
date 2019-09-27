struct _2Sat{

  vector<vector<int>> g, rg;
  vector<bool> vis;
  vector<int> cmp, tr;  ///true variables
  int nodes;

  _2Sat(int n = 0){
    nodes = n;
    g.resize(n + 5);
    rg.resize(n + 5);
    vis.assign(n + 5, 0);
    cmp.assign(n + 5, 0);
  }

  void addEdge(int u, int v){
    g[u].pb(v);
    rg[v].pb(u);
  }

  void addOR(int u, int v){
    ///this means either U or V is true
    addEdge(u^1,v);
    addEdge(v^1,u);
  }

  void dfs1(int u){
    if(vis[u])
      return;
    vis[u] = true;
    for(auto v : g[u])
      dfs1(v);
    stk.push(u);
  }
  void dfs2(int u, int cnt){
    if(cmp[u])
      return;
    cmp[u] = cnt;
    for(auto v : rg[u])
      dfs2(v, cnt);
  }
  bool killSat(){
    for(int i = 0; i < nodes + nodes; i++)
      dfs1(i);
    int cnt = 0;
    while(stk.size()){
      auto x = stk.top();
      stk.pop();
      if(!cmp[x])
        dfs2(x, ++cnt);
    }
    for(int i = 0; i < nodes; i++)
      if(cmp[i << 1] == cmp[i << 1 | 1])
        return false;
      else if(cmp[i << 1] > cmp[i << 1 | 1])
        tr.pb(i);
    return true;
  }
};
