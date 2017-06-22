#include <iostream>
using namespace std;

long long sv[10006];

int cnt = 1;

void init(){
  for(int i = 1; cnt <= 10000; i++){

    for(int j = 1; j <= i && cnt <= 10000; j++)
      sv[cnt] = sv[cnt-1] + i, cnt++;

  }


}

int main(){

  init();

  int x;

  while(cin >> x && x){
    cout << x << ' ' << sv[x] << '\n';


  }



  return 0;
}
