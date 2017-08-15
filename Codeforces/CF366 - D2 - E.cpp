#include <bits/stdc++.h>
using namespace std;

int n, m, k, s;
int a[2005][2005];

int song[100005];

short int ret = 0;

short int ans[10][10];

pair<short int, pair<short int, short int> >sv[4][10];
pair< short int, pair< short int, short int> >sv2[4][10];
int x;

short int dist(short int x, short int y, short int i, short int j){

  if(i > n || i < 0 || j > m || j < 0)return 0;

  return abs( x - i ) + abs( j - y );

}

int main(){

  scanf("%d%d%d%d", &n, &m, &k, &s);


  for(int i = 0; i < 4; i++)
    for(int j = 1; j <= k; j++)
      sv[i][j] = {-1, {-1, -1}},
        sv2[i][j] = {5000, {5000, 5000}};

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      scanf("%d", &x);

      sv[0][x] = max(sv[0][x], {-i-j,{i,j}});
      sv[1][x] = max(sv[1][x], {i-j,{i,j}});
      sv[2][x] = max(sv[2][x], {-i+j,{i,j}});
      sv[3][x] = max(sv[3][x], {i+j,{i,j}});
      sv2[0][x] = min(sv2[0][x], {-i-j,{i,j}});
      sv2[1][x] = min(sv2[1][x], {i-j,{i,j}});
      sv2[2][x] = min(sv2[2][x], {-i+j,{i,j}});
      sv2[3][x] = min(sv2[3][x], {i+j,{i,j}});



      for(int f = 0; f < 4; f++){

        for(int f1 = 1; f1 <= k; f1++){

          ans[x][f1] = max(ans[x][f1], dist(i, j, sv[f][f1].second.first, sv[f][f1].second.second));
          ans[x][f1] = max(ans[x][f1], dist(i, j, sv2[f][f1].second.first, sv2[f][f1].second.second));
          ans[f1][x] = max(ans[x][f1], dist(i, j, sv[f][f1].second.first, sv[f][f1].second.second));
          ans[f1][x] = max(ans[x][f1], dist(i, j, sv2[f][f1].second.first, sv2[f][f1].second.second));

        }

      }

    }
  }

  int bck;

  for(int i = 0; i < s; i++){
    scanf("%d", &x);
    if(i)ret = max(ret, ans[x][bck]);
    bck = x;
  }


  printf("%d\n", ret);


  return 0;
}
