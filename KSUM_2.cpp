#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

int n, k, a[MAXN];

void Solve() {
	cin >> n >> k;

    long long sum = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    
    priority_queue <pair <long long, int> > pr;
    
    for (int i = 0; i < n; i++) { 
        pr.push(make_pair(sum, n - 1));
        sum -= a[i];
    }
    
    while (k--) {
        pair <long long, int> cur = pr.top();
        
        pr.pop();
        cout << cur.first << " ";
        
        if (cur.second) {
            pr.push(make_pair(cur.first - a[cur.second], cur.second - 1));
        }
    }
}
 
int main(void) {
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    Solve();
    
    return 0;
}
