vector<int> manacher(string s){
    int n = s.size();
    if(n == 0)
        return vector<int>();
    n = 2 * n + 1;
    vector<int>L(n,0);
    L[1] = 1;
    int C = 1, R = 2, iMirror;
    int diff = -1;

    for(int i = 2; i < n; i++){
        iMirror = 2 * C - i, L[i] = 0, diff = R - i;
        if(diff > 0)L[i] = min(L[iMirror], diff);
            while (((i + L[i]) < n && (i - L[i]) > 0)
               && (((i + L[i] + 1) % 2 == 0)
               || (s[(i+L[i]+1)/2] == s[(i-L[i]-1)/2])))L[i]++;
        if(i + L[i] > R)C = i, R = i + L[i];
    }

    return L;
}
