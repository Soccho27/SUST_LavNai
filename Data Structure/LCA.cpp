int timer = 0;
vector<vector<int>> adj, up;
vector<int> tin, tout, sts, dep;

void dfs(int cur, int par)
{
	tin[cur] = ++timer;
    // for node == 1 take par also equals to 1
	up[cur][0] = par;
	dep[cur] = dep[par] + 1;

	for (int i = 1; i <= 25; ++i)
		up[cur][i] = up[up[cur][i - 1]][i - 1];

	for (int child : adj[cur])
	{
		if (child != par)
		{
			dfs(child, cur);
			sts[cur] += sts[child];
		}
	}
	sts[cur]++;
	tout[cur] = ++timer;
}
     
bool is_ancestor(int u, int v)
{
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
	if (is_ancestor(u, v))
		return u;
	if (is_ancestor(v, u))
		return v;

	for (int i = 25; i >= 0; --i) {
		if (!is_ancestor(up[u][i], v))
			u = up[u][i];
	}

	return up[u][0];
}

int getDis(int u, int v){
    // this returns all the nodes between them including them(inclusive)
    int parrr = lca(u, v);
    int dis1 = abs(dep[u] - dep[parrr]) + 1;
    int dis2 = abs(dep[v] - dep[parrr]);
    return dis1 + dis2;
}
up.assign(n + 1, vector<int>(26, 0));
adj = vector<vector<int > >(n + 1);
tin.assign(n + 1, 0);
tout.assign(n + 1, 0);
sts.assign(n + 1, 0);
dep.assign(n + 1, 0);
