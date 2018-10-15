#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;
const int N = 705;

ll adj[44], suffix[44];
int n, m;
bool bt(int idx, ll mask, int lft){
    if(mask == (1ll << n)-1){
        return true;
    }
    if(!lft)return false;
    for(int i = idx; i < n; i++)
        if(mask == (mask | adj[i]))continue;
        else if((1ll << n) - 1 != (mask | suffix[i]))
            return false;
        else if(bt(i+1,mask|adj[i],lft-1))
            return true;

}

int main(){

    while(cin >> n >> m && n){

        for(int i = 0; i < n; i++)
            adj[i] = (1ll << i);

        int u, v;
        for(int i = 0; i < m; i++){
            cin >> u >> v;  --u, --v;
            adj[u] |= (1ll << v);
            adj[v] |= (1ll << u);
        }

        suffix[n-1] = adj[n-1];

        for(int i =n-2;i >= 0; --i)
            suffix[i] = suffix[i+1] | adj[i];

        int lo = 1, hi = n;

        while(lo < hi){
            int md = lo + (hi-lo)/2;
            if(bt(0,0,md))
                hi=md;
            else
                lo = md + 1;
        }

        cout << lo << '\n';

    }


    return 0;
}
