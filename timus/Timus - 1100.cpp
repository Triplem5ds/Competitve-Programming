#include <bits/stdc++.h>

using namespace std;

pair<int, pair<int, int> >a[150005];

int n;


int main(){


  scanf("%d", &n);

  for(int i = 0; i < n; i++)
    scanf("%d%d", &a[i].second.second, &a[i].first), a[i].second.first = -i;

  sort(a, a + n);
  reverse(a, a + n);



  for(int i = 0; i < n; i++)
    printf("%d %d\n", a[i].second.second, a[i].first);


  return 0;
}
