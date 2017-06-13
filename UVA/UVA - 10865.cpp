#include <bits/stdc++.h>
using namespace std;
const int N = 2e5  + 5;

long long x[N], y[N];
/*
  the idea is that it's optimal to always draw the two lines at the brownie in the center
  then use the dx. dy to know what kind of brownie is it.
*/
int n;

int main(){


  while(cin >> n&&n){

    for(int i = 0; i < n; i++)
      cin >> x[i] >> y[i];

    int s = 0, o = 0;

    for(int i = 0;  i < n; i++){
      long long dx = x[i] - x[n>>1];
      long long dy = y[i] - y[n>>1];

      if(dx == 0 || dy == 0)continue;

      if(dx * dy > 0)s++;
      else o++;


    }

    cout << s << ' ' << o << '\n';

  }



  return 0;
}
