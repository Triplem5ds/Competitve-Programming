#include <bits/stdc++.h>
using namespace std;

string txt, pat;

string con(int x){
  stringstream ss;
  ss << x;
  return ss.str();
}

int sv_sub[1000005][10];
int F[1000005];

void fail(){

  int i = 0, j = -1;
  F[0] = -1;

  while(i < pat.size()){

    while(j >= 0 && pat[i] != pat[j]) j = F[j];

    i++, j++;

    F[i] = j;

  }

}

vector<int>sv2;

bool chk(int sz, vector<int> sv){

  string sz_s = con(sz);

  for(char c : sz_s)
    sv[c-'0']--;

  int cnt = 0;

  for(int i = 0; i < 10; i++)
    cnt += sv[i];

  if(cnt != sz)return 0;

  for(int i = 0; i <= 9; i++)
    if(sv[i] < 0)return 0;

  for(int i = 0; i <= 9; i++)
    if(sv[i] < sv2[i])return 0;

  for(int i = 1; i <= 9; i++)
    if(sv[i])return 1;

  return 0;
}

vector<int>sv;

void get_txt(int sz){

  string sz_s = con(sz);

  for(char c : sz_s)
    sv[c-'0']--;

}


bool chk(int idx, int add, int match){

    auto tmp_sv = sv;

    if(!idx && !add)return 0;
    if(!tmp_sv[add])return 0;
    tmp_sv[add]--;



    while(match >= 0 && add != (pat[match] - '0'))match = F[match];
    match++;
    for(int i = 0; i < 10; i++)
      if(tmp_sv[i] < sv_sub[match][i])return 0;


    return 1;
}

int main(){

  //ios_base::sync_with_stdio(0);
  //cin.tie(0);



  cin >> txt >> pat;

  if(txt.size() == 2){

    if(txt[0] == '1')txt.erase(txt.begin());
    else txt.erase(txt.begin() + 1);

    cout << txt << '\n';
    return 0;

  }

  sv.assign(10, 0);
  sv2.assign(10, 0);

  for(char c : txt)sv[c - '0']++;
  for(char c : pat)sv2[c - '0']++;

  int i = 1;

  for(int i = pat.size() - 1; i >= 0; i--)
    for(int j = 0; j < 10; j++)
        sv_sub[i][j] = sv_sub[i + 1][j] + (j == (pat[i] - '0'));


  for( ; ; i++){

    if(chk(i, sv))break;

  }

  int sz = i;

  get_txt(sz);

  string ans = "";

  int f = 0;


  i = 0;

  fail();


  while(i < sz){

    for(int j = (i==0); j < 10; j++){
      if(chk(i, j, f)){
        ans.push_back(j + '0');
        sv[j]--;
        break;
      }
    }
    while(f >= 0 && ans[i] != pat[f])f = F[f];

    i++, f++;

    if(f == pat.size())break;

  }

  for(int i = 0; i < 10; i++)
    while(sv[i]--)
      ans.push_back('0' + i);

  cout << ans << '\n';

  return 0;
}
