#include <bits/stdc++.h>
using namespace std;
int dx[8] = {-1,1,-2,2,-2,2,-1,1};
int dy[8] = {-2,-2,-1,-1,1,1,2,2};
bool vis[30][30];
string ans = "";
int n, m;
string con(int x){
  stringstream ss;
  ss << x;
  string s;
  ss >> s;
  return s;
}
bool chk(int x, int y){
  if(x >= n || x < 0 || y >= m || y < 0 || vis[x][y])return 0;
  return 1;
}
string conv(int x, int y){
  char c = 'A' + y;
  string ret;
  ret.push_back(c);
  x++;
  ret += con(x);
  return ret;
}
bool dfs(string path, int x, int y, int cnt){
  if(cnt == n * m){
      cout << path << '\n';
    return true;
  }
  int nx, ny;
 
  for(int i = 0; i < 8; i++){
    nx = x + dx[i], ny = y + dy[i];
    if(!chk(nx, ny))continue;
    vis[nx][ny] = 1;
    //cout << nx << ' ' << ny << '\n';
    //system("pause");
    if(dfs(path + conv(nx, ny), nx, ny, cnt + 1))return true;
    vis[nx][ny] = 0;
  }
 
  return false;
 
}
bool solve(){
 
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      memset(vis, 0, sizeof vis);
      vis[i][j] = 1;
 
      if(dfs(conv(i, j),i, j, 1))return true;
      vis[i][j] = 0;
    }
 
  }
  return false;
 
}
int main() {
  int t;
 
  cin >> t;
 
  while(t--){
    memset(vis, 0, sizeof vis);
 
    cin >> n >> m;
 
    if(!solve())puts("-1");
 
  }
 
}
 
