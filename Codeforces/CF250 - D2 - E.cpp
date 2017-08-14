#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

char grid[105][10005];
int n, m;
int vis[105][10005][2];
int limit[105][10005][2];

typedef long long ll;

set<int> conc[105], brick[105], empt[105];

int dist(int i, int j){return abs(i - j);}

ll solve(int idx, int col, int gaze){

  //cout << idx << ' ' << col << ' ' << gaze << '\n';
  //system("pause");

  if(idx == n - 1)return 0;

  if(vis[idx][col][gaze] > limit[idx][col][gaze])return 1e13;

  vis[idx][col][gaze]++;

    int go_to, near_conc, near_brick;

    if(!gaze){
      go_to = *(empt[idx + 1].lower_bound(col));
      near_brick = *(brick[idx].lower_bound(col));
      near_conc = *(conc[idx].lower_bound(col));
    }
    else {
      go_to = *(--empt[idx + 1].lower_bound(col));
      near_brick = *(--brick[idx].lower_bound(col));
      near_conc = *(--conc[idx].lower_bound(col));
      if(grid[idx + 1][col] == '.')go_to = col;
    }

    if(dist(col, go_to) < min(dist(col, near_conc), dist(col, near_brick))){
      return 1 + dist(col, go_to) + solve(idx + 1, go_to, gaze);
    }

    if(dist(near_brick, col) < dist(near_conc, col)){
      brick[idx].erase(near_brick);
      return dist(near_brick, col) + solve(idx, near_brick + (gaze? 1 : -1), gaze ^ 1);
    }

    return dist(col, near_conc) + solve(idx, near_conc + (gaze? 1 : -1), gaze ^ 1);


}


int main(){

 ios_base::sync_with_stdio(0);cin.tie(0);

  cin >> n >> m;


  for(int i = 0; i < n; i++){
      grid[i][0] = grid[i][m + 1] = '#';
    for(int j = 1; j <= m; j++){
      cin >> grid[i][j];
      if(grid[i][j] == '.')empt[i].insert(j);
      else if(grid[i][j] == '+')brick[i].insert(j);
      else conc[i].insert(j);

      if(grid[i][j - 1] == '#')limit[i][j][0] = 20000;
      else limit[i][j][0] = 5;
      if(grid[i][j + 1] == '#')limit[i][j][1] = 20000;
      else limit[i][j][1] = 5;

    }
    conc[i].insert(0);
    conc[i].insert(m + 1);
    empt[i].insert(0);
    empt[i].insert(m + 1);
    brick[i].insert(0);
    brick[i].insert(m + 1);

  }

  ll ans = solve(0, 1, 0);

  if(ans > 1e13)return puts("Never");

  cout << ans << '\n';

  return 0;
}
