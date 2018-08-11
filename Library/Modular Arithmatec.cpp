#include "bits/stdc++.h"
using namespace std;

const int mod = 1e9 + 7;

inline int add(int x, int y){
  x += y;
  if(x >= mod)x -= mod;
  return x;
}
inline int sub(int x, int y){
  x -= y;
  if(x < 0) x += mod;
  return x;
}
inline int mult(int x, int y){
  return x * 1ll * y % mod;
}
int fast(int b, int e){
  if(!e)return 1;
  if(e&1)return b * 1ll * fast(b,e-1) % mod;
  return fast(b * 1ll * b % mod, e >> 1);
}

inline int inv(int x){
  return fast(x,mod-2);
}
