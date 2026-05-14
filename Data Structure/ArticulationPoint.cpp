vector<int> tin, low, vis, mark;
vector<pair<int, int > > bridge;
int timer = 1;

void dfs(int node, int parentNode, vector<int> adj[]){
    tin[node] = low[node] = timer++;
    vis[node] = 1;
	int child = 0;
    for(auto it: adj[node]){
        if(it == parentNode)continue;
        if(!vis[it]){
            dfs(it, node, adj);
			low[node] = min(low[node], low[it]);
			if (low[it] >= tin[node] && parentNode != -1) {
				mark[node] = 1;
			}
			child++;
        }
		else{
			low[node] = min(low[node], tin[it]);
		}
    }
	if (child > 1 && parentNode == -1) {
		mark[node] = 1;
	}
	return;
}

low = vector<int>(n + 1, 0);
tin = vector<int>(n + 1, 0);
vis = vector<int> (n + 1, 0);
mark = vector<int> (n + 1, 0);
vector<int> adj[n + 1];

bridge.clear();
timer = 1;