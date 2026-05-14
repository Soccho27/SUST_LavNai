vector<int> tin, low, vis;
vector<pair<int, int > > bridge;
int timer = 1;
void findBridge(int node, int parentNode, vector<int> adj[]){
    tin[node] = low[node] = timer++;
    vis[node] = 1;
    for(auto it: adj[node]){
        if(it == parentNode)continue;
        if(!vis[it]){
            findBridge(it, node, adj);
        }
        low[node] = min(low[node], low[it]);
        if(tin[node] < low[it])bridge.push_back({node, it});
    }
}
low = vector<int>(n + 1, 0);
tin = vector<int>(n + 1, 0);
vis = vector<int> (n + 1, 0);
vector<int> adj[n + 1];
bridge.clear();
timer = 1;