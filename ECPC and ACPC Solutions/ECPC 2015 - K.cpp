#include<bits/stdc++.h>
using namespace std;

unsigned long long DP[2][205];

int main(){
    
    int t;cin>>t;
    
    while(t--){
    
        long long a, b;
    
        cin >> a >> b;
    
        int n;cin>>n;
    
        vector<int>s;
    
        for(int i=0;i<=n;i++){
    
            unsigned long long k = a/b;
    
            a-=b*k;
    
            a *= 10;
    
            s.push_back(k);
        }
    
        s.erase(s.begin());
        int p;cin>>p;
    
        memset(DP,0,sizeof(DP));
    
        unsigned long long sum=0;
    
        for(int i=1;i<=n;i++){
            int x=s[i-1];
    
          for(int j=0;j<p;j++)DP[i%2][j]=0;
    
            for(int j=0;j<p;j++)
                DP[(i)%2][(j*10+x)%p]+=DP[(i-1)%2][j];
           
            DP[(i%2)][x%p]++;
            sum+=DP[i%2][0];
        }
        
        cout<<sum<<endl;
    }
return 0;}
