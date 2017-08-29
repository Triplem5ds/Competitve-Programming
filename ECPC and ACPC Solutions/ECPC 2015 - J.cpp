#include "bits/stdc++.h"
using namespace std;

char con[26][26];
int t;
bool isV[26];

string lft(string s){

    string ret = "";

    int n = s.size();

    for(int i = 0; i + 1 < n; i += 2)
        ret.push_back(con[s[i] - 'a'][s[i + 1] - 'a']);

    if(n & 1)
        ret.push_back(s.back());

    return ret;

}
string rt(string s){

    string ret = "";

    int n = s.size();

    if(n & 1)
        ret.push_back(s[0]);

    for(int i = (n & 1); i < s.size(); i += 2)
        ret.push_back(con[s[i + 1] - 'a'][s[i] - 'a']);

    return ret;

}

bool bt(int player, string s){

    if(s.size() == 1){
        return isV[s[0] - 'a'];
    }

    string x = lft(s);
    string y = rt(s);

    assert(x.size() == (s.size() + 1) / 2);
    assert(y.size() == (s.size() + 1) / 2);

    if(player)
        return (bt(player ^ 1, lft(s)) & bt(player ^ 1, rt(s)));
    return (bt(player ^ 1, lft(s)) | bt(player ^ 1, rt(s)));
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    isV[ 'a' - 'a'] = 1;
    isV[ 'e' - 'a'] = 1;
    isV[ 'i' - 'a'] = 1;
    isV[ 'o' - 'a'] = 1;
    isV[ 'u' - 'a'] = 1;

    for(cin >> t; t--; ){

        for(int i = 0; i < 26; i++)
            for(int j = 0; j < 26; j++)
                cin >> con[i][j];

        string s; cin >> s;

        cout << (bt(0, s)? "Salah\n" : "Marzo\n");

    }

    return 0;
}
