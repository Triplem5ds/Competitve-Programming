#include <bits/stdc++.h>

using namespace std;

const int SZ = 100005;

int N, H, W;

set<int>rows, cols;

vector<int>rw, cl;

vector<int>Exist[2][SZ];

int x, y;

int sv[SZ];

int chk1(int row, int side, int d){

  memset(sv, 0, sizeof sv);

  for(int i = 0; i <= (d == 1? W : H); i++){
    if(i)
      sv[i] = sv[i - 1];

    bool f = true;

    if(Exist[d][i].size()){

      int lo = 0, hi = Exist[d][i].size() - 1;

      while(lo < hi){

        int md = lo + (hi - lo + 1)/2;

        if(Exist[d][i][md] < row)lo = md;
        else
          hi = md - 1;

      }



      if(Exist[d][i][lo] < row && Exist[d][i][lo] > row - side)f = 0;

    }


    sv[i] += f;
  }


  int bck = 0;
  for(int i = 0; i + side <= (d ? W : H); i++){
    if(sv[i + side] - bck == side + 1)return i;
    bck = sv[i];
  }

  return -1;

}
int chk2(int row, int side, int d){


  memset(sv, 0, sizeof sv);

  for(int i = 0; i <= (d? W : H); i++){

    if(i)
      sv[i] = sv[i - 1];

    bool f = true;

    if(Exist[d][i].size()){

      int lo = 0, hi = Exist[d][i].size() - 1;

      while(lo < hi){

        int md = lo + (hi - lo)/2;

        if(Exist[d][i][md] > row)hi = md;
        else
          lo = md + 1;

      }



      if(Exist[d][i][lo] > row && Exist[d][i][lo] < row + side)f = 0;

    }

    sv[i] += f;

  }
  int bck = 0;
  for(int i = 0; i + side <= (d? W : H); i++){
    if(sv[i + side] - bck == side + 1)return i;
    bck = sv[i];
  }

  return -1;

}


int main(){


  scanf("%d%d%d", &N, &W, &H);

  swap(H, W);

  for(int i = 0; i < N; i++){

    scanf("%d%d", &x, &y);
    Exist[0][x].push_back(y);
    Exist[1][y].push_back(x);
    rows.insert(x);
    cols.insert(y);

  }

  for(auto v : rows)
    sort(Exist[0][v].begin(), Exist[0][v].end()), rw.push_back(v);
  for(auto v : cols)
    sort(Exist[1][v].begin(), Exist[1][v].end()), cl.push_back(v);

  int L = 0, X = 0, Y = 0;


  //down
  if(rw.size() == 0 || rw.back() != H)rw.push_back(H);
  if(rw[0] != 0)rw.push_back(0);


  sort(rw.begin(), rw.end());

  for(int i = 1; i < rw.size(); i++){

    int lo = 0, hi = rw[i];


    while(lo < hi){


      int md = lo + (hi - lo + 1)/2;

      if(chk1(rw[i], md, 1) != -1)lo = md;
      else
        hi = md - 1;

    }


    if(lo > L){
      L = lo;
      Y = rw[i] - lo;
      X = chk1(rw[i], lo, 1);
    }

  }


  //up
  for(int i = 0; i < rw.size() - 1; i++){

    int lo = 0, hi = H - rw[i];

    while(lo < hi){

      int md = lo + (hi - lo + 1)/2;

      if(chk2(rw[i], md, 1) != -1)lo = md;
      else
        hi = md - 1;

    }

    if(lo > L){
      L = lo;
      Y = rw[i];
      X = chk2(rw[i], lo, 1);
    }

  }

  if(cl.size() == 0 || cl.back() != W)cl.push_back(W);
  if(cl[0] != 0)cl.push_back(0);

  sort(cl.begin(), cl.end());


  for(int i = 1; i < cl.size(); i++){

    int lo = 0, hi = cl[i];

    while(lo < hi){

      int md = lo + (hi - lo + 1)/2;

      if(chk1(cl[i], md, 0) != -1)lo = md;
      else
        hi = md - 1;

    }

    if(lo > L){
      L = lo;
      X = cl[i] - lo;
      Y = chk1(cl[i], lo, 0);
    }

  }
  //up
  for(int i = 0; i < cl.size() - 1; i++){

    int lo = 0, hi = W - cl[i];

    while(lo < hi){

      int md = lo + (hi - lo + 1)/2;

      if(chk2(cl[i], md, 0) != -1)lo = md;
      else
        hi = md - 1;

    }

    if(lo > L){
      L = lo;
      X = cl[i];
      Y = chk2(cl[i], lo, 0);
    }

  }

  swap(Y, X);

  cout << X << ' ' << Y << ' ' << L << '\n';

  return 0;
}
