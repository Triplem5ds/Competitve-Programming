#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int N = 1000005;
const int M = 26;
struct suffixAutomaton{
	struct state{
		int len;		// length of longest string in this class
		int link;		// pointer to suffix link
		int next[M]; 	// adjacency list
		ll cnt;			// number of times the strings in this state occur in the original string

		bool terminal;	// by default, empty string is a suffix
						// a state is terminal if it corresponds to a suffix

		state(){
			len = 0, link = -1, cnt = 0;
			terminal = false;
			for(int i = 0; i < M; i++) next[i] = -1;
		}
	};

  vector<state>st;
	int sz, last, l;
	char offset = 'a';	// Careful!

	suffixAutomaton(string &s){

		int l = s.length();
    st.resize(2 * l);
		for(int i = 0; i < 2*l; i++) st[i] = state();

		sz = 1, last = 0;
		st[0].len = 0;
		st[0].link = -1;

		for(int i = 0; i < l; i++)
			addChar(s[i] - offset);

		for(int i = last; i != -1; i = st[i].link) st[i].terminal = true;
	}

	void addChar(int c){
		int cur = sz++; assert(cur < N*2);
		st[cur].len = st[last].len + 1;
		st[cur].cnt = 1;

		int p = last;
		while(p != -1 and st[p].next[c] == -1){
			st[p].next[c] = cur;
			p = st[p].link;
		}

		last = cur;

		if(p == -1){
			st[cur].link = 0; return;
		}

		int q = st[p].next[c];

		if(st[q].len == st[p].len + 1){
			st[cur].link = q; return;
		}

		int clone = sz++;

		for(int i = 0; i < M; i++) st[clone].next[i] = st[q].next[i];
		st[clone].link = st[q].link;
		st[clone].len = st[p].len + 1;
		st[clone].cnt = 0;				// cloned states initially have cnt = 0

		while(p != -1 and st[p].next[c] == q){
			st[p].next[c] = clone;
			p = st[p].link;
		}

		st[q].link = st[cur].link = clone;

		return;
	}

	bool contains(string &t){
		int cur = 0;
		for(int i = 0; i < t.length(); i++){
			cur = st[cur].next[t[i] - offset];
			if(cur == -1) return false;
		}
		return true;
	}

	// alternatively, compute the number of paths in a DAG
	// since each substring corresponds to one unique path in SA
	ll numberOfSubstrings(){
		ll res = 0;
		for(int i = 1; i < sz; i++) res += st[i].len - st[st[i].link].len;
		return res;
	}

	void numberOfOccPreprocess(){
		vector<pii> v;
		for(int i = 1; i < sz; i++) v.push_back(make_pair(st[i].len, i));

		sort(v.begin(), v.end(), greater<pii>());

		for(int i = 0; i < sz-1; i++){
			int suf = st[v[i].second].link;
			st[suf].cnt += st[v[i].second].cnt;
		}
	}

	ll numberOfOcc(string &t){
		int cur = 0;
		for(int i = 0; i < t.length(); i++){
			cur = st[cur].next[t[i] - offset];
			if(cur == -1) return 0;
		}

		return st[cur].cnt;
	}
	 void dfs(int u, ll & k, string & ans){
    for(int i = 0; i < 26; i++){

      if(st[u].next[i] != -1){
        k -= st[st[u].next[i]].cnt;
        if(k <= 0){
          ans.push_back(char(i+'a'));
          return;
        }
        dfs(st[u].next[i], k,ans);
        if(k <= 0){
          ans.push_back(char(i+'a'));
          return;
        }

      }

    }

  }
  int solve(string s){
    int n =s.size();
    s += s;
    map<int,int>used;
    int curLen = 0;
    int curState = 0;
    int ret = 0;

    for(int i = 0; i < 2 * n; i++){
      while(curState != -1 && st[curState].next[s[i]-offset] == -1)curState = st[curState].link, curLen = st[curState].len;
      if(curState == -1)curState = 0, curLen = 0;
      else curState = st[curState].next[s[i]-offset], curLen++;
      if(curLen == n){
        if(!used[curState])ret += st[curState].cnt;
        used[curState] = 1;
        curLen--;
        if(curLen == st[st[curState].link].len)
          curState = st[curState].link;
      }

    }
    return ret;
  }
};
string s;
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> s;
  suffixAutomaton SA(s);

  SA.numberOfOccPreprocess();

  int q;  cin >> q;
  while(q--){
    string t; cin >> t;
    cout << SA.solve(t) << '\n';
  }

  return 0;
}
