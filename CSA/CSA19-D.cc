
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int,int>;
using ll = long long;

const int N = 1e5+5;
const int mod = 1e9 + 7;

/*
    IDEA 
    test putting the first 10 smallest numbers and 
    the 10 largest numbers frequency wise once one
    of them gets a correct then it's his position in the sequence
*/

int n, a[N], cnt[N];
set<int>st;
set<pair<int,int>>freq;
bool test(int lft, int b4, int x){
    if(x == b4)return false;
    bool f = true;
    freq.erase({cnt[x],x});
    --cnt[x];
    if(cnt[x])freq.insert({cnt[x],x});
    pair<int,int>mx1 = {0,0};
    if(freq.size())mx1 = *freq.rbegin();
    pair<int,int>mx2 = {0,0};
    if(freq.size() > 1)mx2 = *(----freq.end());
    if(mx1.second == x){
        if(lft/2 < mx1.first || (lft+1)/2 < mx2.first)
            f = false;
    }   else {
        if(lft/2 < mx2.first || (lft+1)/2 < mx1.first)
            f = false;
    }
    assert(mx2.first == cnt[mx2.second]);
    if(cnt[x])freq.erase({cnt[x],x});
    ++cnt[x];
    freq.insert({cnt[x],x});
    return f;
}
int b4;
void add(int x){
    freq.erase({cnt[x],x});
    cnt[x]--;
    if(cnt[x])freq.insert({cnt[x],x});
    else st.erase(x);
    b4 = x;
}
int main(){
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE

    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> a[i];
        cnt[a[i]]++;
    }

    if(*max_element(cnt,cnt + N) > (n + 1) / 2){
        cout << -1 << '\n';
        return 0;
    }

    for(int i = 1; i <= 100000; i++)if(cnt[i]){
        freq.insert(make_pair(cnt[i], i));
        st.insert(i);
    }

    for(int i = 0; i < n; i++){
        vector<int>cur;
        int cnt = 0;
//        cout << i << '\n';
        for(auto it : st){
            if(cnt == 10)break;
            cnt++;
            cur.push_back(it);
        }
        cnt = 0;
        for(auto it = --freq.end(); ; --it){
            cur.push_back(it->second);
            cnt++;
            if(cnt == 10 || it == freq.begin())break;
        }   
        sort(cur.begin(),cur.end());
        for(auto x : cur)if(test(n-i-1,b4,x)){
            add(x);
            cout << x << " ";
            break;
        }
    }

    return 0;
}
