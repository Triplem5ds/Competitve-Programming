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
            V[r - c + 3 * n - 2
