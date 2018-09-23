#include <bits/stdc++.h>

using namespace std;

using ll = long long;

// n < 4,759,123,141 				3 :  2, 7, 61
// n < 1,122,004,669,633 			4 :  2, 13, 23, 1662803
// n < 3,474,749,660,383			6 :  pirmes <= 13
// n < 3,825,123,056,546,413,051	9 :  primes <= 23

int testPrimes[] = {2,3,5,7,11,13,17,19,23};

struct MillerRabin{
  ///change K according to n
  const int K = 9;
  ll mult(ll s, ll m, ll mod){
    if(!m) return 0;
    ll ret = mult(s, m/2, mod);
    ret = (ret + ret) % mod;
    if(m & 1) ret = (ret + s) % mod;
    return ret;
  }

  ll power(ll x, ll p, ll mod){
    ll s = 1, m = x;
    while(p){
      if(p&1) s = mult(s, m, mod);
      p >>= 1;
      m = mult(m, m, mod);
    }
    return s;
  }

  bool witness(ll a,ll n,ll u,int t){
    ll x = power(a, u, n), nx;
    for(int i = 0; i < t; i++){
      nx = mult(x, x, n);
      if(nx == 1 and x != 1 and x != n-1) return 1;
      x = nx;
    }
    return x != 1;
  }

  bool isPrime(ll n){	// return 1 if prime, 0 otherwise
    if(n < 2) return 0;
    if(!(n&1)) return n == 2;
    for(int i = 0; i < K; i++)if(n == testPrimes[i])return 1;
    ll u = n-1; int t = 0;

    while(u&1) u >>= 1, t++;	// n-1 = u*2^t

    for(int i = 0; i < K; i++) if(witness(testPrimes[i], n, u, t)) return 0;
    return 1;
  }
}tester;

int main() {
  
  
  
  return 0;
}
