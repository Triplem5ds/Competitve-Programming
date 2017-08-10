#include <bits/stdc++.h>
using namespace std;

const long long N = 1e5 + 5;

long long t, n, q, type;

long long a[N];

map<long long, long long>mp;

vector<vector<long long> >adj;

bool vis[N];

int main(){

  scanf("%lld", &t);

  while(t--){

    memset(vis, 0, sizeof vis);

    set<long long>st;

    mp.clear();
    adj.clear();
    scanf("%lld%lld", &n, &q);
    adj.resize(n + 1);

    for(long long i = 1; i <= n; i++){
      scanf("%lld", a + i); mp[a[i]];
    }

    long long idx = 1;

    for(map<long long, long long> :: iterator it = mp.begin(); it != mp.end(); it++)
      it->second = idx++;

    for(long long i = 1; i <= n; i++){

      a[i] = mp[a[i]];
      adj[a[i]].push_back(i);

    }


    st.insert(0);
    st.insert(n + 1);

    long long ans;
    long long all = (n * 1ll * (n + 1) / 2);
    long long b4, lft, rt;

    while(q--){

      scanf("%lld", &type);

      type = mp[type];

      ans = b4 = 0;

      if(!vis[type]){

        vis[type] = true;

        for(long long i = 0; i < adj[type].size(); i++){

            long long v = adj[type][i];

            st.insert(v);

            set<long long> :: iterator it = st.find(v);
            set<long long> :: iterator itl = it;
            set<long long> :: iterator itr = it;
            itl--;
            itr++;

            lft = v - max(*itl, b4);
            rt = *itr - v;



            ans += lft * 1ll * rt;

            b4 = v;
        }


      }

      all -= ans;

      printf("%lld %lld\n", ans, all);

    }




  }


  return 0;
}
