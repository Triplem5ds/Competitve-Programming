  #include <bits/stdc++.h>
  using namespace std;

  int main() {

    int n, k;

    cin >> n >> k;
    if(n <= k)
      return puts("2");

    n *= 2;

    cout << n/k +  bool(n%k) << '\n';



    return 0;
  }
