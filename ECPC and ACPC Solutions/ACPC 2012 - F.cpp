#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;


int mp[12][12];
bool vis[12][12];
bool chk(pair<int, int>a, pair<int, int>b, int msk){
  int x = abs(a.first - b.first);
  int y = abs(a.second - b.second);
  if(x == 0){
    if(a.second > b.second)swap(a, b);
    a.second++;
    while(a != b){
      if(!(msk & (1 << mp[a.first][a.second])))return 0;
      a.second++;
    }
    return 1;
  }
  if(y == 0){
    if(a.first > b.first)swap(a, b);
    a.first++;
    while(a != b){
      if(!(msk & (1 << mp[a.first][a.second])))return 0;
      a.first++;
    }
    return 1;
  }
  if(x == y){
    if(a.first < b.first)
      a.first++;
    else
      a.first--;
    if(a.second < b.second)
      a.second++;
    else
      a.second--;

    while(a != b){
      if(!(msk & (1 << mp[a.first][a.second])))return 0;

    if(a.first < b.first)
      a.first++;
    else
      a.first--;
    if(a.second < b.second)
      a.second++;
    else
      a.second--;
    }
  }
  return 1;
}

long long dp[5][5][1<<13][100];


int L, n;

long long solve(int rw, int col, int dist, int msk){
    if(dist > L)return 0;
    if(dist == L)return 1;

    long long &ret = dp[rw][col][msk][dist];

    if(~ret)return ret;

    ret = 0;

    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 3; j++){

        if(!vis[i][j] && !(msk&(1 << mp[i][j])) && chk({rw, col}, {i, j}, msk)){

            ret += solve(i, j,dist + abs(i - rw) + abs(j - col) ,msk | (1<<mp[i][j]));
        }
      }
    }
  return ret;
}


int msk = 0;



void init(){
  mp[0][0] = 0;
  mp[0][1] = 1;
  mp[0][2] = 2;
  mp[1][0] = 3;
  mp[1][1] = 4;
  mp[1][2] = 5;
  mp[2][0] = 6;
  mp[2][1] = 7;
  mp[2][2] = 8;
  mp[3][0] = 9;
  mp[3][1] = 10;
  mp[3][2] = 11;
}

int main(){
  //ios_base::sync_with_stdio(0);
  //cin.tie(0);
  init();

  memset(dp, -1, sizeof dp);

  cin >> L >> n;

  if(L > 60)
    return puts("BAD MEMORY");

  for(int i = 0; i < n; i++){
    int x, y;

    cin >> x >> y;
    x--, y--;
    swap(x, y);
    vis[x][y] = true;
  }

  long long ans = 0;

  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 3; j++){
      if(!(msk&(1<<mp[i][j])) && !vis[i][j]){
        ans += solve(i,j,0,msk|(1<<mp[i][j]));
       // cout << i << ' ' << j << ' ' << ans << '\n';
       // system("pause");
      }
    }
  }


  if(!ans)return puts("BAD MEMORY");

  cout << ans << '\n';

}   
