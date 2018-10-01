#include "bits/stdc++.h"
using namespace std;

typedef pair<int,int> ii;
typedef long long ll;

const int N = 1e5 + 5;

/*
    IDEA :
    the answer is sum function for number of sails
    on this height meaning if there are x sails at height h
    ans += x * (x - 1) / 2;
    so the order of placement of sails is irrelevant
    so we sort them according to height
    now i know that it's optimal to place a sail first at the index with smallest value
    if there is a tie place it at the biggest one
    i can do that with line sweep and bit
    so i grab the biggest k range which is h-k+1 -> h
    color it if h==k or if the current element i am standing on is 0
    so i either binary search on the position of the last element >= query(l)
    now all of these are optimal to put in and i am sure they are less than k
    then decrease the k and do the same for k + 1 i am sure that they will end up with sum == k
*/

int bit[N];

void upd(int idx, int val){
    for(; idx < N ; idx += idx & -idx)
        bit[idx] += val;
}
int qry(int idx){
    int ret = 0;
    for(;idx; idx -= idx & -idx)
        ret += bit[idx];
    return ret;
}
ii a[N];
int getIdx(int x){
    int lo = 0, hi = N;

    while(lo < hi){

        int md = lo + (hi - lo + 1) / 2;
        if(qry(md) >= x)
            lo=md;
        else
            hi=md-1;

    }

    return lo;
}
int main(){

    int n;

    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d%d", &a[i].first, &a[i].second);

    sort(a,a+n);

    for(int i = 0; i < n; i++){

        int h, k;
        tie(h,k) = a[i];
        int l = h-k+1;
        if(l == 1 || qry(l) != qry(l-1)){
            upd(l,1);
            upd(h+1,-1);
        }   else {
            int idx = getIdx(qry(l));
            if(qry(l)){
                upd(idx+1,1);
                upd(h+1,-1);
                k -= (h - idx);
            }
            idx = getIdx(qry(l) + 1);
            upd(idx+1,1);
            upd(idx+k+1,-1);
        }
    }

    ll ans = 0;

    for(int i = 1; i < N; i++){
        ll tmp = qry(i);
        ans += tmp * (tmp-1) / 2;
    }

    cout << ans << "\n";

    return 0;
}
