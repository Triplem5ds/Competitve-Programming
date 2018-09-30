#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 2e5+5;
const int mod = 1e9 + 7;

/*
    IDEA :
    given n ranges
    and m ranges
    for each range in the m ranges
    get the range that has maximal intersection with this range
    and * c[i] and maximize
    i am going to handle the second type of ranges as queries
    for the first type of ranges if x < l i can get it with a prefix max
    and binary search if y > r i can get it with a prefix min and binary search
    if the whole range is inside i can get it with merge sort tree and prefix max inside each node
*/



struct node{
    vector<ii> mx;
    vector<pair<ii,int>> arr;
}tree[N << 2];

void build(int node, int s, int e, vector<pair<ii,int>> & org){

    if(s == e){
        tree[node].arr.push_back({{org[s].first.second, org[s].first.first},org[s].second});
        tree[node].mx.push_back({org[s].first.second - org[s].first.first, org[s].second});
    }   else {
        int md = (s+e)>>1;
        build(node<<1,s,md,org);
        build(node<<1|1,md+1,e,org);
        merge(tree[node<<1].arr.begin(),tree[node<<1].arr.end(), tree[node<<1|1].arr.begin(), tree[node<<1|1].arr.end(), back_inserter(tree[node].arr));
        for(int i = 0; i < tree[node].arr.size(); i++){
            tree[node].mx.push_back({tree[node].arr[i].first.first - tree[node].arr[i].first.second, tree[node].arr[i].second});
            if(i)
                tree[node].mx[i] = max(tree[node].mx[i], tree[node].mx[i-1]);
        }
    }
}
pair<int,int> qry(int node, int s, int e, int l, int r, int target){
    if(r < s || e < l || l > r)return {0,-1};
    if(l <= s && e <= r){
        if(tree[node].arr[0].first.first > target)return {0,-1};
        int lo = 0, hi = tree[node].arr.size()-1;
        while(lo < hi){
            int md = lo + (hi-lo+1)/2;
            if(tree[node].arr[md].first.first <= target)
                lo=md;
            else
                hi=md-1;
        }

        return tree[node].mx[lo];
    }
    int md = (s+e)>>1;
    return max(qry(node<<1,s,md,l,r,target),
               qry(node<<1|1,md+1,e,l,r,target));
}
int n, m;
vector<pair<ii,int>> rangesA, rangesB;
ii pMax[N], pMin[N];
ii getNextA(int x){
    int lo = 0, hi = rangesA.size() - 1;
    while(lo < hi){
        int md = lo + (hi-lo + 1) / 2;
        if(rangesA[md].first.first <= x)
            lo=md;
        else
            hi=md-1;
    }
    if(rangesA[lo].first.first <= x)
        return pMax[lo];
    return {-1,-1};
}
ii getNextB(int x){
    int lo = 0, hi = rangesB.size()-1;
    while(lo < hi){
        int md = lo + (hi-lo + 1) / 2;
        if(rangesB[md].first.second >= x)
            lo=md;
        else
            hi=md-1;
    }
    if(rangesB[lo].first.second >= x)
        return pMin[lo];
    return {1e9 + 1,-1};
}
int main(){
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE

    cin >> n >> m;

    vector<pair<ii,int>> videos(n);
    int idx = 0;
    for(auto & x : videos)
        cin >> x.first.first >> x.first.second, x.second = idx++;

    rangesA = videos;
    rangesB = videos;

    sort(rangesA.begin(), rangesA.end());
    sort(rangesB.begin(), rangesB.end(), [](pair<ii, int> x, pair<ii,int> y)->bool {
            return x.first.second > y.first.second;
         });

    for(int i = 0; i < rangesA.size(); i++){
        pMax[i] = {rangesA[i].first.second,rangesA[i].second};
        if(i)pMax[i] = max(pMax[i-1], pMax[i]);
    }

    for(int i = 0; i < rangesB.size(); i++){
        pMin[i] = {rangesB[i].first.first, rangesB[i].second};
        if(i)pMin[i] = min(pMin[i-1], pMin[i]);
    }


    ll out = 0;

    build(1,0,n-1,rangesA);
    int idx1 = 0, idx2 = 0;
    for(int i = 0; i < m; i++){

        int l, r, c;
        cin >> l >> r >> c;

        int inter = 0;
        auto tmp1 = getNextA(l);
        auto tmp2 = getNextB(r);
        auto tmp3 = qry(1,0,n-1,lower_bound(rangesA.begin(),rangesA.end(),make_pair(ii(l,-1),-1)) - rangesA.begin(),
                               upper_bound(rangesA.begin(),rangesA.end(), make_pair(ii(r,INT_MAX),INT_MAX)) - rangesA.begin() - 1, r);
        if(c * 1ll * min(r-l,tmp1.first-l) > out){
            out = c * 1ll * min(r-l,tmp1.first-l);
            idx1 = tmp1.second;
            idx2 = i;
        }
        if(c * 1ll * min(r-l,r-tmp2.first) > out){
            out = c * 1ll * min(r-l,r-tmp2.first);
            idx1 = tmp2.second;
            idx2 = i;
        }
        if(c * 1ll * min(r-l,tmp3.first) > out){
            out = c * 1ll * min(r-l,tmp3.first);
            idx1 = tmp3.second;
            idx2 = i;
        }

    }

    cout << out << "\n";

    if(out)
        cout << idx1+1 << ' ' << idx2 + 1 << '\n';


    return 0;
}
