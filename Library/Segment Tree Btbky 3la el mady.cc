struct node{
  node * L, *R;
  int val;
  node(){
    val = 0;
    L = R = NULL;
  }
};
int mrg(node * x, node * y){
  /// i am sure on of them is not empty
  /// be careful according to the problem
  assert((x) || (y));
  if(!x)return y->val;
  if(!y)return x->val;
  return x->val + y->val;
}
node * upd(node * root, int s, int e, int idx, int v){
  node * ret = new node();
  if(s == e){
    ret->val = v;
    return ret;
  }
  int md = (s+e)>>1;
  if(idx <= md){
    if(root->L == 0)
      root->L = new node();
    ret->L = upd(root->L,s,md,idx,v), ret->R = root->R;
  } else{
    if(root->R == 0)
      root->R = new node();
    ret->R = upd(root->R,md+1,e,idx,v), ret->L = root->L;
  }
  ret->val = mrg(ret->L, ret->R);
  return ret;
}
int qry(node * root, int s, int e, int l, int r){
  if(!root || r < s || e < l)return 0;
  if(l <= s && e <= r){
    return root->val;
  }
  int md = (s+e)>>1;
  return qry(root->L,s,md,l,r)
  + qry(root->R,md+1,e,l,r);
}

node * trees[100005];

/*
  trees[x] = upd(trees[prv(x)]);
*/
