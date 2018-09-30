#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 1e5+5;
const int mod = 1e9 + 7;

/*
    if dp[l->r] = 1
    and dp[x->r] = 1
    then dp[l->x-1] = 1

*/

int n;
string str;
int b4[N][26];
void solve(int l, int r){
    if(l > r)return;
    if(str[l] == str[r]){
        cout << "(";
        solve(l+1,r-1);
        cout << ")";
        return;
    }
    int to = b4[r][str[l] - 'a'];
    cout << "(";
    solve(l+1,to-1);
    cout << ")";
    solve(to + 1, r);
}
int main(){
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE

    cin >> str; n = str.size();

    stack<int>stk;

    for(int i = 0; i < n; i++){
        if(stk.empty() || str[stk.top()] != str[i])
            stk.push(i);
        else
            stk.pop();
    }
    if(!stk.empty()){
        cout << -1 << '\n';
        return 0;
    }
    memset(b4, -1, sizeof b4);
    for(int i = 2; i < n; i++){

        for(char j = 'a'; j <= 'z'; j++){

            if(str[i] == str[i-1]){
                if(str[i-2] == j)
                    b4[i][j-'a'] = i - 2;
                else
                    b4[i][j-'a'] = b4[i-2][j-'a'];
            }   else {
                int to = b4[i-1][str[i]-'a'] - 1;
                if(to < 0)continue;
                if(str[to] == j)
                    b4[i][j-'a'] = to;
                else
                    b4[i][j-'a'] = b4[to][j-'a'];

            }

        }

    }
    solve(0,n-1);

    return 0;
}
