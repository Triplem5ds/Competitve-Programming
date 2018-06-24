namespace HLD{
    const int N = 2e5+5;
    vector<pair<int,int>>adj[N];
    int sz[N], par[N], lvl[N];
    int in[N], head[N], timer=0;
    int a[N], b[N];
    int pos[N];
    void dfs0(int u, int p=-1,int l=0){

        lvl[u] = l;
        par[u] = p;
        sz[u] = 1;

        for(auto & v : adj[u])if(v.first != p){
            dfs0(v.first,u,l+1);
            sz[u] += sz[v.first];
            if(sz[v.first] > sz[adj[u][0].first])
                swap(v, adj[u][0]);
        }

    }

    void dfs1(int u){

        in[u] = timer++;

        for(auto v : adj[u])if(v.first != par[u]){
            head[v.first] = (v.first == adj[u][0].first ? head[u] : v.first);
            int i = v.second;
            pos[i] = timer;
            a[timer] = 1;
            b[timer] = 1;
            dfs1(v.first);
        }

    }

    struct node{
        int s, e, lSon, rSon;
        int val, laz;
    }tree[N<<2];

    int build(int s, int e, int * a = NULL){
        int node = ++timer;
        tree[node].s=s;
        tree[node].e=e;
        if(s==e){
            tree[node].val = a[s];
            return node;
        }
        int md = (s+e)>>1;
        tree[node].lSon = build(s,md);
        tree[node].rSon = build(md+1,e);
        tree[node].val = tree[tree[node].lSon].val + tree[tree[node].rSon].val;
        return node;
    }
    void push(int node){
      ///TODO
    }
    int qry(int node, int l, int r, int v){
      push(node);
      if(l <= tree[node].s && tree[node].e <= r){
          return tree[node].val;
      }
      int ret = 0;
      if(tree[tree[node].lSon].e >= l)ret = ret + qry(tree[node].lSon,l,r);
      if(tree[tree[node].rSon].s <= r)ret = ret + qry(tree[node].rSon,l,r);
      return ret;
    }
    int solve(int u, int v){

        int ret={0,0};
        while(head[u] != head[v]){

            if(lvl[head[u]] > lvl[head[v]])swap(u,v);
            ret = ret + qry(1,in[head[v]], in[v]);
            v = par[head[v]];
        }

        if(u != v){
            ret =  ret + qry(1,min(in[u],in[v])+1,max(in[u],in[v]));
        }
        return ret;
    }
    void upd(int node, int l, int r, int v){
        if(l <= tree[node].s && tree[node].e <= r){
            tree[node].val=v;
            return;
        }
        if(tree[tree[node].lSon].e >= l)upd(tree[node].lSon,l,r,tp);
        if(tree[tree[node].rSon].s <= r)upd(tree[node].rSon,l,r,tp);
        tree[node].val = tree[tree[node].lSon].val + tree[tree[node].rSon].val;
    }
    void upd(int u, int v, int val){
       while(head[u] != head[v]){

            if(lvl[head[u]] > lvl[head[v]])swap(u,v);
            upd(1,in[head[v]], in[v], val);
            v = par[head[v]];
        }

        if(u != v){
          ///TODO
        }

    }

}

int main(){

  HLD::dfs0(1);
  HLD::dfs1(1);
  HLD::timer=0;
  HLD::build(1,n-1);

  return 0;
}
