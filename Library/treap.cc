#include "bits/stdc++.h"
using namespace std;

typedef struct item *pitem;

struct item{
  int key, cnt, val;
  pitem l, r;
  item(int val) : key(rand()), cnt(1), val(val), l(0), r(0){}
};
int cnt(pitem t){return t? t->cnt : 0;}
void upd(pitem t){
  if(t){
    t->cnt = cnt(t->l) + cnt(t->r) + 1;
    ///Update treap according to the problem
    ///Same way as segment tree
  }

}
void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->key > r->key)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd(t);
}
void split (pitem t, pitem & l, pitem & r, int key) {
    if (!t)
        return void( l = r = 0 );
    if (key <= cnt(t->l))
        split (t->l, l, t->l, key),  r = t;
    else
        split (t->r, t->r, r, key-1-cnt(t->l)),  l = t;
    upd(t);
}
