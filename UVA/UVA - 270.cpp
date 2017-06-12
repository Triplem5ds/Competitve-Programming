#include <bits/stdc++.h>
using namespace std;
typedef long double db;
/*
  my idea was basically that if i should take every point and shift it -1 on the x - axis using the difference between that point and every other point 
  and save it's new y - coordinatie in a map then loop over the map and find the maximum number.
*/
const db EPS = 1e-7;
const db PI = acos(-1);


struct PT{
  db x, y;
  PT(){}

  PT(db _x, db _y):x(_x), y(_y){}

  PT operator + (const PT &a){return PT(x + a.x, y + a.y);}
  PT operator - (const PT &a){return PT(x - a.x, y - a.y);}
  PT operator * (const db &a){return PT(x * a, y * a);}
  bool operator == (const PT &a){return x==a.x && y ==a.y;}


};
istream &operator >> (istream &is, PT &p){return is >> p.x >> p.y;}
ostream &operator << (ostream &os, PT &p){return os << p.x << ' ' << p.y;}

struct vec{
  db x, y;

  vec(db _x,db _y):x(_x), y(_y){}

};

vec toVec(PT a, PT b){
  return vec(b.x - a.x, b.y - a.y);
}
vec scale(vec v, db s){
  return vec(v.x * s, v.y * s);
}

PT translate(PT p, vec v){
  return PT(p.x + v.x, p.y + v.y);
}

db dot(vec a, vec b){return a.x * b.x + a.y * b.y;}

db sqr(vec v){return v.x * v.x + v.y * v.y;}


db dist(PT a, PT b){return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));}

db distanceToLine(PT p, PT a, PT b, PT &c){//find projection of point p on line a -> b
  vec ap = toVec(a, p);//vector from a to p
  vec ab = toVec(a, b);//vector from a to b
  db u = dot(ap, ab)/ sqr(ab);//:"D

  c = translate(a, scale(ab, u));

  return dist(p, c);

}

db get_angle (PT a, PT o, PT b){
  vec oa = toVec(o, a), ob = toVec(o, b);
  //dot product = |A||B|cos(@) = A.B
  return acos(dot(oa,ob)/sqrt(sqr(oa) * sqr(ob)));
}

db cross(vec a, vec b){return a.x * b.y - a.y * b.x;}

db get_angle(vec a, vec b){
  db dot1 = dot(a, b);
  db det = cross(a, b);
  return atan2(det, dot1);
}


bool collinear(PT p, PT q, PT r){
  //checks if the angle between the two vectors is 0 (aka less than the epsilon)
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

db torad(db angle){
  return angle * PI / 180;
}

db w, h, alpha;


struct circle{
  PT cen;
  db r;
  circle (PT cen = PT(0.0, 0.0), db r = 0.0):cen(cen), r(r){}

};

int grid[500][500];

bool check_in(PT x, circle y){
  return dist(x, y.cen) <= y.r ;
}

PT fss(string s){
  db a = 0, b = 0;

  int i = 0;
  for(; i < s.size(); i++){
    if(s[i] == ' ')break;
    a = a * 10 + (s[i] - '0');
  }
  i++;
  for(; i < s.size(); i++){
    if(s[i] == ' ')break;
    b = b * 10 + (s[i] - '0');
  }
  return PT(a, b);
}

int main(){
 // freopen("in.in", "r", stdin);
  int t;
  cin >> t;
  string str;
  getline(cin, str);
  getline(cin, str);

  while(t--){
    char c;

    vector<PT>v;

    getline(cin, str);

    int n;

    for(n = 0; str.size() != 0; ){
      istringstream iss(str);
      db x, y;
      iss >> x >> y;
      v.push_back(PT(x, y));
      n++;
      if(cin.eof())break;
      getline(cin, str);

    }



    int ans = 0;

    //cout << v[0] << endl;

    for(int i = 0; i < n; i++){
      map<db, int>mp;

      for(int j = 0; j < n; j++){
        if(i == j)continue;
        PT diff = v[j] - v[i];
        db k = -1/diff.x;
        db y2 = v[i].y + k * diff.y;
        mp[y2]++;
        if(i == 0){
          if(j == 1 || j == 2){
            //cout << diff << endl;
            //cout << y2 << endl;
            //system("pause");
          }
        }
      }
      for(auto it : mp)
        ans = max(ans, it.second);

    }

    cout << ans + 1 << '\n';

    if(t)puts("");
  }

}
