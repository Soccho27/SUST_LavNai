const int64_t inf = int(1e18);
struct MCF{
   struct Edge {
      int to, rev; int64_t cap, cost, flow = 0;
   };
   int n; vector<vector<Edge>> g;
   vector<int64_t> h, dist; vector<int> prevv, preve;
   MCF(int _n = 0) {
      init(_n);
   }
   void init(int _n) {
      n = _n;
      g.assign(n, {});
      h.assign(n, 0);
      dist.assign(n, 0);
      prevv.assign(n, 0);
      preve.assign(n, 0);
   }
   void add(int u, int v, int64_t cap, int64_t cost) {
      g[u].push_back({v, (int)g[v].size(), cap, cost});
      g[v].push_back({u, (int)g[u].size() - 1, 0, -cost});
   }
   pair<int64_t, int64_t> flow(int s, int t, int64_t need = inf) {
      pair<int64_t, int64_t> res = {0, 0};
      fill(h.begin(), h.end(), 0LL);
      while (need > 0) {
         priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> pq;
         fill(dist.begin(), dist.end(), inf);
         dist[s] = 0;
         pq.emplace(0, s);
         while (!pq.empty()) {
            auto [d, v] = pq.top();
            pq.pop();
            if (dist[v] < d) continue;
            for (int i = 0; i < (int)g[v].size(); ++i) {
               Edge &e = g[v][i];
               if (e.cap > e.flow) {
                  int64_t nc = d + e.cost + h[v] - h[e.to];
                  if (dist[e.to] > nc) {
                     dist[e.to] = nc;
                     prevv[e.to] = v;
                     preve[e.to] = i;
                     pq.emplace(nc, e.to);
                  }
               }
            }
         }
         if (dist[t] == inf)  break;
         for (int i = 0; i < n; ++i) {
            if (dist[i] < inf) {
               h[i] += dist[i];
            }
         }
         int64_t push = need;
         for (int v = t; v != s; v = prevv[v]) {
            push = min(push, g[prevv[v]][preve[v]].cap - g[prevv[v]][preve[v]].flow);
         }
         need -= push;
         res.first += push;
         res.second += push * h[t];
         for (int v = t; v != s; v = prevv[v]) {
            Edge &e = g[prevv[v]][preve[v]];
            e.flow += push;
            g[e.to][e.rev].flow -= push;
         }
      }
      return res;
   }
   void clear_flow() {
      for (auto &vec : g) {
         for (auto &e : vec) {
            e.flow = 0;
         }
      }
   }
};
