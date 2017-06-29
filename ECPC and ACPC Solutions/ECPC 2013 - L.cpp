#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int ptr[26];
vector<vector<int> >adj;
int cas = 1;
int main(){

 freopen("mahdi.in", "r", stdin);

  int t;

  cin >> t;

  while(t--){


    char c;

    cin >> c;

    long long x, y, z;

    cin >> x >> y >> z;
    adj.clear();
    adj.resize(26);

    adj[c - 'a'].push_back(0);
    printf("Case %d:\n",cas++);


    for(long long i = 1; i < x; i++){
      char nxt = 'a' + (((c - 'a') * y + i * z) % 26);
      adj[nxt - 'a'].push_back(i);
      c = nxt;

    }

    //cout << 1 << '\n';


    int q;

    cin >> q;

    while(q--){
      cin >> c >> x >> y >> z;

      memset(ptr, 0, sizeof ptr);

      if(adj[c - 'a'].size() == 0){
        puts("REPEAT");
        continue;
      }

      bool f = true;

      int idx = adj[c-'a'][0];

      for(int i = 1; i < x; i++){
        char nxt = 'a' + (((c - 'a') * y + i * z) % 26);

        c = nxt;

        auto it = lower_bound(adj[c-'a'].begin(), adj[c-'a'].end(), idx + 1);

        if(it == adj[c-'a'].end()){
          f = false;
          break;
        }

        idx = adj[c-'a'][it - adj[c-'a'].begin()];

      }

      puts(f? "BRAVO" : "REPEAT");

    }



  }



  return 0;
}
