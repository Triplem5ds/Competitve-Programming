struct node{
  node * L;
  node * R;
  int s, e, sum;
  node(node * L = 0, node * R = 0, int s = 0, int e = 0, int sum = 0):
    L(L), R(R), s(s), e(e), sum(sum){}
};
node * trees[N];
node * upd(node * root, int idx, int v){
  node * ret = new node();
  ret->s = root->s;
  ret->e = root->e;
  ret->sum = root->sum + v;
//  cout << root->s << ' ' << root->e << '\n';
//  system("pause");
  if(root->s == root->e)return ret;
  int md = (root->s+root->e)>>1;
  if(idx <= md){
    if(root->L == 0)
      root->L = new node(0,0,root->s,md,0);
    ret->L = upd(root->L,idx,v), ret->R=root->R;
  }
  else{
    if(root->R == 0)
      root->R = new node(0,0,md+1,root->e,0);
    ret->R = upd(root->R,idx,v), ret->L = root->L;
  }
