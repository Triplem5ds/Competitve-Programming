#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("powers.in","r",stdin);
    int t;cin >> t;
    int ret=0;
    while (t--){
        int cnt;
        cin >> cnt;
        int ans=0;
        int B,N;

        for(int i=0;i<cnt;i++){
            cin >> B >> N;
            int cur;
            if(B%2==1){
              cur=N%2;
            }
            else{
                N%=B+1;
                if( N == B)
                  cur = 2;
                else
                  cur = N%2;
            }
            ans^=cur;
        }
        puts(ans?"1":"2");



    }
return 0;}
