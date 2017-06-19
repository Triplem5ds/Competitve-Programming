#include <bits/stdc++.h>
using namespace std;
const long long N = 1e5 + 5;

long long a[N], n, k, b;

long long pref[N];

void fix(long long &x){
  x = (x%(k-1) + (k-1))%(k-1);
}

int main(){
  scanf("%d%d%d", &k, &b, &n);

  for(long long i = 0; i < n; i++){
    scanf("%d", a + i);
    pref[i] = (a[i] + (i?pref[i-1]:0))%(k-1);
  }

  long long ans = 0;

  map<long long, long long>cnt;
  cnt[0]++;
  for(long long i = 0; i < n; i++){
    long long diff = pref[i] - b;
    fix(diff);

    ans += cnt[diff];
    cnt[pref[i]]++;
  }

  long long calc = 0;

  for(long long i = 0; i < n; i++){
    if(!a[i]){
      long long j  = i;
      for( ; j < n && !a[j]; j++);
      calc += (j-i+1) * (j-i)/2;
      i = j;
    }

  }

  if(b == k-1)ans -= calc;
  if(!b) ans = calc;

  cout << ans << '\n';



  return 0;
}
