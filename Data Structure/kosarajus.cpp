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