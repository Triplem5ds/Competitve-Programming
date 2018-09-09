#include "bits/stdc++.h"
using namespace std;



const int siz = 300000000;
int Ktos[210], stoK[48];
long long isComposite[(siz + 209) / 210];
int nums[] = {2, 3, 5, 7};

void init() {
  memset(Ktos, -1, sizeof Ktos);
  int j = 0;
  for (int i = 0; i < 210; i ++) {
    for (auto p : nums) {
      if (i % p == 0)
        goto nxt;
    }
    Ktos[i] = j;
    stoK[j ++] = i;
    nxt:;
  }
}

void sieveGamdZ7alee2() {
  isComposite[0] = 1;
  // ba2fesh el start bta3 kol block with size 210
  for (int i = 0; !i || i <= siz / i; i += 210) {
    for (int j = 0; j < 48; j ++) {
      if (!((isComposite[i / 210] >> j) & 1)) {
        int k = i + stoK[j];
        for (int l = k * k; l < siz; l += k) {
          int x = Ktos[l % 210];
          if (x == -1)
            continue;
          isComposite[l / 210] |= (1LL << x);
        }
      }
    }
  }
}

inline bool isPrime(int n) {
  int x = Ktos[n % 210];
  if (x == -1)
    return count(nums, nums + 4, n);
  return !(((isComposite[n / 210]) >> x) & 1);
}

int main() {

  init();
  sieveGamdZ7alee2();

  return 0;
}
