#include <bits/stdc++.h>

using namespace std;

const int N = 405;

struct Edge{
  int from, to ,nxt, cap, flw;
  double cost;
}e[N*N*4];

int n, edgeCnt, head[N<<1], flw[N<<1], vis[N<<1], p[N<<1], src, snk;
double dist[N<<2], d[N][N];

void addEdge(int u, int v, int cap, double cost){
  e[edgeCnt].from = u;
  e[edgeCnt].to = v;
  e[edgeCnt].cap = cap;
  e[edgeCnt].flw = 0;
  e[edgeCnt].cost = cost;
  e[edgeCnt].nxt = head[u];
  head[u] = edgeCnt++;
}
int spfa(){
  ///The Strongest Algorithm in the World
  memset(vis, 0, sizeof vis);
  memset(flw, 0, sizeof flw);
  for(int i = 0; i <= snk; i++)dist[i] = 1e8;
  queue<int>q;
  q.push(src); vis[src] = 1; flw[src] = 1e8; dist[src] = 0;

  while(!q.empty()){

    auto  cur = q.front();  q.pop();  vis[cur] = 0;
    for(int i = head[cur]; ~i; i = e[i].nxt){
        int v = e[i].to;
        if(e[i].cap == e[i].flw)continue;
//        cerr << e[i].cap << ' ' << e[i].flw << '\n';
        if(dist[v] > dist[cur] + e[i].cost + 1e-7){
            dist[v] = dist[cur] + e[i].cost;
            p[v] = i;
            flw[v] = min(flw[cur], e[i].cap - e[i].flw);
            if(!vis[v]){
              vis[v] = 1;
              q.push(v);
            }
        }

    }

  }
  return flw[snk] > 0;
}
void addBiEdge(int u, int v, int cap, double cost){
  addEdge(u,v,cap,cost);
  addEdge(v,u,0,-cost);
}
pair<int,double> MCMF(){
  pair<int,double>ret = make_pair(0,0.0);
  while(spfa()){

    ret.first+= flw[snk];
    ret.second += dist[snk];
    for(int i = snk; i != src; i = e[p[i]].from){
      e[p[i]].flw+=flw[snk];
      e[p[i]^1].flw-=flw[snk];
    }


  }

  return ret;

}
