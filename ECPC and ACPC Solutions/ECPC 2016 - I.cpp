#include <bits/stdc++.h>
using namespace std;

typedef pair<double, int> pt;
typedef long long ll;

const int N = 1e5 + 5;
const double eps = 1e-8;

int t, n, m;

vector<pt> v;

ll x[N], y[N], r[N];

int main(){
    
    freopen("walk.in", "r", stdin);

    for(scanf("%d", &t); t--; ){

        scanf("%d%d", &n, &m);

        v.clear();

        for(int i = 1; i <= n; i++){

            scanf("%lld%lld%lld", x + i, y + i, r + i);

            if(abs(y[i]) <= m - r[i]){

                double delta = sqrt((m - r[i]) * (m - r[i]) - y[i] * y[i]);

                v.push_back(pt(x[i] - delta - eps, r[i]));
                v.push_back(pt(x[i] + delta + eps, -r[i]));

            }

        }

        sort(v.begin(), v.end());


        ll cur = 0, ans = 0;

        for(int i = 0; i < v.size(); i++)
            cur += v[i].second, ans = max(ans, cur);

        printf("%lld\n", ans);
    }




    return 0;
}
