#include <bits/stdc++.h>
using namespace std;
/*
  there is a way more easier solution using two pointers and sets which i know, but
  i wanted to solve it this way to try a new trick.
  first you build a merge sort and a segment tree and you split the array into negative and positive.
  then for every segment find the k_th smallest or biggest number and flip the sign for all numbers
  below it i did that fast with accumlative sum so i would get the answer in O(1)
  then just query and find the maximum alot of container used for the sake of this solution.

*/
const int N = 1e5 + 5;
const int lg = 20;
typedef long long ll;
ll tree1[2][20][N];
ll tree2[2][4*N];
ll sm_tree1[2][20][N];
ll a[2][N], n, k, len, x;
ll tree_tanya[2][20][N], pos[2][N], Real[2][N];
void build(ll idx, ll node, ll nnode, ll s, ll e){
  if(s == e){
    tree1[idx][nnode][s] = a[idx][s];
    sm_tree1[idx][nnode][s] = a[idx][s];
    tree2[idx][node] = a[idx][s];
    return;
  }
  ll md = (s + e)>>1;
  build(idx, node << 1, nnode + 1, s, md);
  build(idx, node << 1 | 1, nnode + 1, md + 1, e);
  tree2[idx][node] = tree2[idx][node << 1] + tree2[idx][node << 1 | 1];
  ll i=s,j=md+1;
  ll ptr=0;

  while(i<=md&&j<=e){
        if(tree1[idx][nnode+1][i] < tree1[idx][nnode+1][j])
            tree1[idx][nnode][s+(ptr++)]=tree1[idx][nnode+1][i++];
        else
            tree1[idx][nnode][s+(ptr++)] = tree1[idx][nnode+1][j++];
  }
  while(i<=md)tree1[idx][nnode][s+(ptr++)]=tree1[idx][nnode+1][i++];
  while(j<=e)tree1[idx][nnode][s+(ptr++)]=tree1[idx][nnode+1][j++];

  for(ll i = s; i <= e; i++)
    sm_tree1[idx][nnode][i] = (i==s?0 : sm_tree1[idx][nnode][i-1]) + tree1[idx][nnode][i];
}
void init(ll idx, ll node, ll s, ll e){
  if(s == e){
    tree_tanya[idx][node][s] = pos[idx][s];
    return;
  }

  ll md = (s + e) >> 1;
  init(idx, node + 1, s, md);
  init(idx, node + 1, md + 1, e);
  ll i = s, j = md + 1;
  ll ptr = 0;
  while(i <=md && j <= e){
    if(tree_tanya[idx][node + 1][i] < tree_tanya[idx][node + 1][j])
      tree_tanya[idx][node][s + (ptr++)] = tree_tanya[idx][node + 1][i++];
    else
      tree_tanya[idx][node][s + (ptr++)] = tree_tanya[idx][node + 1][j++];

  }
  while(i <= md)tree_tanya[idx][node][s + (ptr++)] = tree_tanya[idx][node + 1][i++];
  while(j <= e)tree_tanya[idx][node][s + (ptr++)] = tree_tanya[idx][node + 1][j++];


}
pair<ll,ll>add(pair<ll, ll> x, pair<ll, ll> y){
  return {x.first + y.first, x.second + y.second};
}
pair<long long, long long> get_index(ll idx, ll node, ll s, ll e, ll l, ll r, ll target){

  if(r < s || e < l)return {0, 0};
  if(l <= s && e <= r){
      ll lo = s, hi = e;
      while(lo < hi){
        ll md = lo + (hi - lo + 1)/2;
        if(tree1[idx][node][md] < target)
          lo = md;
        else
          hi = md - 1;
      }
      if(tree1[idx][node][lo] >= target)return {0, 0};

      return {sm_tree1[idx][node][lo], lo - s + 1};
  }
  ll md = (s + e) >> 1;

  return add(get_index(idx, node + 1, s, md, l, r, target) , get_index(idx, node + 1, md + 1, e, l, r, target));
}
ll qry(ll idx, ll node, ll s, ll e, ll l, ll r){
  if(r < s || e < l)return 0;
  if(l <= s && e <= r)return tree2[idx][node];
  ll md = (s + e) >> 1;
  return qry(idx, node << 1, s, md, l, r) + qry(idx, node << 1 | 1, md + 1, e, l, r);
}
inline ll find(ll idx,ll node, ll s, ll e, ll l, ll r){
  return upper_bound(tree_tanya[idx][node] + s, tree_tanya[idx][node] + e + 1, r) - lower_bound(tree_tanya[idx][node] + s, tree_tanya[idx][node] + e + 1, l);
}
ll get(ll idx, ll n,ll l, ll r, ll kth){
    ll node = 0,s = 0, e = n - 1;
    while(s != e){
      ll go = find(idx,node + 1, s, (s + e) >> 1, l, r);
      ll md = (s + e) >> 1;
      if(go >= kth)
        e = md;
      else{
        s = md + 1;
        kth -= go;
      }
      node++;
    }
  return s;
}
map<int, int>mp1, mp2;
int main(){
  scanf("%lld%lld", &n, &len);
  vector<ll>s1, s2;
  for(ll i = 0; i < n; i++){
    scanf("%lld", &x);
    if(x < 0)a[0][i] = x;
    else if(x > 0)a[1][i] = -x;
    s1.push_back(a[0][i]);
    s2.push_back(a[1][i]);
  }
  scanf("%d", &k);

  sort(s1.begin(), s1.end());
  sort(s2.begin(), s2.end());


  k = min(k, len);

  build(0, 1, 0, 0, n - 1);
  build(1, 1, 0, 0, n - 1);

  memset(pos, -1, sizeof pos);

  for(ll i = 0; i < n; i++){
    ll old1 = a[0][i];
    ll old2 = a[1][i];
    mp1[a[0][i]]++;
    mp2[a[1][i]]++;

    a[0][i] = lower_bound(s1.begin(), s1.end(), a[0][i]) - s1.begin() + mp1[a[0][i]] - 1;
    a[1][i] = lower_bound(s2.begin(), s2.end(), a[1][i]) - s2.begin() + mp2[a[1][i]] - 1;
    pos[0][a[0][i]] = i;
    pos[1][a[1][i]] = i;
    Real[0][a[0][i]] = old1;
    Real[1][a[1][i]] = old2;
  }

  init(0, 0, 0, n - 1);
  init(1, 0, 0, n - 1);

  ll ans = 0;


  for(ll i = 0; i + len <= n; i++){
    ll all = qry(0, 1, 0, n -1, i, i + len - 1) +
      abs(qry(1, 1, 0, n -1, i, i + len - 1));
    if(!k){
      ans = max(ans,abs(all));
        continue;
    }
    ll target1 = get(0, n, i, i + len - 1, k);
    ll target2 = get(1, n, i, i + len - 1, k);
    target1 = Real[0][target1];
    target2 = Real[1][target2];
  //  cout << target1 << ' ' << target2 << '\n';
    auto it1 = get_index(0, 0, 0, n - 1, i, i + len - 1, target1);
    auto it2 = get_index(1, 0, 0, n - 1, i, i + len - 1, target2);
 //   cout << it1.first << ' ' << it2.first << '\n';
    ll sm1 = it1.first + (k - it1.second) * target1;
    ll sm2 = it2.first + (k - it2.second) * target2;
    //cout << all << ' ' << target1 << ' ' << target2 << '\n';
    //system("pause");
    ll org1 = sm1;
    ll org2 = sm2 * - 1;
    sm1 *= -1;
//   cout << sm1 << ' ' << sm2 << ' ' << org1 << ' ' << org2 << '\n';
 //   system("pause");
    ans = max(ans, max(abs(all - org1 + sm1), abs(all - org2 + sm2)));
  }

  cout << ans << '\n';


  return 0;
}
