#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef long double db;
db grid[605][605];
int L[605], R[605];
int n;
vector<pair<int, db> > dfs(int cur){
  //cout << cur << '\n';
  //system("pause");
  vector<pair<int, db> >ret;
  if(cur <= n){
    ret.push_back({cur, 1});
    return ret;
  }
  auto lft = dfs(L[cur]);
  auto rt = dfs(R[cur]);

  for(int i = 0; i < lft.size(); i++){
    double prop = 0;
    for(int j = 0; j < rt.size(); j++)
      prop += lft[i].second * rt[j].second * grid[lft[i].first][rt[j].first];
    ret.push_back({lft[i].first,prop});
  }
  for(int i = 0; i < rt.size(); i++){
    double prop = 0;
    for(int j = 0; j < lft.size(); j++)
      prop += rt[i].second * lft[j].second * grid[rt[i].first][lft[j].first];
    ret.push_back({rt[i].first,prop});
  }

  return ret;

}
int main(){

//  cin >> n >> m >> g;
  while(cin >> n && n){
    for(int i = 1; i <= n; i++)
      for(int j = 1; j <= n; j++)
        cin >> grid[i][j];
      int in[605] = {};
    for(int i = n + 1; i < 2 * n; i++){
      cin >> L[i] >> R[i];
      in[L[i]]++;
      in[R[i]]++;

    }

    for(int i = 1; i < 2 * n; i++){
      if(in[i] == 0){
        auto cur = dfs(i);

        for(auto v : cur){
          if(v.first == 1)
            cout << fixed << setprecision(6) << v.second << '\n';
        }
        break;
      }
    }

  }




  return 0;
}
