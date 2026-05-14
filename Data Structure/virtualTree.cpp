const int N = 100005;
const int LOGN = 20;
vector<int> g[N];
vector<int> adjacency_vt[N];
int tin[N], tout[N], timer;
int up[N][LOGN];
int depth[N];
bool important[N];
int subtree_count[N];
long long ans;
int total_count;
void dfs(int u, int p, int d) {
    tin[u] = ++timer;
    depth[u] = d;
    up[u][0] = p;
    for (int i = 1; i < LOGN; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : g[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
    tout[u] = ++timer;
}
bool upper(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
int lca(int u, int v) {
    if (upper(u, v)) return u;
    if (upper(v, u)) return v;
    for (int i = LOGN - 1; i >= 0; --i) {
        if (!upper(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}
bool cmp(int a, int b) {
    return tin[a] < tin[b];
}
int build_virtual_tree(vector<int>& vert) {
    sort(vert.begin(), vert.end(), cmp);
    int k = vert.size();
    for (int i = 0; i < k - 1; ++i) {
        vert.push_back(lca(vert[i], vert[i + 1]));
    }
    sort(vert.begin(), vert.end(), cmp);
    vert.erase(unique(vert.begin(), vert.end()), vert.end());
    for (int u : vert) {
        adjacency_vt[u].clear();
    }
    vector<int> stack_v;
    stack_v.push_back(vert[0]);
    for (int i = 1; i < vert.size(); ++i) {
        int u = vert[i];
        while (stack_v.size() >= 2 && !upper(stack_v.back(), u)) {
            adjacency_vt[stack_v[stack_v.size() - 2]].push_back(stack_v.back());
            stack_v.pop_back();
        }
        stack_v.push_back(u);
    }
    while (stack_v.size() >= 2) {
        adjacency_vt[stack_v[stack_v.size() - 2]].push_back(stack_v.back());
        stack_v.pop_back();
    }
    return stack_v[0];
}
void solve(int u, int p) {
    subtree_count[u] = important[u];
    for (int v : adjacency_vt[u]) {
        solve(v, u);
        subtree_count[u] += subtree_count[v];
    }
    if (p != -1) {
        int w = depth[u] - depth[p];
        ans += (long long)w * subtree_count[u] * (total_count - subtree_count[u]);
    }
}
int main() {
    int n;cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    timer = 0;
    dfs(1, 1, 0);
    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        vector<int> vert(k);
        for (int i = 0; i < k; ++i) {
            cin >> vert[i];
            important[vert[i]] = true;
        }
        total_count = k;
        ans = 0;
        int vt_root = build_virtual_tree(vert);
        solve(vt_root, -1);
        cout << ans << "\n";
        for (int x : vert) {
            important[x] = false;
        }
    }
    return 0;
}
