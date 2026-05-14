template<typename T>
struct segTree{
   int n;   vector<T> t, lazy;
   T neutral =0; // 0 for sum, -inf for max, +inf for min
   SegTree(int n =0): n(n), t(4*n, neutral), lazy(4*n, 0){}
   T combine(T a, T b){}
   void push(int v, int tl, int tr){}
   void build(const vector<T>& a, int v, int tl, int tr){}
   void build(const vector<T>& a) { build(a, 1, 1, n); }
   void update(int v, int tl, int tr, int l, int r, T add){}
   void update(int l, int r, T add){update(1, 1, n, l, r, add);}
   T query(int v, int tl, int tr, int l, int r){}
   T query(int l, int r) { return query(1, 1, n, l, r); }
   void set_value(int pos, T val) { // overwrite
      T cur =query(pos, pos);
      update(pos, pos, val - cur);
   }
};
template<typename T>
struct HLD {
   int n,timer;   vector<vector<int>> g;
   vector<int> parent, depth, heavy, head, pos, sz;
   vector<T> flat;   SegTree<T> seg;
   HLD(int n): n(n), g(n+1), parent(n+1), depth(n+1),heavy(n+1,-1), head(n+1), pos(n+1), sz(n+1), timer(0) {}
   void add_edge(int u, int v) {
      g[u].push_back(v);
      g[v].push_back(u);
   }
   int dfs(int u, int p) {
      parent[u] =p; sz[u] =1;
      int max_sz =0;
      for (int v : g[u]) if (v !=p) {
         depth[v] =depth[u] + 1;
         int sub =dfs(v, u);    sz[u] +=sub;
         if (sub > max_sz) max_sz =sub, heavy[u] =v;
      }
      return sz[u];
   }
   void decompose(int u, int h, const vector<T>& val) {
      head[u] =h;   pos[u] =++timer; flat[timer] =val[u];
      if (heavy[u] !=-1) decompose(heavy[u], h, val);
      for (int v : g[u])if (v !=parent[u] && v !=heavy[u])   decompose(v, v, val);
   }
   void init(const vector<T>& val, int root =1) {
      flat.assign(n+1, 0);
      dfs(root, 0);
      timer =0;
      decompose(root, root, val);
      seg =SegTree<T>(n);
      seg.build(flat);
   }
   void update_path(int u, int v, T add) {    // Path range add
      while (head[u] !=head[v]) {
         if (depth[head[u]] < depth[head[v]]) swap(u, v);
         seg.update(pos[head[u]], pos[u], add);
         u =parent[head[u]];
      }
      if (depth[u] > depth[v]) swap(u, v);
      seg.update(pos[u], pos[v], add);
   }
   T query_path(int u, int v) {    // Path query (need to update)
      T res =0; // check
      while (head[u] !=head[v]) {
         if (depth[head[u]] < depth[head[v]]) swap(u, v);
         res +=seg.query(pos[head[u]], pos[u]);
         u =parent[head[u]];
      }
      if (depth[u] > depth[v]) swap(u, v);
      res +=seg.query(pos[u], pos[v]);
      return res;
   }
   void update_subtree(int u, T add) {    // Subtree range add
      seg.update(pos[u], pos[u] + sz[u] - 1, add);
   }
   T query_subtree(int u) {   // Subtree query
      return seg.query(pos[u], pos[u] + sz[u] - 1);
   }
   void set_value(int u, T val) {   // Point set
      seg.set_value(pos[u], val);
   }
   int lca(int u, int v) {
      while (head[u] !=head[v]) {
         if (depth[head[u]] < depth[head[v]]) swap(u, v);
         u =parent[head[u]];
      }
      return depth[u] < depth[v] ? u : v;
   }
};
