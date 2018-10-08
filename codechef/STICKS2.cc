/*
    to check the no rectangle case
    check that number of distinct integers >= k-1
    if i can put 3 of the same kind then it's also -1
    so if distinct integers == k-2 and there is some one of at least freq 3 answer is -1
    now for the main problem first give him all the distinct
    now the answer is either 2 different or 3 of the same
    i think i can get rid of all the cases if i basically use binary search and check the number of sticks i can put
    i think i can get rid of the 3 same case by decomposing the vector int x-2 and 2 for each element
    what is left is for me to check each prefix then binary search on the last element i can get
    and check rmq
    After Accept:
    i think i could have handled that better with a next array giving me the first position of the 2
*/
#include <bits/stdc++.h>

using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int mod = 1e9 + 7;
const int N = 1e5+5;

inline void fmin(int &x, int y){if(x > y)x=y;}
inline void fmax(int &x, int y){if(x < y)x=y;}
inline void add(int &x, int y){if((x+=y) >= mod)x-=mod;}

int n, k, t;
int a[N];
map<int,int>st;
int tb[N+N][18];
int sv[N+N];
int get(int l, int r){
    return max(tb[l][sv[r-l+1]], tb[r-(1<<sv[r-l+1])+1][sv[r-l+1]]);
}
int main(){
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE
    for(int i = 2; i < N+N; i++)
        sv[i] = sv[i>>1] + 1;
    cin >> t;
    while(t--){

        cin >> n >> k;
        st.clear();
        int mx = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            st[a[i]]++; fmax(mx,st[a[i]]);
        }
        if(st.size() >= k - 1 || st.size() == k - 2 && mx > 2){
            cout << -1 << '\n';
        } else {
            k -= st.size();
            vector<pair<int,int>>v;
            sort(a,a+n);
            for(int i = 0; i < n; i++)if(st.count(a[i]))st.erase(a[i]);
            else{
                if(v.empty()||a[i] != v.back().first)
                    v.push_back({a[i], 1});
                else
                    v.back().second++;
            }
            vector<pair<int,int>>vp;
            for(auto x : v)if(x.second < 3)vp.push_back(x);
            else {
                vp.push_back({x.first,2});
                vp.push_back({x.first,x.second-2});
            }
            ///build sparse table

            for(int i = 0; i < vp.size(); i++)if(vp[i].second <= 2)
                tb[i][0] = vp[i].second;    else tb[i][0] = 0;
            for(int i = 1; i < 18; i++)
                for(int j = 0; j + (1 << (i-1)) < vp.size(); j++)
                    tb[j][i] = max(tb[j][i-1],tb[j+(1 << (i-1))][i-1]);

            ll lo = 1, hi = 1000000000000000000ll;

            ///solution nlgnlgA
            ///there is a nlgA solution

            while(lo < hi){

                ll md = lo + (hi-lo)/2;

                int cnt = 0;
                int mx = 0;
                for(int i = 0; i < vp.size(); i++){
                    if(i && vp[i-1].first * 1ll * vp[i].first > md )break;
                    cnt += vp[i].second;
                    mx = max(mx,cnt);
                    if(i+1==vp.size())break;
                    int l = i+1,r=vp.size()-1;
                    while(l < r){
                        int md2 = l + (r-l+1)/2;
                        if(vp[md2].first * 1ll * vp[i].first <= md)
                            l=md2;
                        else
                            r=md2-1;
                    }
                    if(vp[l].first * 1ll * vp[i].first <= md){
                        mx = max(mx,cnt + get(i+1,l));
                    }
                }
                if(mx >= k)
                    hi=md;
                else
                    lo=md+1;

            }

            cout << lo << '\n';

        }

    }

    return 0;
}
