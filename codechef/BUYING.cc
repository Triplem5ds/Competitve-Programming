#include "bits/stdc++.h"
using namespace std;

using ll = long long;

int cas;
ll dp[20][405][20];
int vis[20][405][20];
ll dp2[20][405][20];
int vis2[20][405][20];
vector<int> sv1[22], sv2[22];
int a[50005], n, m, k;
int sv[50005];
ll solve1(int idx, int rem, int m){
//  cout << idx << ' ' << rem << ' ' << m << '\n';
  if(m < 0)m += k;
  if(rem == 0)
    return m ? -1e15 : 0;
  if(idx == k)
    return -1e15;
  ll &ret = dp[idx][rem][m];
  if(vis[idx][rem][m] == cas)return ret;
  vis[idx][rem][m] = cas;
  ret = solve1(idx+1,rem,m);
  ll cur = 0;
  int tmp = 0;
  for(int i = 0; i < min((int)sv1[idx].size(), min(rem,k)); i++){
    tmp += sv[sv1[idx][i]];  if(tmp >= k)tmp -= k;
    cur += a[sv1[idx][i]];
    ret = max(ret, solve1(idx+1,rem-i-1,m-tmp) + cur);
  }
  return ret;
}
ll solve2(int idx, int rem, int m){
  if(m < 0)m += k;
  if(rem == 0)
    return m ? 1e15 : 0;
  if(idx == k)
    return 1e15;
  ll &ret = dp2[idx][rem][m];
  if(vis2[idx][rem][m] == cas + 1)return ret;
  vis2[idx][rem][m] = cas + 1;
  ret = solve2(idx+1,rem,m);
  ll cur = 0;
  int tmp = 0;
  for(int i = 0; i < min((int)sv2[idx].size(), min(rem,k)); i++){
    tmp += sv[sv2[idx][i]];  if(tmp >= k)tmp -= k;
    cur += a[sv2[idx][i]];
    ret = min(ret, solve2(idx+1,rem-i-1,m-tmp) + cur);
  }
  return ret;
}

bool cmp(int x, int y){
  return a[x] < a[y];
}
int main() {

  int t;  scanf("%d", &t);

  while(t--){

    scanf("%d%d%d", &n, &m, &k);

    for(int i = 0; i < n; i++)scanf("%d", a + i);
    sort(a,a+n);
    for(int i = 0; i < n; i++)sv[i] = a[i] % k;

    ll sum = 0, md = 0;
    for(int i = 0; i < m; i++){
      sum += a[i];
      md += sv[i];
      if(md >= k)md -= k;
      sv1[sv[i]].push_back(i);
    }
    for(int i = 0; i < k; i++)reverse(sv1[i].begin(), sv1[i].end());

    for(int i = m; i < n; i++)sv2[sv[i]].push_back(i);

    ll out = 1e15;

    cas += 2;

    for(int i = 0; i <= min(m,k * k); i++)
      for(int x = 0; x < k; x++)
        for(int y = 0; y < k; y++){
          int tmp = md - x + y;
          if(tmp < 0)tmp += k;
          if(tmp >= k)tmp -= k;
          if(tmp == 0){
            ll a = solve1(0,i,x);
            ll b = solve2(0,i,y);
            if(a >= 0 && b <= 1e15)
              out = min(out,sum-a+b);
          }
        }
    if(out == 1e15)out =-1;
    printf("%lld\n", out);
    for(int i = 0; i < k; i++)sv1[i].clear(),sv2[i].clear();
  }

  return 0;
}
