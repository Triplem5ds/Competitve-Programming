#include "bits/stdc++.h"
using namespace std;

const int mxN = 100010;

int sz[mxN], nxt[mxN];
int in[N], out[N], rin[N];
vector<int> g[mxN];
int par[mxN];

void dfs_sz(int v = 0, int p = -1) {
	sz[v] = 1;
	par[v] = p;
	//		//cerr << v << '\n';
	for (auto &u : g[v]) {
		if (u == p) {
			swap(u, g[v].back());
		}
		if(u == p) continue;
		dfs_sz(u,v);
		sz[v] += sz[u];
		if (sz[u] > sz[g[v][0]])
			swap(u, g[v][0]);
	}
	if(v != 0)
		g[v].pop_back();
}

void dfs_hld(int v = 0) {
	in[v] = t++;
	//cerr << v << '\n';
	rin[in[v]] = v;
	for (auto u : g[v]) {
		nxt[u] = (u == g[v][0] ? nxt[v] : u);
		dfs_hld(u);
	}
	out[v] = t;
}

int n;
bool isChild(int p, int u){
  return in[p] <= in[u] && out[u] <= out[p];
}
int solve(int u,int v) {
	vector<pair<int,int> > segu;
	vector<pair<int,int> > segv;
  vector<pair<int,int>>L,R;
	if(isChild(u,v)){
    while(nxt[u] != nxt[v]){
      segv.push_back(make_pair(in[nxt[v]], in[v]));
      v = par[nxt[v]];
    }
    segv.push_back({in[u], in[v]});
//    for(auto x : segv)
//      cout << x.first+1 << ' ' << x.second + 1 << '\n';
	} else if(isChild(v,u)){
    while(nxt[u] != nxt[v]){
      segu.push_back(make_pair(in[nxt[u]], in[u]));
      u = par[nxt[u]];
    }
    segu.push_back({in[v], in[u]});
  }
  else {
    while(u  != v) {
      if(nxt[u] == nxt[v]) {
        if(in[u] < in[v]) segv.push_back({in[u],in[v]}), R.push_back({u+1,v+1});
        else segu.push_back({in[v],in[u]}), L.push_back({v+1,u+1});
        u = v;
        break;
      } else if(in[u] > in[v]) {
        segu.push_back({in[nxt[u]],in[u]}), L.push_back({nxt[u]+1, u+1});
        u = par[nxt[u]];
      } else {
        segv.push_back({in[nxt[v]],in[v]}), R.push_back({nxt[v]+1, v+1});
        v = par[nxt[v]];
      }
    }
	}
	reverse(segv.begin(),segv.end());
//	reverse(R.begin(),R.end());
	int res = 0,state = 0;
	for(auto p : segu) {
		qry(1,1,0,n-1,p.first,p.second,state,res);
//		cout << rin[p.first ] + 1<< ' ' << rin[p.second]+1 << '\n';
	}
//	cout << "------------------------\n";
	for(auto p : segv) {
		qry(0,1,0,n-1,p.first,p.second,state,res);
//		cout << rin[p.first ]+1<< ' ' << rin[p.second]+1 << '\n';
	}
//	for(auto x : L)
//		cout << x.first << ' ' << x.second << '\n';
//	for(auto x : R)
//		cout << x.first << ' ' << x.second << '\n';
	return res;
}
