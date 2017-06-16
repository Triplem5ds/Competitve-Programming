#include<bits/stdc++.h>
using namespace std;
double A[(int)1e6+5];
int main(){
    
    int T;cin>>T;
    
    while(T--){
        
        string s;cin>>s;
        
        int fact1=1;
        
        double fact2=1;
        double j=2;
        
        for(int i=2;i<=s.size();i++,j++)
            fact1*=i,fact2*=j;
        
        string x=s;
        
        sort(s.begin(),s.end());
        reverse(s.begin(),s.end());
        
        A[0]=0;
        A[1]=1;
        A[1]/=fact2;
        
        int cnt=0;
        
        do{
            if(s==x)break;
            cnt++;
            if(cnt>=2)
                A[cnt]=A[cnt-1]+(A[cnt-1]/fact2);

        }while(prev_permutation(s.begin(),s.end()));
        
        cout<<fixed<<setprecision(9);
        
        cout<<A[cnt]<<endl;
    }
return 0;}
