#include <bits/stdc++.h>

using namespace std;

int grid[205][205];

int dx[] = {-1,1,0,0,-1,-1,1,1};
int dy[] ={0,0,-1,1,1,-1,-1,1};

int main(){

  int n, m;

  cin >> n >> m;

  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
      cin >> grid[i][j];

  set<int>st;

  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      if(grid[i][j]== -1)continue;
      for(int k  =0; k < 8; k++){

        if(grid[i][j] == grid[i+dx[k]][j+dy[k]])st.insert(grid[i][j]);

      }

    }


  }


  cout << st.size() << endl;

  return 0;
}
