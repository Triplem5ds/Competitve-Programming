#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include "friend.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5 +5;
int ans[N];
int findSample(int n, int confidence[], int host[], int protocol[]){
    for(int i = 0; i < n; i++)
        ans[i] = confidence[i];

    int ret = 0;

    for(int i = n - 1; i ; --i){

        if(protocol[i] == 0){
            ret += ans[i];
            ans[host[i]] -= ans[i];
            if(ans[host[i]] < 0)
                ans[host[i]] = 0;
            }   else if(protocol[i] == 1){
                ans[host[i]] += ans[i];
            }   else {
                if(ans[i] > ans[host[i]])
                    ans[host[i]] = ans[i];
            }
    }

    ret += ans[0];
    return ret;
}
