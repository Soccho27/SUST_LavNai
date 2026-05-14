//in main: clr testcase->input in gl[], arr[]->dfs_siz(root,-1);dfs_hld(root,-1);build(1,tim,1);
#include <bits/stdc++.h>
using namespace std;
//#define lli long long
// ... [Macros omitted for brevity] ...
#define lli int

const lli SZ=1e5+10;

// WHAT TO CHANGE: 
// 'inv' is the identity value for queries (e.g., 0 for sum, -INF for max, +INF for min).
// 'lzv' is the null/empty lazy state (e.g., -1 if valid values are >= 0, or 0 if adding).
lli inv=0, lzv=-1; 

vector<lli> g[SZ];
// sub: subtree size
// in/out: entry/exit times for DFS (used to flatten tree and check ancestors)
// head: the highest node in the current heavy chain
// par: parent of a node
// tr/lz: segment tree array and lazy array
// t_n: maps a flattened time index back to its tree node
// arr: base values of the nodes (if provided in input)
lli sub[SZ], in[SZ], out[SZ], head[SZ], par[SZ], tr[4*SZ], lz[4*SZ], t_n[SZ], arr[SZ], tim;

// WHAT TO CHANGE:
// The core operation. Change this to max(x, y), min(x, y), etc., depending on the problem.
lli opr(lli x, lli y) {
    return x+y; 
}

// 1. dfs_siz: Calculates subtree sizes and identifies the "heavy" child.
// NO NEED TO CHANGE
void dfs_siz(lli u, lli p) {
    sub[u]=1, par[u]=p;
    for(lli &v:g[u]) {
        if(v==p) continue;
        dfs_siz(v,u);
        sub[u]+=sub[v];
        // Swapping ensures the heavy child (largest subtree) is always at g[u][0].
        // This makes building the heavy chains in the next step incredibly easy.
        if(sub[v]>sub[g[u][0]]) swap(v,g[u][0]); 
    }
}

// 2. dfs_hld: Flattens the tree into a 1D array and assigns chain heads.
// NO NEED TO CHANGE
void dfs_hld(lli u, lli p) { 
    if(p==-1) head[u]=u; // Root of the whole tree is its own head
    in[u]=++tim;         // Assign 1D array index
    t_n[tim]=u;          // Store which node is at this 1D index
    for(lli &v:g[u]) {
        if(v==p) continue;
        // If 'v' is the heavy child (at index 0), it continues the current chain, so it shares the parent's head.
        // Otherwise, it starts a new "light" chain, so 'v' is its own head.
        head[v]=(v==g[u][0]?head[u]:v);
        dfs_hld(v,u);
    }
    out[u]=tim;          // Exit time
}

// 3. isAncestor: Checks if 'p' is an ancestor of 'u' in O(1) time.
// NO NEED TO CHANGE
inline bool isAncestor(lli p, lli u){
    return in[p]<=in[u]&&out[p]>=out[u];
}

// 4. build: Standard Segment Tree build.
// NO NEED TO CHANGE
void build(lli lo, lli hi, lli node) {
    if(lo==hi) {
        tr[node]=arr[t_n[lo]]; // Note: mapping 1D index back to node to get initial value
        return;
    }
    lli mid=(lo+hi)>>1, lft=node<<1, rgt=lft|1;
    build(lo, mid, lft);
    build(mid+1, hi, rgt);
    tr[node]=opr(tr[lft],tr[rgt]);
}

// 5. propagate: Pushes pending lazy updates to children.
// WHAT TO CHANGE: Update logic depends on the problem (e.g., assignment vs addition).
void propagate(lli node, lli low, lli high) { 
    if(lz[node]!=lzv){
        // Currently configured for ASSIGNMENT sum query: Value * length of segment
        // If doing ADDITION sum query, this would be: tr[node] += (high-low+1)*lz[node];
        tr[node]=(high-low+1)*lz[node]; 
        
        if(low!=high) {
            // Currently ASSIGNMENT lazy. 
            // If ADDITION, use: lz[node*2] += lz[node]
            lz[node*2]=lz[node], lz[node*2+1]=lz[node]; 
        }
        lz[node]=lzv; // Reset lazy tag
    }
}

