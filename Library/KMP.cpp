#include "bits/stdc++.h"

using namespace std;

const int N = 1e5 + 5;

int HASHING_PRIMES[] = {1610612741 , 1073676287 , 805306457 , 402653189};
int HASHING_BASES[] = {53, 10007};


//can be optimized using dp

vector<int> FAIL(string pat){

    int m = pat.size();
    vector<int>F(m + 1);
    int i = 0, j = -1;
    F[0] = -1;

    while(i < m){
        while(j >= 0 && pat[i] != pat[j]) j = F[j];
        i++, j++;
        F[i] = j;
    }

    return F;
}

vector<int> KMP_Search(string txt, string pat){


    vector<int>F = FAIL(pat);
    int i = 0, j = 0;
    int n = txt.size(), m = pat.size();
    vector<int>ret(n+1);
    while(i < n){
        while(j >= 0 && txt[i] != pat[j])j = F[j];
        i++, j++;
        ret[i-j] = j;
        if(j == m)
            j = F[j];
    }

    return ret;
}

vector<int> Zalgo(string s){
    vector<int>z(n);
    int L = 0, R = 0;
    for (int i = 1; i < n; i++) {
      if (i > R) {
        L = R = i;
        while (R < n && s[R-L] == s[R]) R++;
        z[i] = R-L; R--;
      } else {
        int k = i-L;
        if (z[k] < R-i+1) z[i] = z[k];
        else {
          L = i;
          while (R < n && s[R-L] == s[R]) R++;
          z[i] = R-L; R--;
        }
      }
    }
    z[0] = n;
    return z;
}

int main(){}
