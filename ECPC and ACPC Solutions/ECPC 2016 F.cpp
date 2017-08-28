#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

inline int read(int &x){
    char c; x = 0;
    c = getchar();
    while(!isdigit(c))c = getchar();
    while(isdigit(c))x = x * 10 + (c - '0'), c = getchar();
}

int main(){

    freopen("bishops.in", "r", stdin);

    int T;

    for(read(T); T--; ){

        int n, m, C;
        read(n);read(m);read(C);

        vector<vector<pair<ll, ll> > > V(4 * n);

        for(int i = 0; i < m; i++){

            int r, c, p;
            read(r);read(c);read(p);
            ll x = p * 1ll *  p;
            V[r + c].push_back({x + r, -x + r + 1 - C});
            V[r - c + 3 * n - 2].push_back({x + r, -x + r + 1 - C});

        }

        int ans = 0;

        for(auto &v : V){

            if(v.size() == 0)continue;

            sort(v.begin(), v.end());
            int cnt = 1, cur = 0;
            for(int i = 1; i < v.size(); i++){

                if(v[i].second >= v[cur].first){

                    cnt++;
                    cur = i;
                }

            }

            ans = max(ans, cnt);


        }
        printf("%d\n", ans);


    }




    return 0;
}
