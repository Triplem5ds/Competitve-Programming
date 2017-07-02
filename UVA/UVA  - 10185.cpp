#include <bits/stdc++.h>
using namespace std;
string s[1024];
string ans;
int main(){
  int n, m;
  while(cin >> n >> m && n){

    for(int i = 0; i < n; i++)cin >> s[i];

    ans.clear();

    int out = 0;
    for(int i = 0; i < m; i++){
      vector<int>tree(n << 1);

      for(int j = n; j < (n << 1); j++)
        tree[j] = (1 << (s[j-n][i] - 'A'));
      for(int j = n - 1; j > 0; j--){
        tree[j] = tree[j<<1] & tree[j << 1 | 1];
        if(tree[j] == 0){
          out++;
          tree[j] = tree[j << 1] | tree[j << 1 | 1];
          //cout << tree[j] << '\n';
        }
      }

      for(int j = 0; j < 26; j++){
        if((tree[1] >> j) & 1){
          ans.push_back(j + 'A');
          break;
        }
      }
    }

    cout << ans << ' ' << out << '\n';

  }

  return 0;
}
