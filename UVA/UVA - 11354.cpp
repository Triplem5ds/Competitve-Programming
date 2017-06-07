#include <bits/stdc++.h>
using namespace std;
struct PT{
  int x, y;
};
int main(){
  int t;
  cin >> t;
  int cas = 0;
  while(t--){
    int n;
    int i, j, k, l;
    PT a, b, c, d;

    cin >> n;

    cin >> a.x >> a.y >> b.x >> b.y;

    i = a.x, j = a.y, k = b.x, l = b.y;

    bool flag = true;

    for(int idx = 1; idx < n; idx++){

      cin >> c.x >> c.y >> d.x >> d.y;
      i = max(a.x, c.x), j =max(a.y, c.y);
      k = min(b.x, d.x), l = min(b.y, d.y);
      if(i >=k || j >= l)
        flag = false;
      else
        a.x = i, a.y = j, b.x = k , b.y = l;
    }
    printf("Case %d: ", ++cas);
    if(!flag)puts("0");
    else printf("%d\n",(i-k) * (j-l));


  }



  return 0;
}
