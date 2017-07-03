#include <bits/stdc++.h>
using namespace std;

int main() {

  int n;

  cin >> n;

  vector<pair<pair<int, int>, int> >v(n);

  for(int i = 0; i < n; i++)
    cin >> v[i].first.first >> v[i].first.second, v[i].second = i + 1;

  sort(v.begin(), v.end());

  for(int i = 1; i < n; i+=2)
    cout << min(v[i].second, v[i-1].second) << ' ' << max(v[i].second, v[i-1].second) << '\n';

} 
