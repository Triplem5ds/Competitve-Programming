#include <bits/stdc++.h>

#define ll long long

using namespace std;
const int N = 1e5 + 5;
int p[N], n, m, q;
int sz[N];
int x[N], y[N], z[N];
int a[N], b[N];
int lo[N], hi[N];
int get(int x){
    if(p[x]==x)return x;
    return p[x] = get(p[x]);
}
int ans[N];
void mrg(int u, int v){
    u = get(u); v = get(v);
    if(u == v)return;
    p[v] = u;
    sz[u] += sz[v];
}
vector<int> qry[2][N];
int main() {
    scanf("%d%d", &n, &m);

    for(int i = 0; i < m; i++){

        int u, v;   scanf("%d%d", &u, &v);  --u, --v;
        a[i] = u;   b[i] = v;
    }
    scanf("%d", &q);
    for(int i = 0; i < q; i++)
        scanf("%d%d%d",x+i,y+i,z+i), x[i]--, y[i]--;

    for(int i = 0; i < q; i++){
      lo[i] = 0, hi[i] = m-1;
      qry[0][lo[i] + (hi[i]-lo[i]) / 2].push_back(i);
    }

    for(int tr = 0; tr < 20; tr++){
        iota(p,p+n,0);
        fill(sz,sz+n,1);
        for(int i = 0; i < m; i++)
            qry[tr&1^1][i].clear();
        for(int i = 0; i < m; i++){
            mrg(a[i], b[i]);
            for(auto idx : qry[tr&1][i]){
                int a = get(x[idx]), b = get(y[idx]), c = z[idx];
                if((a == b && sz[a] >= c) || (a != b && sz[a] + sz[b] >= c)){
                    hi[idx] = i;
                }   else {
                    lo[idx] = i + 1;
                }
                if(lo[idx] < hi[idx])
                    qry[tr & 1 ^ 1][lo[idx] + (hi[idx] - lo[idx]) / 2].push_back(idx);
            }

        }

    }

    for(int i = 0; i < q; i++)
        printf("%d\n", lo[i] + 1);

	return 0;
}
