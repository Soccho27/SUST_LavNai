const int N = 10001, mod = 998244353;
const double eps = 1e-9;
string s;
struct palindromic_tree{
    struct node {
        int len, link;
        array<int, 2> next;
        node(int l = 0) : len(l), link(0) {
            next.fill(-1);
        }
    };
    vector<node> t;
    int last;
    palindromic_tree() {
        t.clear();
		t.reserve(s.size() + 3);
        t.push_back(node(-1));
        t.push_back(node(0));
        t[0].link = 0;
        t[1].link = 0;
        last = 1;
    }
    int getSufflink(int u, int i) {
        while(1) {
            int idx = i - 1 - t[u].len;
            if(idx >= 0 && s[idx] == s[i]) return u;
            u = t[u].link;
        }
    }
    int add(int i) {
        int u = getSufflink(last, i);
        int c = s[i] - 'a';
        if(t[u].next[c] != -1) {
            last = t[u].next[c];
            return 0;
        }
        node nv(t[u].len + 2);
        t.push_back(nv);
        int v = t.size() - 1;
        t[u].next[c] = v;
        if(t[v].len == 1) {
            t[v].link = 1;
        }
        else {
            int w = t[u].link;
            w = getSufflink(w, i);
            t[v].link = t[w].next[c];
        }
        last = v;
        return 1;
    }
};
void solve() {
    cin >> s;
    int n = s.size();
    palindromic_tree tree;
    int pre = 0;
    string out;
    out.reserve(n);
    for (int i = 0; i < n; i++) {
        tree.add(i);
        // tree.t.size() - 2 = number of non-root nodes = total distinct palindromes found so far
        int cur = tree.t.size() - 2;
        out.push_back('0' + (cur - pre));
        pre = cur;
    }
    cout << out << '\n';
}