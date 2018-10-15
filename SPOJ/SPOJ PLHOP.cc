#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;
const int N = 705;

using mat = vector<vector<ll>> ;

mat init;
int k, n;

mat operator * (mat x, mat y){
    mat ret = mat(n, vector<ll>(n, LLONG_MAX));
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                ret[i][j] = min(ret[i][j], x[i][k] + y[k][j]);
    return ret;
}

mat fast(mat b, int e){
    if(e ==1)return b;
    if(e&1)return b * fast(b, e - 1);
    return fast(b * b, e >> 1);
}

int main(){

    int t;  scanf("%d", &t);
    int cas =0;
    while(t--){
        scanf("%d%d", &k, &n);

        init = mat(n,vector<ll>(n, 0));

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%lld", &init[i][j]);

        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    init[i][j] = min(init[i][j], init[i][k] + init[k][j]);

        printf("Region #%d:\n", ++cas);

        init = fast(init, k);

        for(int i = 0; i < n; i++)
            for(int j =0; j < n; j++)
                cout << init[i][j] << " \n"[j+1==n];

    }


    return 0;
}
