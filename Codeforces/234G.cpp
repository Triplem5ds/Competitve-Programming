#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define ios ios_base::sync_with_stdio(0);cin.tie(0);
typedef long long ll;
/*
  the main idea is that for a number which is a power of 2 you need every time to change every 2 ^ i
  meaning for a number like 8 you will divide them 4 and 4 then divide 2 - 2 - 2 - 2 and swap the second and fourth
  and then divide them to 8 and swap the odd numbers.
*/
int n;


int main(){

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  cin >> n;

  int tmp = ((int)ceil(log2(n)));

  cout << tmp << '\n';

  tmp = (1 << tmp);
  tmp/=2;

  while(tmp){
    vector<int>team;
    int i = 0;
    for( ; i < n; ){
        for(int j = i; j < min(i + tmp, n); j++)
          team.push_back(j + 1);
        i+=(tmp * 2);
    }
    cout << team.size();
    for(int i = 0; i < team.size(); i++)
      cout << ' ' << team[i];
    puts("");
    tmp/=2;
  }

}
