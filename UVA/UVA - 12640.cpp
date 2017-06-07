#include <bits/stdc++.h>
using namespace std;
string s;
vector<string>divide(string s){
  vector<string>ret;
  istringstream ss(s);
  string buffer;
  while(ss >> buffer)ret.push_back(buffer);
  return ret;
}
int con(string s){
  int ret;
  istringstream (s) >> ret;
  return ret;
}
int main(){
  char c;
  vector<int>a;
  vector<string>v;
  while(getline(cin, s)){
    a.clear();
    v = divide(s);
    for(auto c : v)
      a.push_back(con(c));
    int ret = 0, mx = 0;
    for(int i = 0; i < a.size(); i++){
      mx += a[i];
      ret = max(ret, mx);
      if(mx < 0)
        mx = 0;
    }
    printf("%d\n", ret);

  }




  return 0;
}
