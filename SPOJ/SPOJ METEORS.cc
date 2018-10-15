#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;
const int N = 3e5+5;

int lo[N], hi[N];
int n, m, k;
int a[N];   ///Meteor States
int cap[N]; ///Cap for each meteor
int l[N], r[N], add[N];
int val[N];
/*
    If i parallel binary search how should i handle
    the L[i], R[i] updates with segment tree
*/
vector<int> corrsponds[N];
int ans[N];
vector<int> qu[2][N];
ll bit[N];
void upd(int idx, int v){
    for(idx++; idx < N; idx += idx & -idx)
        bit[idx] += v;
}
void upd(int l, int r, int v){
    upd(l,v);
    upd(r+1,-v);
}
ll qry(int idx){
    ll ret = 0;
    for(idx++; idx; idx -= idx & -idx)
        ret += bit[idx];
    return ret;
}
int main(){
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE

    memset(ans,-1,sizeof ans);

    scanf("%d%d", &n, &m);

    for(int i = 0; i < m; i++){
        scanf("%d", a + i); --a[i];
        corrsponds[a[i]].push_back(i);
    }

    for(int i = 0; i < n; i++)
        scanf("%d", cap + i);
    scanf("%d", &k);

    for(int i = 0; i < k; i++)
        scanf("%d%d%d", l + i, r + i, add + i), --l[i], --r[i];

    for(int i = 0; i < n; i++){
        hi[i] = k;
        qu[0][(lo[i]+hi[i]) >> 1].push_back(i);
    }


    for(int i = 0; i < 20; i++){
        for(int j = 0; j < k; j++)qu[i&1^1][j].clear();
        for(int j = 0; j < k; j++){
            if(l[j] <= r[j])
                upd(l[j],r[j],add[j]);
            else
                upd(l[j],m-1,add[j]),
                upd(0,r[j],add[j]);
            for(auto v : qu[i&1][j]){
                ll sum = 0;
                for(auto x : corrsponds[v]){
                    sum += qry(x);
                    if(sum >= cap[v])break;
                }

                if(sum >= cap[v])
                    hi[v] = j;
                else
                    lo[v] = j + 1;

                if(lo[v] < hi[v])
                    qu[i&1^1][(lo[v]+hi[v])>>1].push_back(v);
            }
        }

        for(int j = 0; j < k; j++){
            if(l[j] <= r[j])
                upd(l[j],r[j],-add[j]);
            else
                upd(l[j],m-1,-add[j]),
                upd(0,r[j],-add[j]);
        }

    }

    for(int i = 0; i < n; i++)
        if(lo[i] == k)
            puts("NIE");
        else
            printf("%d\n", lo[i]+1);


    return 0;
}
