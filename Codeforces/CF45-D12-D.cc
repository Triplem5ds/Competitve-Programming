#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;
const int N = 2e5+5;

vector<pair<pair<int,int>,int>>vp;
int ans[222];
bitset<10000005>bt;
int main(){
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE

    int n;  cin >> n;
    vp.resize(n);
    int i=0;
    for(auto & x    :   vp) cin >> x.first.second>> x.first.first,x.second=i++;
    sort(vp.begin(),vp.end());
    for(int i = 0; i < n; i++)
        for(int j = vp[i].first.second;;j++)
        if(!bt[j]){
            bt[j] = 1;
            ans[vp[i].second] = j;
            break;
        }

    for(int i= 0; i < n; i++)
        cout << ans[i] << ' ';

    return 0;
}
