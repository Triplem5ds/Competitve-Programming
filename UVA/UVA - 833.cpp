#include <bits/stdc++.h>
using namespace std;
typedef long double db;
typedef long long ll;

/*
  the idea is you to sort all lines by their upper y - axis
  so that you can process segments from top - down then check
  if this point is directly above this segment and between it's x - axis
  see if the segment is tiled to the right or the left and assign the value
  of either side to the point according to that
*/


const db EPS = 1e-7;
const db PI = acos(-1);


struct PT{
  int x, y;
  PT(){}

  PT(int _x, int _y):x(_x), y(_y){}

  PT operator + (const PT &a){return PT(x + a.x, y + a.y);}
  PT operator - (const PT &a){return PT(x - a.x, y - a.y);}
  PT operator * (const db &a){return PT(x * a, y * a);}
  bool operator == (const PT &a){return x==a.x && y ==a.y;}

};
bool cmp(pair<PT, PT> a, pair<PT, PT> b){
  return max(a.first.y, a.second.y) > max(b.first.y, b.second.y);
}

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

db distanceToLine(PT p, PT a, PT b, PT &c){//find projection of poll p on line a -> b
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
  bool intersect(circle other){
    if(dist(cen, other.cen) <= (other.r + r) * (other.r) + r)
      return 1;
    return 0;
  }

};


bool check_in(PT x, circle y){
  return dist(x, y.cen) <= y.r ;
}

vector<pair<PT, PT> >lines;
int n;

int solve(PT p){

  for(int i = 0; i < n; i++){

    if(p.x >= lines[i].first.x && p.x <= lines[i].second.x){
      PT diff = lines[i].second - lines[i].first;
      int diff2 = p.x - lines[i].first.x;
      int y = lines[i].first.y  + ((db)diff2/diff.x) * diff.y;

      if(p.y >= y){

        if(lines[i].second.y > lines[i].first.y){
          p = lines[i].first;
        }
        else
          p = lines[i].second;

      }

    }
  }

  return p.x;
}

int main(){

  int t;

  cin >> t;

  while(t--){
    lines.clear();

    cin >> n;

    lines.resize(n);

    for(int i = 0; i < n; i++){
      cin >> lines[i].first >> lines[i].second;

      if(lines[i].first.x > lines[i].second.x)
        swap(lines[i].first, lines[i].second);

    }

    int q;

    cin >> q;

    sort(lines.begin(), lines.end(), cmp);

    PT p;

    while(q--){
      cin >> p;

      cout << solve(p) << '\n';
    }

    if(t)puts("");

  }
}
