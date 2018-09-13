const int N = 1005;
const int M = 26;
int trie[N][M];
int go[N][M];
int mrk[N], f[N];
int ptr = 1;
void BFS(){

  queue<int> q;
	for(int i = 0; i < M; i++)
		if(trie[0][i])
			q.push(trie[0][i]), f[trie[0][i]] = 0;
	for(int i = 0; i < M; i++) go[0][i] = trie[0][i];
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(int i = 0; i < M; i++) {
			if(trie[x][i]) {
				int y = trie[x][i];
				f[y] = f[x];
				while(f[y] && !trie[f[y]][i])
					f[y] = f[f[y]];
				if(trie[f[y]][i]) f[y] = trie[f[y]][i];
				mrk[y] += mrk[f[y]];
				q.push(y);
			}
			if(trie[x][i]) go[x][i] = trie[x][i];
			else go[x][i] = go[f[x]][i];
		}
	}

}
void ins(string x){
  int v;  cin >> v;
  int cur = 0;
  for(int i = 0; i < x.size(); i++){
      if(!trie[cur][x[i]-'a'])
        trie[cur][x[i]-'a'] = ptr++;
      cur = trie[cur][x[i]-'a'];
  }
  mrk[cur] += v;
}
