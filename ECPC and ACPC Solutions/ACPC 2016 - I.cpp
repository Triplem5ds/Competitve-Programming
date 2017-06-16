#include <bits/stdc++.h>
using namespace std;
int main(){
int t;
cin >> t;
while (t--){
    int n,q;
    cin >> n >> q;
    vector<pair<int,int> >V(n);
    for(int i=0;i<n;i++)cin >> V[i].first >> V[i].second;
    int lo1=V[0].first;
    int hi1=V[0].first;
    int lo2=V[0].second;
    int hi2=V[0].second;
    for(int i=1;i<n;i++){
        if(V[i].first>=hi1&&V[i].second>=hi1){
            hi1=max(hi1,min(V[i].first,V[i].second));
        }
        else if(V[i].first<=lo1&&V[i].second<=lo1){
            lo1=min(lo1,max(V[i].first,V[i].second));
        }
        if(V[i].first>=hi2&&V[i].second>=hi2){
            hi2=max(hi2,min(V[i].first,V[i].second));
        }
        else if(V[i].first<=lo2&&V[i].second<=lo2){
            lo2=min(lo2,max(V[i].first,V[i].second));
        }

    }
    int x;
    if(lo1>lo2){
        swap(lo1,lo2);
        swap(hi1,hi2);
    }
    int l=lo2;
    int r=min(hi1,hi2);
    while(q--){
        scanf("%d",&x);
        if(hi1>=lo2&&x>=l&&x<=r){
            puts("YES");
        }
        else{
            puts("NOT SURE");
        }
    }
}


}
