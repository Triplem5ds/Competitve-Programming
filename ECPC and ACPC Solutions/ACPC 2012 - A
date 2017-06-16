#include <bits/stdc++.h>
using namespace std;
int t, C, V;
int main(){
  scanf("%d", &t);
  while(t--){
    scanf("%d%d", &C, &V);
    vector<vector<int> >a(V, vector<int>(C,0));
    for(int i = 0; i < V; i++)
      for(int j = 0; j < C; j++)
        scanf("%d", &a[i][j]), a[i][j]--;
    vector<int>cur(C, 0);
    for(int i = 0; i < V; i++)
      cur[a[i][0]]++;
    int idx = -1;
    for(int i = 0; i < C;i++){
      if(cur[i] > V/2)
        idx = i;
    }
    if(idx != -1){
      printf("%d 1\n", idx + 1);
      continue;
    }
    int mx = 0;
    idx = -1;
    for(int i = 0; i < C; i++){
      if(cur[i] > mx)
        idx = i, mx = cur[i];
    }
    vector<int>v;
    v.push_back(idx);
    cur[idx] = 0;
    mx = 0, idx = -1;
    for(int i = 0; i < C; i++){
      if(cur[i] > mx)
        idx = i, mx = cur[i];
    }
    v.push_back(idx);
    cur.clear();
    cur.assign(C, 0);
    for(int i = 0; i < V; i++){
      for(int j = 0; j < C; j++){
        if(a[i][j] == v[0]){
          cur[v[0]]++;
          break;
        }
        if(a[i][j] == v[1]){
          cur[v[1]]++;
          break;
        }
      }
    }
    if(cur[v[0]] > cur[v[1]])
      printf("%d 2\n", v[0] + 1);
    else
      printf("%d 2\n", v[1] + 1);
  }
  return 0;
}
