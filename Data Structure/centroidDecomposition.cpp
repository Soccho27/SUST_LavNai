// =================== Tree: LCA + Centroid Decomposition ===================
// Usage: tree.init(n); tree.add_edge(u,v); tree.build(root);
//        tree.dist(u,v), tree.lca(u,v), tree.cpar[v]
struct Tree {
    int n, L = 20;
    vector<vector<int>> adj, up;
    vector<int> dep, sub, cpar;
    vector<bool> removed;
 
    void init(int N) {
        n = N;
        adj.assign(n + 1, {});
        up.assign(n + 1, vector<int>(L, 0));
        dep.assign(n + 1, 0);
        sub.assign(n + 1, 0);
        cpar.assign(n + 1, -1);
        removed.assign(n + 1, false);
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs_lca(int u, int p) {
        up[u][0] = p;
        for (int i = 1; i < L; ++i) up[u][i] = up[up[u][i - 1]][i - 1];
        for (int v : adj[u]) if (v != p) {
            dep[v] = dep[u] + 1;
            dfs_lca(v, u);
        }
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        int d = dep[u] - dep[v];
        for (int i = L-1; i>=0; i--) 
            if ((d >> i) & 1) u = up[u][i];
        if (u == v) return u;
        for (int i = L - 1; i >= 0; i--)
            if (up[u][i] != up[v][i]) { u = up[u][i]; v = up[v][i]; }
        return up[u][0];
    }
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    int dfs_size(int u, int p) {
        sub[u] = 1;
        for (int v : adj[u]) if (v != p && !removed[v])
            sub[u] += dfs_size(v, u);
        return sub[u];
    }
    int find_centroid(int u, int p, int treeSize) {
        for (int v : adj[u]) if (v != p && !removed[v])
            if (sub[v] * 2 > treeSize)
                return find_centroid(v, u, treeSize);
        return u;
    }
    void build_centroid(int u, int p) {
        int sz = dfs_size(u, -1);
        int c  = find_centroid(u, -1, sz);
        removed[c] = true;
        cpar[c] = p;
        for (int v : adj[c]) if (!removed[v])
            build_centroid(v, c);
    }
    void build(int root = 1) {
        dep[root] = 0;
        dfs_lca(root, root);
        build_centroid(root, -1);
    }
} tree;
