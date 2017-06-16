#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define MP make_pair
#define TripleM ios_base::sync_with_stdio(0);cin.tie(0);
#define clr(x,y) memset(x,y,sizeof(x,y))
#define F first
#define S second
#define pb push_back
#define sz size()
typedef long long ll;
ll N,M,K;
int main(){
    int T;scanf("%d",&T);
    while(T--){
        int N;cin>>N;

        bool flag=0;
        for(int i=0;i<N;i++){
            int x;cin>>x;
        if(!(((x%(N*(N-1))>=1))&&((x%(N*(N-1)))<N))){
                flag=1;
        }
    }if(flag)
        cout<<"Alice\n";
    else
        cout<<"Bob\n";


    }
return 0;}
