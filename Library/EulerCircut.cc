const int N = 1e5 + 5;
int n;
std::vector<pair<int, int>> adj[N];
bool vis[N+N];
std::vector<int> ans;
void dfs(int u){
    while(!adj[u].empty()){
        auto x = adj[u].back();
        adj[u].pop_back();
        if(vis[x.second])continue;
        vis[x.second^1]=1;
        dfs(x.first);
    }
	ans.push_back(u);
}
bool solveEuler(){
  int st = 0, cnt = 0; ///0-based
  for(int i = 0; i < n; i++){
    if(adj[i].size() & 1){
      st = i; cnt++;
    }
  }
  if(cnt != 0 && cnt != 2)return false;
  dfs(st);
  return true;
 }
