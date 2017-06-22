#include <iostream>
#include <vector>
#include <stdio.h>
#include <map>
#include <string.h>
/*
  the basic idea is that you need to calculate the xor form the root to all numbers and save it in a trie
  
  then just search in that trie for the maximum number it can get.
  
  the proof for this is that the paths from node u to node v when xored together the matching part will be negated due to it having equal xor.
*/
using namespace std;
const int N = 1e5 + 5;
const int lg = (1<<30);

int n, u, v, w;
int nxt[2*N], W[2*N], last[2*N], to[2*N], trie[31*N][2];
int ans = 0, sum[N], cnt;
int cnt2 = 0;
void add_edge(int u, int v, int w){
  to[cnt] = v, W[cnt] = w, nxt[cnt] = last[u]; last[u] = cnt++;
  to[cnt] = u, W[cnt] = w, nxt[cnt] = last[v]; last[v] = cnt++;

}


void insert(int s){
  int pos = 0;
  for(int i = 30; i >= 0; i--){
    int cur = bool(s & (1<<i));
    if(trie[pos][cur] == -1)trie[pos][cur] = cnt2++;
    pos = trie[pos][cur];
  }
}
int qry(int s){
  int pos = 0;
  int ret = 0;
  for(int i = 30; i >= 0; i--){
    int cur = bool(s & (1<<i));
    if(trie[pos][!cur] != -1){
      ret += (1<<i);
      pos = trie[pos][!cur];
    }
    else{
        pos = trie[pos][cur];
    }
  }
  return ret;
}


void dfs_insert(int u, int par, int s){
  insert(s);
  sum[u] = s;
  for(int v = last[u]; v != -1; v = nxt[v])
    if(to[v] != par)
      dfs_insert(to[v], u, s ^ W[v]);

}

int main(){

  while(scanf("%d", &n) == 1){

  memset(last, -1, sizeof last);

  cnt = 0;

  for(int i = 0; i < n - 1; i++){
    scanf("%d%d%d", &u, &v, &w);
    add_edge(u, v, w);
  }

  ans = 0;

  memset(trie, -1, sizeof trie);

  cnt2 = 1;

  dfs_insert(0, -1, 0);

  for(int i = 0; i < n; i++)
    ans = max(ans, qry(sum[i]));

  printf("%d\n", ans);

  }

}