// 6. upd_val_lazy: Standard Lazy Segment Tree range update.
// NO NEED TO CHANGE (ASSIGNMENT of ADDITION need to be changed)
void upd_val_lazy(lli node, lli low, lli high, lli i, lli j, lli v) {
    propagate(node,low,high);
    if(j<low || high<i) return;
    if(i<=low && high<=j){
        // Currently ASSIGNMENT. If ADDITION, lz[node] += v;
        lz[node]=v; 
        propagate(node,low,high);
        return;
    }
    lli mid=(low+high)>>1, lft=node<<1, rgt=lft|1;
    upd_val_lazy(lft,low,mid,i,j,v);
    upd_val_lazy(rgt,mid+1,high,i,j,v);
    tr[node]=opr(tr[lft],tr[rgt]);
}

// 7. query_lazy: Standard Lazy Segment Tree range query.
// NO NEED TO CHANGE
lli query_lazy(lli node, lli low, lli high, lli i, lli j) {
    propagate(node,low,high);
    if(j<low || high<i) return inv;
    if(i<=low && high<=j) return tr[node];
    lli mid=(low+high)>>1, lft=node<<1, rgt=lft|1;
    lli p1=query_lazy(lft,low,mid,i,j), p2=query_lazy(rgt,mid+1,high,i,j);
    return opr(p1,p2);
}

// 8. update_path: Breaks a tree path u->v into array segments and updates them.
// WHAT TO CHANGE: Uncomment the specific line if working with EDGE weights instead of NODE weights.
void update_path(lli u, lli v, lli val) {
    // Jump the node (u or v) that is deeper/lower in the tree's chain hierarchy
    while(!isAncestor(head[u],v)){
        upd_val_lazy(1,1,tim,in[head[u]],in[u],val);
        u=par[head[u]];
    }
    swap(u,v);
    while(!isAncestor(head[u],v)){
        upd_val_lazy(1,1,tim,in[head[u]],in[u],val);
        u=par[head[u]];
    }
    // Now both u and v are on the SAME heavy chain.
    if(in[v]<in[u]) swap(u,v); // Ensure u is the higher node (LCA)
    
    // IF THE PROBLEM USES EDGE WEIGHTS (stored in child nodes), u (the LCA) must NOT be updated.
    // Replace the next line with: if(u != v) upd_val_lazy(1,1,tim,in[u]+1,in[v],val);
    // ekhane main code er vetore sudhu node niye kaj korlei hobe, eta jeta kore seta holo
    // ekta tree prottekta edge k child node er edge dhore nei
    // 1 2 edge thakle mainly edge 2 er
    // https://vjudge.net/contest/815719#problem/I ei problem a clear hobe bisoy ta
    upd_val_lazy(1,1,tim,in[u],in[v],val);
}

// 9. query_path_lazy: Breaks a tree path u->v into array segments and queries them.
// WHAT TO CHANGE: Same as update_path, handle EDGE weights if necessary.
lli query_path_lazy(lli u, lli v) { 
    lli ret=inv;
    while(!isAncestor(head[u],v)){
        ret=opr(ret,query_lazy(1,1,tim,in[head[u]],in[u]));
        u=par[head[u]];
    }
    swap(u,v);
    while(!isAncestor(head[u],v)){
        ret=opr(ret,query_lazy(1,1,tim,in[head[u]],in[u]));
        u=par[head[u]];
    }
    if(in[v]<in[u]) swap(u,v);
    
    // IF THE PROBLEM USES EDGE WEIGHTS, u (the LCA) must NOT be included in the query.
    // Replace the next line with: if(u != v) ret=opr(ret,query_lazy(1,1,tim,in[u]+1,in[v]));
    // ekhane main code er vetore sudhu node niye kaj korlei hobe, eta jeta kore seta holo
    // ekta tree prottekta edge k child node er edge dhore nei
    // 1 2 edge thakle mainly edge 2 er
    // https://vjudge.net/contest/815719#problem/I ei problem a clear hobe bisoy ta
    ret=opr(ret,query_lazy(1,1,tim,in[u],in[v]));
    return ret;
}

void clr(int n){
    for (int i = 1; i <= n; i++) g[i].clear();
    for(lli i=0; i<=4*n; i++) tr[i]=inv, lz[i]=lzv;
    tim=0;
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t, T=1; //cin>>T;
    for(t=1; t<=T; t++) {
        int n, q;
        cin>>n>>q;
        for(int i=1; i<n; i++) {
            int x, y;
            cin>>x>>y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        dfs_siz(1,-1);
        dfs_hld(1,-1);
        build(1,tim,1);
        while(q--) {
            int u1, v1, u2, v2;
            cin>>u1>>v1>>u2>>v2;
            update_path(u1,v1,1);
            update_path(u2,v2,1);
            cout<<query_lazy(1,1,tim,1,tim)<<endl;
            update_path(u1,v1,0);
            update_path(u2,v2,0);
        }
    }
    return 0;
}