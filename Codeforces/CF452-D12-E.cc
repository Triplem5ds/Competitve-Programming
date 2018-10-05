/*
    IDEA :
    USING A SUFFIX AUTOMATON
    i want to count dp[0][state] * dp[1][state] * dp[2][state]
    where 0 : idx < size1 + 1
    or 1 : idx < size1 + size2 + 2
    or 2 : idx < size1 + size2 + size3 + 3
*/


#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int mod = 1e9 + 7;
const int N = 1e6 + 5;
const int M = 29;

int ans[N];
int dp[3][N];

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

	int get(char c){
        if(c == '@')return 0;
        if(c == '#')return 1;
        if(c == '$')return 2;
        return 3 + c - 'a';
	}

  vector<state>st;
	int sz, last, l;
	char offset = 'a';	// Careful!

	suffixAutomaton(){}
    int pos[3];
    int getLen(int x){
        if(~x)return st[x].len;
        return 0;
    }
	suffixAutomaton(string s){
		int l = s.length();
        st.resize(2 * l);
		for(int i = 0; i < 2*l; i++) st[i] = state();

		sz = 1, last = 0;
		st[0].len = 0;
		st[0].link = -1;

		for(int i = 0; i < l; i++){
			addChar(get(s[i]));
        }

		for(int i = last; i != -1; i = st[i].link) st[i].terminal = true;
		vector<vector<int>>adj(2 * l);
        memset(dp,-1,sizeof dp);

        for(int i = 0; i < sz; i++){
            ans[getLen(st[i].link) + 1] += solve(0,i) * 1ll * solve(1,i) * 1ll * solve(2,i) % mod;
            ans[getLen(i) + 1] -= solve(0,i) * 1ll * solve(1,i) * 1ll * solve(2,i) % mod;
            if(ans[getLen(st[i].link)+ 1] >= mod)
                ans[getLen(st[i].link) + 1] -= mod;
            if(ans[getLen(i) + 1] < 0)
                ans[getLen(i) + 1] += mod;
        }
	}
    int solve(int f, int idx){
        if(idx == pos[f])
            return 1;
        if(idx == pos[0] || idx == pos[1] || idx == pos[2])return 0;
        int &ret = dp[f][idx];
        if(~ret)
            return ret;
        ret = 0;
        for(int i = 0; i < M; i++)
            if(~st[idx].next[i]){
                ret += solve(f,st[idx].next[i]);
                if(ret >= mod)ret -= mod;
            }
        return ret;
    }
	void addChar(int c){
		int cur = sz++; assert(cur < N*2);
		if(c < 3)pos[c] = cur;
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
		vector<ii> v;
		for(int i = 1; i < sz; i++) v.push_back(make_pair(st[i].len, i));

		sort(v.begin(), v.end(), greater<ii>());

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
};



int main(){
#ifdef ONLINE_JUDGE
ios_base::sync_with_stdio(0);
cin.tie(0);
#endif // ONLINE_JUDGE

    string a,b,c;
    cin >> a >> b >> c;
    suffixAutomaton SA(a + "@" + b + "#" + c + "$");
    int mn = min(a.size(), min(b.size(), c.size()));
    int cur = 0;
    for(int i = 1; i <= mn; i++){
        cur += ans[i];
        if(cur >= mod)cur -= mod;   if(cur < 0)cur += mod;
        cout << cur << ' ';
    }

    return 0;
}
