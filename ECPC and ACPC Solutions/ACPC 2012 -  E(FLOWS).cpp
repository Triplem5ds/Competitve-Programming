#include <bits/stdc++.h>
using namespace std;
const int N = 205;

string s;
int sv[26];
int cap[N][N];
vector<vector<int> >adj;
int src, snk, par[N], n;
vector<string>v;
void add_edge(int u, int v, int c){
  cap[u][v] = c;
  cap[v][u] = 0;
  adj[u].push_back(v);
  adj[v].push_back(u);
}
bool bfs(int src){

  memset(par, -1, sizeof par);

  queue<int>q;

  q.push(src);

  while(q.size()){

    int u = q.front();
    q.pop();

    if(u == snk)return 1;

    for(auto v : adj[u]){
      if(~par[v])continue;
      if(cap[u][v]){
        par[v] = u;
        q.push(v);
      }

    }

  }

  return 0;
}

bool ok(int idx, int lft){

  adj.clear();
  adj.resize(n + 30);
  memset(cap, 0, sizeof cap);

  for(int i = idx; i <= n; i++)
    add_edge(src, i, 1);

  for(int i = idx-1; i < n; i++){
    for(auto c : v[i]){
      add_edge(i + 1, n + 1 + (c - 'a'), 1);
    }
  }

  for(int i = 1; i <= 26; i++)if(sv[i-1])
    add_edge(i + n, snk, sv[i-1]);

  int tot_flow = 0;


  while(bfs(src)){

    int path_flow = INT_MAX;


    int u, v;

    for(v = snk; v != src; v = par[v]){
      u = par[v];
      path_flow = min(path_flow, cap[u][v]);
    }
    for(v = snk; v != src; v = par[v]){
      u = par[v];
      cap[u][v] -= path_flow;
      cap[v][u] += path_flow;
    }

    tot_flow += path_flow;

  }

  return tot_flow == lft;
}
int main(){

  cin >> s;

  n = s.size();

  v.resize(n);

  src = 0, snk = n + 27;

  for(int i = 0; i < n; i++)cin >> v[i], sort(v[i].begin(), v[i].end());

  for(auto c : s)sv[c - 'a']++;

  string out = "";

  for(int i = 0; i < n; i++){

    int idx = -1;

    for(int j = 0; j < v[i].size(); j++){
        if(!sv[v[i][j] - 'a'])continue;
        sv[v[i][j] - 'a']--;
        if(ok( i + 2,n - i - 1)){
          idx = j;
          break;
        }
        sv[v[i][j] - 'a']++;
    }

    if(idx == -1)return puts("NO SOLUTION");


    out.push_back(v[i][idx]);

  }

  cout << out << endl;




}
