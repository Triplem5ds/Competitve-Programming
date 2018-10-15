#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


class MarriageProblemRevised {
public:
	int neededMarriages(vector <string> grid) {
		int n = grid.size();
		int m = grid[0].size();
		
		vector<int>men(n);
		vector<int>women(m);
		
		for(int i = 0;i < n; i++)
		    for(int j= 0; j< m; j++){
		        men[i] *= 2;
		        women[j] *= 2;
		        if(grid[i][j] == '1'){
		            men[i]++;
		            women[j]++;
		        }
		    }
		
		if(*min_element(men.begin(),men.end()) == 0||*min_element(women.begin(),women.end()) == 0)
		    return -1;
		
		int ans = 100;
		
		for(int i =0; i < (1 << n); i++)
		    for(int j = 0; j < (1 << m); j++){
		        
		        int x = i, y = j;
		        int cnt1(0), cnt2(0);
		        for(int k = 0; k < n; k++){
		            if((1 << (n-k-1)) & i){
		                cnt1++;
		                y |= men[k];
		            }
		        }
		        for(int k = 0; k < m; k++){
		            if((1 << (m-k-1)) & j){
		                cnt2++;
		                x |= women[k];
		            }
		        }
		        
		        if(x == (1<<n)-1 && y == (1<<m) - 1)
		            ans = min(ans,cnt1+cnt2);
		        
		    }
		return ans;
	}
};
