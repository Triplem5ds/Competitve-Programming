/*
    Zura Ja - nai
    Katsura Da!
*/

#include "bits/stdc++.h"
using namespace std;

#define F first
#define S second
#define sz(x) x.size()
#define ios ios_base::sync_with_stdio(0);cin.tie(0);

typedef long long ll;
typedef pair<int, int> ii;
typedef long double db;

const int N = 2e5 + 5;
const int mod = 1e9 + 7;

int dp[2005][2005];
int a[2005], n;
int main(){

    dp[0][0] = 1;

    cin >> n;

    for(int i = 0; i < n - 1; i++)
        cin >> a[i];

    for(int i = 1; i < n; i++){
        if(a[i-1] == 0){
            ///NOW if the pos of i-1 in the permutation is J
            ///so if i put i at pos j in the permutation
            ///dp[i][j] = sum(dp[i-1][j+1->i]
            int sum = 0;
            for(int j = i; j >= 0; --j){
                sum += dp[i-1][j];
                if(sum >= mod)sum -= mod;
                dp[i][j] = sum;
            }
        }   else {
            int sum = 0;
            for(int j = 0; j <= i; j++){
                if(sum >= mod)sum -= mod;
                dp[i][j] = sum;
                sum += dp[i-1][j];
            }
        }
    }

    int sum = 0;

    for(int i = 0; i < n; i++){
        sum += dp[n-1][i];
        if(sum >= mod)sum -= mod;
    }

    cout << sum << '\n';

    return 0;
}
