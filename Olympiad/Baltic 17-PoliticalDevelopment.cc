#include "bits/stdc++.h"
using namespace std;

const int N = 50000 + 5;
const int mod = 1e9 + 7;

/*
    observation since K <= 10
    the answer is always less than K
    so find the maximum clique where it's
    guaranteed that this clique size is < K
    so get the smallest node i am sure that it's adjacency list size is less than k
    and get all cliques with such nodes and check them then remove it and so on
    O(N * 2 ^ K * K ^ 2 * lgK)
*/

set<int>adj[N];
int n, k;
int main(){

    cin >> n >> k;

    for(int i = 0; i < n; i++){
        int sz; cin >> sz;
        for(int j = 0; j < sz; j++){
            int x;  cin >> x;
            adj[i].insert(x);
        }
        adj[i].insert(i);
    }

    set<pair<int,int>>st;

    for(int i = 0; i < n; i++){
        st.insert({adj[i].size(), i});
    }
    int ans = 0;
    while(st.size()){

        auto cur = st.begin()->second;
        st.erase(st.begin());

        vector<int>v;
        for(auto x : adj[cur])
            v.push_back(x);

        for(int i = 0; i < (1 << v.size()); i++){

            vector<int>tmp;
            for(int j = 0; j < v.size(); j++)if(i >> j & 1)
                tmp.push_back(v[j]);

            for(auto x : tmp)
                for(auto y : tmp)
                    if(adj[x].count(y) == 0)goto nxt;

            ans = max(ans, __builtin_popcount(i));
            nxt:;
        }
        vector<int>tmp = vector<int>(adj[cur].begin(), adj[cur].end());
        for(auto x : tmp){
            st.erase({adj[x].size(),x});
            adj[x].erase(cur);
            st.insert({adj[x].size(),x});
        }


    }

    cout << ans << '\n';


    return 0;
}
