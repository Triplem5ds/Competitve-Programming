#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;
const int N = 1e5+5;
int a[N], n, k;
int main(){

    cin >> n >> k;
    ll sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] < 0)sum += a[i];
        a[i] = abs(a[i]);
    }

    sort(a,a+n);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>>pq;
    pq.push({sum,-1});
    while(k--){
        auto cur = pq.top();    pq.pop();
        printf("%lld\n", cur.first);

        if(cur.second < n-1){
            cur.second++;
            pq.push({cur.first + a[cur.second], cur.second});
            if(cur.second)
                pq.push({cur.first - a[cur.second-1] + a[cur.second], cur.second});
        }


    }


    return 0;
}
