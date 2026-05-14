vector<vector<int>> adj, up;
vector<int> tin, tout, sts, dep;
void dfs(int cur, int par = 1)
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
    int parrr = lca(u, v);
    int dis1 = abs(dep[u] - dep[parrr]) + 1;
    int dis2 = abs(dep[v] - dep[parrr]);
    return dis1 + dis2 - 1;// -1 to exclude single node to get dis
}
struct centroid {
  vector<vector<int> > edges;
  vector<bool> vis;
  vector<int> par;
  vector<int> sz;
  int n;
  void init(int s) {
    n = s;
    edges = adj;
    vis = vector<bool>(n + 1, 0);
    par = vector<int>(n + 1);
    sz = vector<int>(n + 1);
  }
  void edge(int a, int b) {
    edges[a].push_back(b);
    edges[b].push_back(a);
  }
  int find_size(int v, int p = -1) {
    if (vis[v]) return 0;
    sz[v] = 1;
    for (int x: edges[v]) {
      if (x != p) {
        sz[v] += find_size(x, v);
      }
    }
    return sz[v];
  }
  int find_centroid(int v, int p, int n) {
    for (int x: edges[v]) {
      if (x != p) {
        if (!vis[x] && sz[x] > n / 2) {
          return find_centroid(x, v, n);
        }
      }
    }
    return v;
  }
  void init_centroid(int v, int p = -1) {
    find_size(v);
    int c = find_centroid(v, -1, sz[v]);
    vis[c] = true;
    par[c] = p;
    for (int x: edges[c]) {
      if (!vis[x]) {
        init_centroid(x, c);
      }
    }
  }
};
int n, m, k, q, l, r, x, y, z;
int a[1000005];
int b[1000005];
int c[1000005];
string s, t;
int ans = 0;
centroid ct;
int best[100005];
void update(int v) {
	best[v] = 0;
	int u = v;
	while (ct.par[u] != -1) {
		u = ct.par[u];
		best[u] = min(best[u], getDis(u, v));
	}
}
int query(int v) {
	int ans = best[v];
	int u = v;
	while (ct.par[u] != -1) {
		u = ct.par[u];
		ans = min(ans, best[u] + getDis(u, v));
	}
	return ans;
}
void solve()
{
    int n,q;cin>>n>>q;
    up.assign(n + 1, vector<int>(26, 0));
    adj = vector<vector<int > >(n + 1);
    tin.assign(n + 1, 0);
    tout.assign(n + 1, 0);
    sts.assign(n + 1, 0);
    dep.assign(n + 1, 0);
    for(int i = 0; i < n - 1; i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 1; i <= n; i++)best[i] = inf; // this means the closest red node to node i
    dfs(1);
    ct.init(n);
    ct.init_centroid(1);
    update(1); // node 1 is initially painted red
    while(q--){
        int op, node;cin>>op>>node;
        if(op == 1){
            update(node);
        }
        else{
            cout<<query(node)<<nl;
        }
    }
}