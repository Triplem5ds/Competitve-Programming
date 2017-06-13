#include <bits/stdc++.h>
using namespace std;
typedef long double db;

db dist(db x1, db y1, db x2, db y2){
  return sqrt((x2-x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
db area (db x1, db y1, db x2, db y2, db x3, db y3){
  db x = dist(x1, y1, x2, y2);
  db y = dist(x3, y3, x2, y2);
  db z = dist(x1, y1, x3, y3);
  db par = x + y + z;

  par/=2;

  return sqrt(par * (par - x) * (par - y) * (par - z));
}


pair<db, db>get(db lox, db loy, db hix, db hiy){
  db diffx = (hix - lox)/3;
  db diffy = (hiy - loy)/3;
  return {lox + diffx, loy + diffy};
}

struct vec{
  db x, y;

  vec(db _x,db _y):x(_x), y(_y){}

};

vec toVec(db ax, db ay, db bx, db by){
  return vec(bx - ax, by - ay);
}
vec scale(vec v, db s){
  return vec(v.x * s, v.y * s);
}
pair<db, db> translate(db px, db py, vec v){
  return pair<db, db>(px + v.x, py + v.y);
}
db dot(vec a, vec b){return a.x * b.x + a.y * b.y;}

db sqr(vec v){return v.x * v.x + v.y * v.y;}

db distanceToLine(db px, db py, db ax, db ay, db bx, db by){//find projection of poll p on line a -> b
  vec ap = toVec(ax, ay, px, py);//vector from a to p
  vec ab = toVec(ax, ay, bx, by);//vector from a to b
  db u = dot(ap, ab)/ sqr(ab);//:"D

  auto c = translate(ax, ay, scale(ab, u));

  return dist(px, py, c.first, c.second);

}

pair<db, db>get2(db lineax1, db lineay1, db lineax2, db lineay2,db linebx1, db lineby1, db linebx2, db lineby2){
  db diffx = lineax2 - lineax1;
  db diffy = lineay2 - lineay1;

  db lo = 0.0, hi = 1.0;

  for(int i = 0; i < 100; i++){
    db md1 = lo + (hi - lo)/3;
    db md2 = hi - (hi - lo)/3;
    if(distanceToLine(lineax1 + diffx * md1, lineay1 + diffy * md1, linebx1, lineby1, linebx2, lineby2) > distanceToLine(lineax1 + diffx * md2, lineay1 + diffy * md2, linebx1, lineby1, linebx2, lineby2))
      lo = md1;
    else
      hi = md2;
  }
  //cout << distanceToLine(lineax1 + diffx * lo, lineay1 + diffy * lo, linebx1, lineby1, linebx2, lineby2)  << '\n';
  return {lineax1 + (lo * diffx), lineay1 + (lo * diffy)};
}
db ax, ay, bx, by, cx, cy, dx, dy, ex, ey, fx, fy, px, py, qx, qy, rx, ry;

int main(){

  int t;

  cin >> t;

  while(t--){

    cin >> ax >> ay >> bx >> by >> cx >> cy;

    auto d = get(bx, by, cx, cy);

    dx = d.first;
    dy = d.second;

    auto e = get(cx, cy, ax, ay);

    ex = e.first;
    ey = e.second;

    auto f = get(ax, ay, bx, by);

    fx = f.first;
    fy = f.second;


    auto p = get2(dx, dy , ax, ay, bx, by, ex, ey);
    auto q = get2(cx, cy , fx, fy, bx, by, ex, ey);
    auto r = get2(cx, cy , fx, fy, ax, ay, dx, dy);

    cout << fixed << setprecision(0) << area(p.first, p.second, q.first, q.second, r.first, r.second) << '\n';
  }




}
