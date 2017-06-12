#include <iostream>
#include <vector>
#include <stack>
#include <string.h>
#include <stdio.h>
using namespace std;

/*
  the idea is that if we divide the graph into strongly connected the super graph becomes a DAG however finding which
  SCC that all cities can go to would be hard so we reverse the edges and find the SCC that 0 cities can go to
  if there are multiple ones the answer is 0.

*/
const int  N = 1e5 + 5;
bool vis[N];
int scc[N];
stack<int> stk;
int cnt;
vector<int>cmp[N];
vector<int> adj[N];
vector<int> adj2[N];
int in[N];
int n, m, u, v;
void dfs(int u){
  if(vis[u])return;
  vis[u] = true;
  for(int i = 0; i < adj[u].size(); i++){
    int v = adj[u][i];
    dfs(v);
  }
  stk.push(u);
}
void dfs2(int u){
  if(scc[u] != -1)return;
  scc[u] = cnt;
  cmp[cnt].push_back(u);
  //cout << adj2[u].size() << '\n';
  for(int i = 0; i < adj2[u].size(); i++){
    int v = adj2[u][i];
    dfs2(v);
  }
}
void Kosaraju(){
  memset(vis, 0, sizeof vis);
  memset(scc, -1, sizeof scc);
  for(int i = 0; i < n; i++)
    dfs(i);
  while(stk.size()){
    int v = stk.top();
    stk.pop();
    if(scc[v] == -1){
     // cout << v << '\n';
     // system("pause");
      dfs2(v);
      cnt++;
    }
  }
}
int main(){
  scanf("%d%d", &n, &m);

  for(int i = 0; i < m; i++){
    scanf("%d%d", &u, &v);
    u--, v--;
    adj[v].push_back(u);
    adj2[u].push_back(v);
  }
  Kosaraju();


  //vector<int>ans;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < adj[i].size(); j++){
      int v = adj[i][j];
      if(scc[i] != scc[v])
        in[scc[v]]++;
    }
  }
  int cnt2 = 0;
  for(int i = 0; i < cnt; i++)
    if(!in[i])cnt2++;

  if(cnt2 > 1)
    return puts("0");
  cnt2 = 0;

  for(int i = 0; i < n; i++){
    if(!in[scc[i]])cnt2++;
  }

  printf("%d\n", cnt2);

  for(int i = 0; i < n; i++){
    if(!in[scc[i]])
      printf("%d ", i+1
             );
  }

  puts("");


}
