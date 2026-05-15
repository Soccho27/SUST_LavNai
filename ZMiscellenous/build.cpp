{
"cmd" : ["g++ -std=c++20 $file_name -o $file_base_name && timeout 5s ./$file_base_name<input.txt>output.txt"],
"selector" : "source.cpp",
"shell": true,
}

//orderSet
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using o_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> using o_multiset = tree<pair<T,int>, null_type, less<pair<T,int>>, rb_tree_tag, tree_order_statistics_node_update>;
// order_of_key(k) //this returns the count of values that is **less** than k
// find_by_order(k) // this returns the value at index k(0 - based indexing)
// template
ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
