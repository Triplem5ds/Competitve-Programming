#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;

int dp[N][2][2][2][2], n;

string s[N];

int solve(int idx, bool lft, bool rt, bool bl, bool br){

  if(idx == n)return 0;

  int &ret = dp[idx][lft][rt][bl][br];

  if(~ret)return ret;

  ret = N * 100;


  if(s[idx][0] == s[idx][1])
    ret = min(ret , solve(idx + 1, 0, 0, 0, 0));





}

int main(){

  int t;

  cin >> t;

  while(t--){
    memset(dp, -1, sizeof dp);

    cin >> n;

    for(int i = 0; i < n; i++)
      cin >> s[i];

    s[n] = "##";

    cout << solve(0, 0, 0, 0, 0) << '\n';

  }




  return 0;
}
