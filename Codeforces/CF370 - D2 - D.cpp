#include <bits/stdc++.h>
using namespace std;

int n, m;
char grid[2005][2005];
int cnt, sv[2005][2005];
set<int>row;
set<int>col;
int get(int i, int j, int x, int y){
  return sv[x][y] - sv[x][j - 1] - sv[i - 1][y] + sv[i - 1][j - 1];
}
bool chk(int x, int y, int limit){
    if(x + limit > n || y + limit > m)return 0;
    if(limit == 0)return cnt == 1 && grid[x][y] == 'w';
    int bl_x = x + limit;
    int bl_y = y + limit;
    int t = get(x, y + 1, x, bl_y);
    int b = get(bl_x,y, bl_x, bl_y - 1);
    int l = get(x,y,bl_x - 1,y);
    int r = get(x + 1,bl_y,bl_x,bl_y);
    return t + b + l + r == cnt;
}
int x, y;
int tst_row(){


  int lft = *row.begin();
  int rt = *(--row.end());

  int ans = rt - lft;

  //cout << chk(1, 3, 3) << endl;

  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
      if(chk(i, j, ans)){
        x = i, y = j;
        return ans;
      }

  return INT_MAX;

}
int tst_col(){

  int lft = *col.begin();
  int rt = *(--col.end());

  int ans = rt - lft;

  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
      if(chk(i, j, ans)){
        x = i, y = j;
        return ans;
      }



  return INT_MAX;
}


int main(){

  scanf("%d%d", &n, &m);

  for(int i = 1; i <= n; i++){

    for(int j = 1; j <= m; j++){
      scanf(" %c", &grid[i][j]);


      if(grid[i][j] == 'w')sv[i][j] = 1, cnt++;

      sv[i][j] += sv[i-1][j] + sv[i][j-1] - sv[i-1][j-1];

      if(grid[i][j] == 'w')row.insert(i), col.insert(j);


    }

  }


  int ans = INT_MAX;

  ans = min(ans, tst_row());
  ans = min(ans, tst_col());



  if(ans == INT_MAX)return puts("-1");



  for(int i = y; i <= y + ans; i++)
    if(grid[x][i] != 'w')grid[x][i] = '+';
  for(int i = y; i <= y + ans; i++)
    if(grid[x + ans][i] != 'w')grid[x + ans][i] = '+';
  for(int i = x; i <= x + ans; i++)
    if(grid[i][y] != 'w')grid[i][y] = '+';
  for(int i = x; i <= x + ans; i++)
    if(grid[i][y + ans] != 'w')grid[i][y + ans] = '+';

  for(int i = 1; i <= n; i++, puts(""))
    for(int j = 1; j <= m; j++)
      putchar(grid[i][j]);

  return 0;
}
