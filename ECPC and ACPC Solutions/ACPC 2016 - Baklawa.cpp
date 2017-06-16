#include <bits/stdc++.h>
using namespace std;
vector<pair<int, pair<int, int> > >a;
int x, y, z, n;
vector<int>v;
bool chk(int limit){
  for(int i = 0; i < n; i++)
    if(a[i].first <= limit)
      return 0;
  return 1;
}
bool chk2(int limit){
  for(int i = 0; i < n; i++)
    if(a[i].first > limit)
      return 0;
  return 1;
}
void solve(){
  int lo = 0, hi = x;
  while(lo < hi){
    int md = lo + (hi - lo + 1)/2;
    if(chk(md))
      lo = md;
    else
      hi = md - 1;
  }
  v.push_back(lo);
  lo = 0, hi = x;
  while(lo < hi){
    int md = lo + (hi - lo)/2;
    if(chk2(md))
      hi = md;
    else
      lo = md + 1;
  }
  v.push_back(x - lo);
}
int main(){
  int t;
  cin >>t;
  while(t--){
    scanf("%d%d%d%d", &x, &y, &z, &n);
    int ans = 0;
    if(!n){
        ans ^= (x - 1);
        ans ^= (y - 1);
        ans ^= (z - 1);
    }
    v.clear();
    a.clear();
    a.resize(n);
    for(int i = 0; i <n ; i++)
      scanf("%d%d%d", &a[i].first, &a[i].second.first, &a[i].second.second);
    solve();
    swap(x, y);
    for(int i = 0; i < n; i++)
      swap(a[i].first, a[i].second.first);
    solve();
    swap(x,z);
    for(int i = 0; i < n; i++)
      swap(a[i].first, a[i].second.second);
    solve();
    for(int i = 0; i < 6; i++)
      ans ^= v[i];
    puts(ans? "Alice" :"Bob");
  }
}
