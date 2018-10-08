/*
    dp[node][state];
    state 0 : the node before me is a server
    state 1 : the node before me isn't a server but it's covered by a server
    state 2 : the node before me is a server but it's not covered by a server
*/
#include <bits/stdc++.h>

using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int mod = 1e9 + 7;
const int N = 2005;

inline void fmin(int &x, int y){if(x > y)x=y;}
inline void fmax(int &x, int y){if(x < y)x=y;}
inline void add(int &x, int y){if((x+=y) >= mod)x-=mod;}

int n, cs, cf;
int dp[N][N];
int main(){
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE

    cin >> n >> cs >> cf;

    dp[0][0] = 1;

    for(int i = 1; i < n; i++){
        if(i == cs ||i== cf){
            for(int j = 0; j < i; j++)
                add(dp[i][j], dp[i-1][j]);
            for(int j = 0; j < i; j++)
                add(dp[i][j-1], dp[i-1][j] * 1ll * j % mod);
        }   else {
            for(int j = 0; j < i; j++){
                if(j >= 2)
                    add(dp[i][j-1], dp[i-1][j] * 1ll * j % mod * 1ll * (j-1) % mod);
                if(i >= cs)
                    add(dp[i][j-1],dp[i-1][j] * 1ll * j % mod);
                 if(i >= cf)
                    add(dp[i][j-1],dp[i-1][j] * 1ll * j % mod);
                add(dp[i][j+1], dp[i-1][j]);
            }
        }
    }

    cout << dp[n-1][0] << '\n';

    return 0;
}
