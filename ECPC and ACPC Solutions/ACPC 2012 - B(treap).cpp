#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct treap{
	char key;
	int prior,cnt;
	treap*l,*r;
	treap(){}
	treap(char key,int prior):key(key),prior(prior),l(NULL),r(NULL),cnt(1){}
};

typedef treap * ptreap;

int cnt(ptreap t){
	if(!t)return 0;else return t->cnt;
}

void upd(ptreap&t){
	if(!t)return ;
	t->cnt=cnt(t->l)+cnt(t->r)+1;
}

void split(ptreap t,int key,ptreap&l,ptreap&r,int add=0){
	if(!t)return void(l=r=NULL);
	upd(t);
	int ckey=add+cnt(t->l)+1;
	if(ckey>=key)split(t->l,key,l,t->l,add),r=t;else split(t->r,key,t->r,r,add+1+cnt(t->l)),l=t;
	upd(t);
}

void merge(ptreap&t,ptreap l,ptreap r){
	upd(l);
	upd(r);
	if(!l)t=r;else
		if(!r)t=l;else
			if(l->prior>r->prior)merge(l->r,l->r,r),t=l;else merge(r->l,l,r->l),t=r;
	upd(t);
}


ptreap gettreap(string s){
	ptreap ret=NULL;
	int i;
	for(i=0;i<s.length();i++)merge(ret,ret,new treap(s[i],(rand()<<15)+rand()));
	return ret;
}

void writetreap(ptreap t){
	if(!t)return;
	writetreap(t->l);
	cout<<t->key;
	writetreap(t->r);
}

ptreap root, lft, rt, instreap, tmplft, tmprt;

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  string s;
  cin >> s;
  int idx, l, r;

  root = gettreap(s);

  while(true){
    cin >> s;
    if(s == "END")break;
    if(s == "I"){
      cin >> s >> idx;
      idx++;
   //   cout << 1 << endl;
      split(root, idx, lft, rt);
      instreap = gettreap(s);

      merge(lft, lft, instreap);
      merge(root, lft, rt);

    }
    else{
      cin >> l >> r;

      l++, r++;

      split(root, l, lft, rt);
      split(rt, r - l + 2, tmplft, tmprt);

      writetreap(tmplft);

      merge(rt, tmplft, tmprt);
      merge(root, lft, rt);
      cout << '\n';
    }

  }

}
