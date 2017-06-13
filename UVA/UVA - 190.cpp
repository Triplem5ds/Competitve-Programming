#include <bits/stdc++.h>
using namespace std;

/*
  either the line is fully in the rectangle or intersects another line.
*/

struct pt{
  int x, y;
  pt(int _x, int _y):x(_x), y(_y){}

};

int xl, xr, yt, yb;

int ret(pt p, pt q, pt r){
  int val = (q.y - p.y) * (r.x - q.x) -
  (q.x - p.x) * (r.y - q.y);
  if(val == 0)return 0; 

  return (val > 0)? 1 : 2; 
}

bool onSegment(pt p, pt q, pt r){
  // check if pt q belongs to line pr
  
  if(q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))return 1;

  return 0;
}

bool intersect(pt p1, pt q1, pt p2, pt q2){
  int o1 = ret(p1, q1, p2);
  int o2 = ret(p1, q1, q2);
  int o3 = ret(p2, q2, p1);
  int o4 = ret(p2, q2, q1);

  if(o1 != o2 && o3 != o4)return true;

  if(o1 == 0 && onSegment(p1, p2, q1))return true;
  if(o2 == 0 && onSegment(p1, q2, q1))return true;
  if(o3 == 0 && onSegment(p2, p1, q2))return true;
  if(o4 == 0 && onSegment(p2, q1, q2))return true;

  return false;
}


int main(){

  int t;

  cin >> t;

  pt a(0,0), b(0,0);

  while(t--){
    cin >> a.x >> a.y >> b.x >> b.y;

    cin >> xl >> yt >> xr >> yb;

    if(xl > xr)swap(xl, xr);
    if(yt < yb)swap(yt, yb);

    bool f = false;

    if(intersect(a, b, pt(xl,yb), pt(xl, yt)))f = true;
    if(intersect(a, b, pt(xl,yb), pt(xr, yb)))f = true;
    if(intersect(a, b, pt(xr,yt), pt(xr, yb)))f = true;
    if(intersect(a, b, pt(xr,yt), pt(xl, yt)))f = true;
    if(a.x >= xl && a.x <= xr && b.x >= xl && b.x <= xr &&
    a.y >= yb && a.y <= yt && b.y >= yb && b.y <= yt )f = true;

    puts(f? "T" : "F");

  }



}
