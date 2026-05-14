int scc = 0;
stack<int> st;
vector<int> vis(sz), adj[sz], adjT[sz];
void dfs(int node){
    vis[node] = 1;
    for(auto it: adj[node]){
        if(!vis[it])dfs(it);
    }
    st.push(node);
}
void dfsT(int node){
    vis[node] = 1;
    for(auto it: adjT[node]){
        if(!vis[it])dfsT(it);
    }
}
void kosaRajus(int n){
    for(int i = 1; i <= n; i++){
        if(!vis[i])dfs(i);
    }
    for(int i = 1; i <= n; i++){
        for(auto it: adj[i]){
            adjT[it].push_back(i);
        }
    }
    vis.assign(n + 1, 0);
    while(!st.empty()){
        int node = st.top();
        st.pop();
        if(!vis[node]){
            dfsT(node);
            scc++;
        }
    }
}
////// amar ta 
typedef struct node {
   int vis; vector<int> adj; vector<int> ulta;
  } node;
  node tree[300010]; vector<vector<int>> scc(300010); stack<int> st; int scount = 0;
  void dfs(int u) {
    tree[u].vis = 1;
    f(i,tree[u].adj.size()) {
        int next = tree[u].adj[i];
        if(tree[next].vis==0) dfs(next);
    }
    st.push(u);
  }
  void dfs2(int u) {
    tree[u].vis = 1; scc[scount-1].push_back(u); 
    f(i,tree[u].ulta.size()) {
        int next = tree[u].ulta[i];
        if(tree[next].vis==0) dfs2(next);
    }
  }
 for(int i = 1 ; i <= n;i++) if(tree[i].vis==0){ dfs(i);}
  while (!st.empty()) {
    int u = st.top();st.pop();
    if(tree[u].vis==0) {
        scount++;   dfs2(u);
    }
   };
