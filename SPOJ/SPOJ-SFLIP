#include "bits/stdc++.h"
using namespace std;

typedef pair<int,int> ii;

const int N = 1e5 + 5;

struct node{

    int sum, sumL, sumR;
    int bst, bstL, bstR;
    int pref, prefL, prefR;
    int suff, suffL, suffR;

    node(){}
    node(int x, int i){
        sum = bst = pref = suff = x;
        sumL = bstL = prefL = suffL = i;
        sumR = bstR = prefR = suffR = i;
    }

}tree[N<<2], tree2[N<<2];

bool lz[N<<2];
int x;
vector<function<bool(int,int)>> cmp = {
    [](int i, int j){return i < j;},
    [](int i, int j){return i > j;}
};
void inv(node & x){
    x.bst = -x.bst;
    x.pref = -x.pref;
    x.suff = -x.suff;
    x.sum = -x.sum;
}
void push(int node, int s, int e){

    if(lz[node]){
        inv(tree2[node]);
        inv(tree[node]);
        swap(tree2[node],tree[node]);
        if(s!=e){
            lz[node<<1] ^= 1;
            lz[node<<1|1] ^= 1;
        }
        lz[node] = 0;
    }

}
node mrg(node & L, node & R, bool f){

    node ret;
    ret.sum = L.sum + R.sum;ret.sumL=L.sumL;ret.sumR=R.sumR;
    ///prefix either LPrefix or Lsum and RPrefix
    if(cmp[f](L.pref,L.sum+R.pref)){
        ret.pref=L.pref;ret.prefL=L.prefL;ret.prefR=L.prefR;
    }   else {
        ret.pref=L.sum+R.pref;ret.prefL=L.sumL;ret.prefR=R.prefR;
    }///suffix either Rsuffix or Rsum and Lsuffix
    if(cmp[f](R.suff,R.sum+L.suff)){
        ret.suff=R.suff;ret.suffL=R.suffL;ret.suffR=R.suffR;
    }   else {
        ret.suff=R.sum+L.suff;ret.suffL=L.suffL;ret.suffR=R.sumR;
    }

    if(cmp[f](L.bst,R.bst)){
        ret.bst = L.bst; ret.bstL = L.bstL; ret.bstR = L.bstR;
    }   else {
        ret.bst = R.bst; ret.bstL = R.bstL; ret.bstR = R.bstR;
    }

    if(cmp[f](L.suff+R.pref,ret.bst)){
        ret.bst = L.suff + R.pref;
        ret.bstL = L.suffL;
        ret.bstR = R.prefR;
    }
    return ret;
}
void build(int o, int s, int e){
    if(s==e){
        scanf("%d", &x);
        tree[o] = tree2[o] = node(x,s);
    }   else {
        int md = (s+e) >> 1;
        build(o<<1,s,md);
        build(o<<1|1,md+1,e);
        tree[o] = mrg(tree[o<<1], tree[o<<1|1], 0);
        tree2[o] = mrg(tree2[o<<1], tree2[o<<1|1], 1);
    }
}
void upd(int node, int s, int e, int l, int r){
    push(node,s,e);
    if(r < s || e < l)return;
    if(l <= s && e <= r){
        lz[node] ^= 1;
        push(node,s,e);
        return;
    }
    int md = (s+e) >> 1;
    upd(node<<1,s,md,l,r);
    upd(node<<1|1,md+1,e,l,r);
    tree[node] = mrg(tree[node<<1], tree[node<<1|1], 0);
    tree2[node] = mrg(tree2[node<<1], tree2[node<<1|1], 1);
}

int main(){
    int n, k;   scanf("%d%d", &n, &k);
    build(1,1,n);
    for(int i = 0; i < k && tree[1].bst < 0; i++)
        upd(1,1,n,tree[1].bstL, tree[1].bstR);
    cout << tree[1].sum << '\n';
    return 0;
}
