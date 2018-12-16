//O(log ^ 2 N) updates and queries


#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;


Tree<int> t[N];

void add(int idx, int v){
    for(int x = ++idx; x < N; x += x & -x){
        t[x].insert(v);
    }
}
void erase(int idx, int v){
    for(int x = ++idx; x < N; x += x & -x)
        t[x].erase(v);
}
int get(int idx,  int limit){
    int ret = 0;
    for(int x = ++idx; x; x -= x & -x)
        ret += (t[x].order_of_key(limit+1));
    return ret;
}
