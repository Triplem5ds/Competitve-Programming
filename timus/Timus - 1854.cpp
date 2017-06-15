#include <bits/stdc++.h>
using namespace std;
long long get_ans(long long x){

  long long ret = 1;

  for(long long i = 1; i * i * i <= x; i++){
    if(x%i == 0){
      long long tmp = (x/(i));

      long long cur = sqrt(tmp);

      if(cur * cur == tmp)
        ret = max(ret, cur);
      if(x/i%i == 0)
        ret = max(ret,i);
    }

  }

  return ret * ret;

}
int main(){


  long long n;

  cin >> n;

  cout << get_ans(n) << '\n';





  return 0;
}
