  #include <bits/stdc++.h>
  using namespace std;

  int main(){

    int C, D, A, B;

    int t;

    cin >> t;

    while(t--){


      cin >> C >> D;

      if((C & D) != C){
        puts("-1");
        continue;
      }

      A = B = C;

      D ^= C;

      for(int i = 30; i >= 0; i--){
        if(D & (1 << i)){
          D ^= (1 << i);
          B |= (1 << i);
          break;
        }
      }

      cout << (A | D) << ' ' << B << '\n';


    }







    return 0;
  }
