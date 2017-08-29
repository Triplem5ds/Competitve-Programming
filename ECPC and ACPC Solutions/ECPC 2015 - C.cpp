#include "bits/stdc++.h"
using namespace std;

map<int, map<int, int> >mp;

int n, m, t;

struct dsu{

    vector<int>par;
    vector<int>rnk;

    dsu(int n){

        rnk.assign(n, 1);

        for(int i = 0; i < n; i++)
            par.push_back(i);

    }

    int get1(int i){
        return i == par[i]? i : get1(par[i]);
    }
    int get2(int i, int limit){
        return i == limit? 0 : max(mp[i][par[i]], get2(par[i], limit));
    }

    bool same(int u, int v){
        return get1(u) == get1(v);
    }

    void merge(int u, int v, int tm){

        u = get1(u);
        v = get1(v);

        if(u == v)return;

        if(rnk[u] > rnk[v])swap(u, v);

        par[u] = v;
        rnk[v] += rnk[u];
        mp[u][v] = tm;

    }

    int get_lca(int u, int v){

        set<int>st;


        while(true){

            st.insert(u);
            if(u == par[u])break;
            u = par[u];
        }

        while(true){

            if(st.find(v) != st.end())return v;

            v = par[v];

        }

        return -1;


    }


};

int main(){

    for(scanf("%d", &t); t--; ){

        mp.clear();

        scanf("%d%d", &n, &m);

        int tp, u, v;

        dsu tree = dsu(n);

        for(int i = 1; i <= m; i++){

            scanf("%d%d%d", &tp, &u, &v);

            u--, v--;

            if(tp == 1)
                tree.merge(u, v, i);
            else{

                if(!tree.same(u, v))
                    puts("-1");
                else{

                    int lca = tree.get_lca(u, v);

                    assert(lca != -1);

                    printf("%d\n", max(tree.get2(u, lca), tree.get2(v, lca)));

                }


            }


        }


    }



    return 0;
}
