{
"cmd" : ["g++ -std=c++20 $file_name -o $file_base_name && timeout 5s ./$file_base_name<input.txt>output.txt"],
"selector" : "source.cpp",
"shell": true,
}

//orderSet
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;   
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

//STDIN
freopen("mj5.in", "r", stdin);  freopen("mj5.out", "w", stdout);
