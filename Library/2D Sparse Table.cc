short get(int x1, int y1, int x2, int y2){
  int lenx=x2-x1+1;
  int kx=sv[lenx];
  int leny=y2-y1+1;
  int ky=sv[leny];
  short ret = 0;
  ret = max(ret, max(tb[kx][x1][ky][y1], tb[kx][x2-(1 << kx) + 1][ky][y1]));
  ret = max(ret, max(tb[kx][x1][ky][y2 - (1 << ky) + 1], tb[kx][x2-(1 << kx) + 1][ky][y2 - (1 << ky) + 1]));
  return ret;
}
void build(){
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++){
      tb[0][i][0][j] = a[i][j];
    }
  for(int j = 1; (1 << j) <= m; j++)
    for(int ii = 1; ii <= n; ii++)
      for(int jj = 1; jj + (1 << (j-1)) <= m; jj++)
        tb[0][ii][j][jj] = max(tb[0][ii][j-1][jj], tb[0][ii][j-1][jj + (1 << (j-1))]);
  for(int i = 1; (1 << i) <= n; i++)
    for(int j = 0;(1<<j) <= m; j++){

      for(int ii = 1; ii + (1 << (i-1)) <= n; ii++)
        for(int jj = 1; jj + (1 << (j-1)) <= m; jj++)
          tb[i][ii][j][jj] = max(
          tb[i-1][ii][j][jj],
          tb[i-1][ii+(1 << (i-1))][j][jj]
          );
    }
}
