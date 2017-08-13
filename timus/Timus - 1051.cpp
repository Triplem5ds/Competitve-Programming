#include <bits/stdc++.h>

using namespace std;

int n;
int t;
int m;




int main(){

  int n, m;

  cin >> n >> m;

  if(n == 1)cout << (m + 1)/2 << endl;
  else if(m == 1)cout << (n + 1)/2 << endl;
  else if(n%3 == 0 || m % 3 == 0)cout << 2 << endl;
  else cout << 1 << endl;


  return 0;
}
