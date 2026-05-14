const int N = 1e5 + 9;
struct PST {
#define lc t[cur].l
#define rc t[cur].r
  struct node {
    int l = 0, r = 0, val = 0;
  } t[20 * N];
  int T = 0;
  int build(int b, int e) {
    int cur = ++T;
    if(b == e) return cur;
    int mid = b + e >> 1;
    lc = build(b, mid);
    rc = build(mid + 1, e);
    t[cur].val = t[lc].val + t[rc].val;
    return cur;
  }
  int upd(int pre, int b, int e, int i, int v) {
    int cur = ++T;
    t[cur] = t[pre];
    if(b == e) {
      t[cur].val += v;
      return cur;
    }
    int mid = b + e >> 1;
    if(i <= mid) {
      rc = t[pre].r;
      lc = upd(t[pre].l, b, mid, i, v);
    } else {
      lc = t[pre].l;
      rc = upd(t[pre].r, mid + 1, e, i, v);
    }
    t[cur].val = t[lc].val + t[rc].val;
    return cur;
  }
  int query(int pre, int cur, int b, int e, int k) {
    if(b == e) return b;
    int cnt = t[lc].val - t[t[pre].l].val;
    int mid = b + e >> 1;
    if(cnt >= k) return query(t[pre].l, lc, b, mid, k);
    else return query(t[pre].r, rc, mid + 1, e, k - cnt);
  }
} t;

//the code returns k-th number in a range l to r if the range were sorted
int V[N], root[N], a[N];
int32_t main() {
  map<int, int>mp;
  int n, q;
  cin >> n >> q;
  for(int i = 1; i <= n; i++) cin >> a[i], mp[a[i]];
  int c = 0;
  for(auto x : mp) mp[x.first] = ++c, V[c] = x.first;
  root[0] = t.build(1, n);
  for(int i = 1; i <= n; i++) {
    root[i] = t.upd(root[i - 1], 1, n, mp[a[i]], 1);
  }
  while(q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << V[t.query(root[l - 1], root[r], 1, n, k)] << '\n';
  }
  return 0;
}

///////
struct node {
    long long int sum;
    node *right, *left;
    node (int val) {
        sum = val;
        right = left = NULL;
    }
    node (node *l, node *r) {
        sum = l -> sum + r -> sum;
        left = l;
        right = r;
    }
};
vector<int> v; int n;
node *build(int start = 0, int end = n-1) {
    if(start == end) 
        return new node(v[start]);
    int mid = (start + end) / 2;
    return new node(build(start, mid), build(mid+1, end));
}
node *update(node *cur, node *prev, int pos, int val, int start = 0, int end = n-1) {
    if(start == end) 
        return new node(val + prev->sum);
    int mid = start + end >> 1;
    return pos <= mid ? new node(update(cur->left, prev->left, pos, val, start, mid), cur->right)
            : new node(cur->left, update(cur->right, prev->right, pos, val, mid+1, end));
}
long long query(node *cur, int l, int r, int left = 0, int right = n-1) {
    if(left > r or right < l) 
        return 0;
    if(left >= l and right <= r)
        return cur->sum;
    int mid = left + right >> 1;
    return query(cur->left, l, r, left, mid) + query(cur->right, l, r, mid+1, right); 
} 
void solve() {
    cin >> n;
    v.assign(n, 0);
    for (int &i : v) cin >> i;
    vector<node> roots;
    roots.push_back(*build());
    int i1 = 1;
    int q; cin >> q;
    int cs = 1;
    while(q--) {
        int id; cin >> id;
        if(id == 1) {
            int ver, pos, val; cin >> ver >> pos >> val;
            node *n1 = update(&roots[ver], &roots[ver],pos-1, val);
            roots.push_back(*n1);
        } else {
            int ver, l, r; cin >> ver >> l >> r;
            cout << query(&roots[ver], l-1, r-1) << endl;
        }
    }
 
}
