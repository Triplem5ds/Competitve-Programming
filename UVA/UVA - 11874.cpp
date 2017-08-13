#include <bits/stdc++.h>
using namespace std;
 
int flyd[105][105];
 
int main(){
 
  ios_base::sync_with_stdio(0);
  cin.tie(0);
 
  int t;
 
  int cas = 0;
 
  cin >> t;
 
  while(t--){
 
    int n, m, p;
 
    cin >> n >> m >> p;
 
    for(int i  = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        flyd[i][j] = 1e9;
 
    while(m--){
 
      int x, y, a, b;
 
      cin >> x >> y >> a >> b;
 
      flyd[x][y] = min(flyd[x][y], p * b - a);
 
 
    }
 
    for(int k = 0; k < n; k++)
      for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
          flyd[i][j] = min(flyd[i][j], flyd[i][k] + flyd[k][j]);
 
 
    bool f = false;
 
    for(int i = 0; i < n; i++)
      f |= (flyd[i][i] < 0);
 
 
    cout << "Case "<<++cas<<": " << (f?"YES":"NO") << '\n';
 
 
  }
 
 
 
 
 
 
  return 0;
}
