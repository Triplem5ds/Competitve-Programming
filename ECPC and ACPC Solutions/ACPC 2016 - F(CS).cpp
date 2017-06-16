#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;

string s[N];
int dp[N][2][2], n;


int solve(int idx, bool b4, bool can){
  //cout << idx << ' ' << b4 << ' ' << can << '\n';
  //system("pause");

  //can then i can connect these two together
  //b4 then the ones before me are connected together
  if(idx == n)return 0;
  int &ret = dp[idx][b4][can];

  if(~ret)return ret;

  ret = N * 4;

  if(can && s[idx][0] == s[idx][1])
    ret = min(ret,solve(idx + 1, 1, 1));

  if(!b4 && s[idx][0] == s[idx-1][0])
    ret = min(ret, 1 + solve(idx + 1, 0, 1));
  if(!b4 && s[idx][1] == s[idx-1][1])
    ret = min(ret, 1 + solve(idx + 1, 0, 1));
  if(!b4 && s[idx][1] == s[idx-1][1] && s[idx][0] == s[idx-1][0])
    ret = min(ret, solve(idx + 1, 0, 1));
  ret = min(ret, 2 + solve(idx + 1, 0, 1));
  if(s[idx][1] == s[idx+1][1])
    ret = min(ret, 1 + solve(idx + 1, 0, 0));
  if(s[idx][0] == s[idx+1][0])
    ret = min(ret, 1 + solve(idx + 1, 0, 0));

  //can el fel 25r

  if(s[idx][0] == s[idx+1][0] && s[idx][1] == s[idx + 1][1])
    ret = min(ret, solve(idx + 1, 0, 0));

  if(!b4 && s[idx][0] == s[idx+1][0] && s[idx-1][1] == s[idx][1])
    ret = min(ret, solve(idx + 1, 0, 0));
  if(!b4 && s[idx][0] == s[idx-1][0] && s[idx+1][1] == s[idx][1])
    ret = min(ret, solve(idx + 1, 0, 0));

  return ret;
}


int main(){

  int t;

  cin >> t;

  while(t--){
    cin >> n;

    for(int i = 0; i < n; i++)
      cin >> s[i];

    s[n] = "##";

    memset(dp, -1, sizeof dp);

    cout << solve(0, 1, 1) << '\n';

  }
  return 0;
}

