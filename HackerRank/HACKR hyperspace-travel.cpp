#include <bits/stdc++.h>
using namespace std;

/*
  the answer for each dimension is separate
  ternary search the answer for each dimension
*/
int n, m, x;
vector<int>ans;
vector<int>dimen[104];

long long chk(int idx, int p){

  long long ret = 0;

  for(int i = 0; i < n; i++){
    ret += abs(dimen[idx][i] - p);
  }
  return ret;

}


int main(){

  cin >> n >> m;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin >> x;
      dimen[j].push_back(x);
    }
  }

  for(int i = 0; i < m; i++){
    int lo = -1e9, hi = 1e9;

    while(lo < hi){
      int md = lo + (hi - lo)/2;
      if(chk(i, md) <= chk(i, md + 1))hi = md;
      else lo = md + 1;

    }
    ans.push_back(lo);
  }

  for(int i = 0; i < m; i++)
    cout << ans[i] << " \n"[i + 1 == m];


  return 0;
}
