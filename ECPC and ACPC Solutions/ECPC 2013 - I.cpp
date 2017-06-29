#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define F first
#define S second
#define MP make_pair
map<double,bool>vis;
vector<pair<long long,long long>>tmp;
void BFS()
{
    queue<pair<long long,long long> >Q;
    Q.push(MP(0,1));
    tmp.push_back(MP(0,1));
    while(!Q.empty())
    {
        auto p =Q.front();
        for(long long a =1; a < 13; a++)
            for(long long b =a+1; b <= 13; b++)
            {
                long long x =p.F*b+p.S*a;
                long long y =p.S*b;
                long long d =__gcd(x,y);
                x /=d, y /=d;
                if(x >= y) continue;
                if(!vis[(double)x/y]) Q.push(MP(x,y)),tmp.push_back(MP(x,y));
                vis[(double)x/y]=true;
            }
        Q.pop();
    }
}
int main()
{
    freopen("zanzibar.in","r",stdin);
    BFS();
    long long t;
    cin>>t;
    vector<pair<double,pair<long long,long long> > >V;
    for(long long i=0; i<tmp.size(); i++)
    {
        V.push_back(MP((double)tmp[i].F/tmp[i].S,MP(tmp[i].F,tmp[i].S)));
    }
    sort(V.begin(),V.end());
    long long cas=0;
    while(t--)
    {
        ll a,b;
        cin>>a>>b;
        printf("Case %d: ",++cas);
        long long ans1,ans2;
        double Min=5e15;
        double x=(double)a/b;
        long long lo=0,hi=V.size()-1;
        while(lo<hi)
        {
            long long mid=lo+(hi-lo)/2;
            if(V[mid].F>=x)hi=mid;
            else lo=mid+1;
        }
        long long idx1=lo;
        lo=0,hi=V.size()-1;
        while(lo<hi)
        {
            long long mid=lo+(hi-lo+1)/2;
            if(V[mid].F>x)hi=mid-1;
            else lo=mid;
        }
        long long idx2=lo;
        if(abs(V[idx1].F-x)<abs(V[idx2].F-x))
        {
            long long x=V[idx1].S.F,y=V[idx1].S.S;
            long long top = abs(x*b - a*y);
            long long down = y*b;
            long long gcd=__gcd(top,down);
            top/=gcd;
            down/=gcd;
            ans1=top;
            ans2=down;
        }
        else
        {
            long long x=V[idx2].S.F,y=V[idx2].S.S;
            long long top = abs(x*b - a*y);
            long long down = y*b;
            long long gcd=__gcd(top,down);
            top/=gcd;
            down/=gcd;
            ans1=top;
            ans2=down;
        }
        for(int i=max(idx1-150,0LL); i<min(idx1+510,(long long)V.size()); i++)
        {
            if(abs(x-V[i].F)<Min)
            {
                Min=abs(x-V[i].F);
                long long x=V[i].S.F,y=V[i].S.S;
                long long top = abs(x*b - a*y);
                long long down = y*b;
                long long gcd=__gcd(top,down);
                top/=gcd;
                down/=gcd;
                ans1=top;
                ans2=down;
            }
        }
        for(int i=max(idx2-100,0LL); i<min(idx2+100,(long long)V.size()); i++)
        {
            if(abs(x-V[i].F)<Min)
            {
                Min=abs(x-V[i].F);
                long long x=V[i].S.F,y=V[i].S.S;
                long long top = abs(x*b - a*y);
                long long down = y*b;
                long long gcd=__gcd(top,down);
                top/=gcd;
                down/=gcd;
                ans1=top;
                ans2=down;
            }
        }
        cout<<ans1<<'/'<<ans2<<'\n';
    }
    return 0;
}
