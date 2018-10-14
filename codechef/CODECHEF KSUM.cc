#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;
const int N = 1e5+5;


int main(){
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE

    int n, k;   cin >> n >> k;
    priority_queue<pair<ll, int>>pq;

    vector<int>a(n);    for(auto & x : a)   cin >> x;

    ll sum = 0;
    for(int i = 0; i < n; i++)sum += a[i];
    for(int i = 0; i < n; i++){
        pq.push({sum,n-1}); sum -= a[i];
    }
    while(k--){
        auto cur = pq.top();  pq.pop();
        cout << cur.first << ' ';
        if(cur.second)pq.push({cur.first - a[cur.second], cur.second - 1});
    }

    return 0;
}
