#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
char A[1024], W[N], S[N];
int F[N];
void fail(char *P){
  int i = 0, j = -1;
  F[0] = -1;

  int m = strlen(P);

  while(i < m){
    while(j >= 0 && P[i] != P[j]) j = F[j];
    i++, j++;
    F[i] = j;
  }
}
bool match(char *T, char *P){
  int cnt = 0;

  int i = 0, j = 0;

  int n = strlen(T), m = strlen(P);

  while(i < n){
    while(j >= 0 && T[i] != P[j])j = F[j];
    i++, j++;
    if(j == m)cnt++, j = F[j];
    if(cnt == 2)return 0;
  }

  return cnt == 1;
}
char nxt[1025];

int main(){
  int t;

  scanf("%d", &t);

  while(getchar() != '\n');

  while(t--){
    gets(A);
    gets(W);
    gets(S);

    for(int i = 0; i < strlen(A); i++)
      nxt[A[i]] = (A[(i+1)%strlen(A)]);

    int nA = strlen(A);
    int nW = strlen(W);
    int nS = strlen(S);

    vector<int>ans;

    for(int i = 0; i < nA; i++){
      fail(W);



      if(match(S, W))
        ans.push_back(i);

      for(int j = 0; j < nW; j++)
        W[j] = nxt[W[j]];

    }

    if(ans.size() == 0)
      puts("no solution");
    else if(ans.size() == 1){
      printf("unique: %d\n", ans[0]);
    }
    else{
      printf("ambiguous:");
      for(int i = 0; i < ans.size(); i++)
        printf(" %d", ans[i]);
      puts("");
    }


  }




  return 0;
}
