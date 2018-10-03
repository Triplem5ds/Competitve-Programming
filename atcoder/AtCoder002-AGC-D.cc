#include <bits/stdc++.h>

#define ll long long

using namespace std;
const int N = 1e5 + 5;
const int blk = 320;
int p[N], n, m, q;
vector<int>inBlk[blk];
int mark[N], sz[N];
int x[N], y[N], z[N];
int a[N], b[N];
int get(int x){
    if(p[x]==x)return x;
    return p[x] = get(p[x]);
}
void mrg(int u, int v){
    u = get(u); v = get(v);
    if(u == v)return;
    p[v] = u;
    sz[u] += sz[v];
}

int main() {
    scanf("%d%d", &n, &m);
    fill(sz,sz+n,1);
    memset(mark, -1, sizeof mark);
    iota(p,p+n,0);
    for(int i = 0; i < m; i++){

        int u, v;   scanf("%d%d", &u, &v);  --u, --v;
        a[i] = u;   b[i] = v;
    }
    scanf("%d", &q);
    int sq = ceil(sqrt(m+0.));

    for(int i = 0; i < q; i++)
        scanf("%d%d%d",x+i,y+i,z+i), x[i]--, y[i]--;


    for(int i = 0; i * sq < m; i++){


        for(int j = i * sq; j < min(m,i*sq + sq); j++)
            mrg(a[j], b[j]);

        for(int j = 0; j < q; j++)if(mark[j] == -1){
            int a = get(x[j]), b = get(y[j]);
            if(a == b && sz[a] >= z[j]){
                mark[j] = i;
            }   else if(a != b && sz[a] + sz[b] >= z[j]){
                mark[j] = i;
            }
        }


    }
    for(int i = 0; i < q; i++){
        inBlk[mark[i]].push_back(i);
    }

    memset(mark, -1, sizeof mark);
    fill(sz,sz+n,1);
    iota(p,p+n,0);

    for(int i = 0; i < m; i++){
        mrg(a[i], b[i]);
        for(auto idx : inBlk[i/sq])if(mark[idx] == -1){
            int a = get(x[idx]), b = get(y[idx]);
            if(a == b && sz[a] >= z[idx]){
                mark[idx] = i;
            }   else if(a != b && sz[a] + sz[b] >= z[idx]){
                mark[idx] = i;
            }
        }
    }

    for(int i = 0; i < q; i++)
        printf("%d\n", mark[i]+1);


	return 0;
}
