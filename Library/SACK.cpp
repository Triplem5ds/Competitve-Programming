
const int N = 1e5 + 5

int in[N], out[N], ord[N], lvl[N], sz[N], timer;
vector<vector<int>>adj;

void dfs0(int u){
    sz[u] = 1;
    in[u] = timer;
    for(auto v : adj[u])if(v != p){
        lvl[v] = lvl[u] + 1;
        dfs0(v), sz[u] += sz[v];
    }
    ord[timer] = u;
    out[u] = timer++;
}

void add(int node){
  //To Be Implemented
}

void del(int node){
  //To Be Implemented
}

void dfs1(int u, bool keep){

    int mx = -1, bigChild =-1;
    for(auto v : adj[u])if(v != p && sz[v] > mx)
        mx = sz[v], bigChild = v;
    for(auto v : adj[u])if(v != bigChild && v != p)
        dfs1(v, 0);
    if(~bigChild){
        dfs1(bigChild, 1);
    }

    for(auto v : adj[u])if(v != bigChild){

        for(int x = in[v]; x <= out[v]; x++){
            add(ord[x]);
        }

    }

    add(u);

    if(!keep){
        for(int x = in[u]; x <= out[u]; x++){
          del(ord[x]);
     }
        
    }

}
