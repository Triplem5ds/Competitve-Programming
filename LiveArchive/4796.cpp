#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

int tree[N], a[N], L[N], R[N], n;

map<int, int>mp;

int idx;

int get(int id){
  int ret = 0;
  for(; id > 0; id -= (id & -id)){
 //   cout << id  << ' ';
    ret = max(ret, tree[id]);
  }
  return ret;
}

void update(int id, int v){

  for(; id <= idx; id += (id & -id))
    tree[id] = max(tree[id], v);
}
int main(){

  int t;

  scanf("%d", &t);

  while(t--){
    memset(L, 0, sizeof L);
    memset(R, 0, sizeof R);
    memset(tree, 0, sizeof tree);
    mp.clear();
    idx = 0;

    scanf("%d", &n);

    for(int i = 0; i < n; i++)
      scanf("%d", a + i), mp[a[i]];

    for(auto it : mp)
      mp[it.first] = idx++;

    for(int i = 0; i < n; i++)
      a[i] = mp[a[i]];

    for(int i = 0; i < n; i++){
      if(a[i] > a[i-1])
        L[i] = L[i-1] + 1;
      else
        L[i] = 1;
    }


    for(int i = n - 1; i >= 0; i--){
      if(a[i] < a[i+1])
        R[i] = R[i+1] + 1;
      else
        R[i] = 1;
    }


    int mx = 0;

    for(int i = 0; i < n; i++){
      mx = max(mx, get(a[i]) + R[i]);
      update(a[i] + 1,L[i]);
    }

    cout << mx << '\n';

  }
}
