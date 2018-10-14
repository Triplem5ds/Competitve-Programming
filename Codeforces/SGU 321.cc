#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;
const int N = 2e5+5;

vector<int>adj[N];
int n;
int u[N], v[N], w[N];
string str;
vector<int>ans;
int dfs(int a, int lvl, int p = -1){

    int ret = (lvl + 1) / 2;

    for(auto i : adj[a]){
        int nxt = a ^ u[i] ^ v[i];
        if(nxt == p)continue;
        int tmp = dfs(nxt,lvl+1,a);
        tmp-=(w[i]);
        if(tmp > lvl){
            ans.push_back(i);
            tmp--;
        }
        ret = max(ret, tmp);
    }
    return ret;
}
int main(){
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE

    cin >> n;

    for(int i = 1; i < n; i++){

        cin >> u[i] >> v[i];
        cin >> str;
        if(str[0] == 'a'){
            cin >> str; w[i] = 0;
        }   else {
            w[i] = 1;
        }
        adj[u[i]].push_back(i);
        adj[v[i]].push_back(i);
    }

    dfs(1,0);
    cout << ans.size() << "\n";

    for(int i = 0; i < ans.size(); i++)
        cout << ans[i] << " \n"[i+1==ans.size()];


    return 0;
}
