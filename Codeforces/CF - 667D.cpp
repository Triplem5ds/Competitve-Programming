#include <bits/stdc++.h>
using namespace std;

/*
  the idea is to run a BFS and Reverse BFS for all nodes finding the shortest distance between all nodes and each other
  then the basic idea is that you need 4 nodes a->b->c->d you can loop over b and c
  and then after some pre-processing check a and d.

*/

const short int N = 3005;
vector<short int>adj[2][N];;
short int dist[2][N][N];
set<pair<short int, short int> >st[2][N];
short int n, m;
struct ans{
  short int val;
  vector<short int>nodes;
  ans(short int val = 0, vector<short int>nodes = {}):val(val),nodes(nodes){}

};

ans max(ans a, ans b){
  if(a.val > b.val)return a;
  return b;
}

void bfs(short int src, short int idx){
  queue<short int>q;
  vector<bool>vis(n + 1);
  q.push(src);

  vis[src] = 1;
  dist[idx][src][src] = 0;

  while(q.size()){
    auto cur = q.front();
    q.pop();

    for(auto v : adj[idx][cur]){
      if(vis[v])continue;
      vis[v] = true;
      dist[idx][src][v] = dist[idx][src][cur] + 1;
      q.push(v);
    }
  }
}
int main(){
  memset(dist, -1, sizeof dist);

  cin >> n >> m;

  for(short int i = 0; i < m; i++){
    short int u, v;
    cin >> u >> v;
    adj[0][u].push_back(v);
    adj[1][v].push_back(u);
  }

  for(short int i = 0; i < 2; i++)
    for(short int j = 1; j <= n; j++)
      bfs(j, i);

  ans ret;
  pair<int, int> sv[n];
  for(short int tst = 0; tst < 2; tst++){
    for(short int i = 1; i <= n; i++){
      int idx = 0;
      for(short int j = 1; j <= n; j++){
        sv[j] = {0,-1};
        if(i == j)continue;
        if(dist[tst][i][j] != - 1){
            sv[idx++] = {-dist[tst][i][j],j};
        }
      }
      sort(sv, sv + n);
      for(int k = 0; k < min(idx, 6); k++){
        st[tst][i].insert(sv[k]);
      }
    }
  }
  //puts("WHY");
  for(short int i = 1; i <= n; i++){

    for(short int j = 1; j <= n; j++){
      if(i == j)continue;
      if(dist[0][i][j] == -1 || st[1][i].size() == 0 || st[0][j].size() == 0)continue;

      auto it1 = st[1][i].begin();
      if((*it1).second == j)it1++;
      if(it1 == st[1][i].end())continue;

      auto it2 = st[0][j].begin();
      if((*it2).second == i)it2++;
      if(it2 == st[0][j].end())continue;

      if((*it2).second != (*it1).second){
        ret = max(ret,ans(dist[0][i][j] - (*it2).first - (*it1).first, {(*it1).second,i,j,(*it2).second}));
      }
      else{
        auto it3 = it1, it4 = it2;
        it3++, it4++;
        if(it3 != st[1][i].end()&&(*it3).second == j)it3++;
        if(it4!=st[0][j].end()&&(*it4).second == i)it4++;

        if(it3 != st[1][i].end()){
          ret = max(ret,ans(dist[0][i][j] - (*it2).first - (*it3).first, {(*it3).second,i,j,(*it2).second}));
        }
        if(it4 != st[0][j].end()){
        ret = max(ret,ans(dist[0][i][j] - (*it4).first - (*it1).first, {(*it1).second,i,j,(*it4).second}));
        }

      }
    }

  }

//  cerr << ret.val << '\n';

  for(short int i = 0; i < ret.nodes.size(); i++)
    cout << ret.nodes[i] << ' ';


}
