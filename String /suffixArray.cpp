struct SuffixArray {
    int n;
    string s;
    vector<int> sa, rankv, tmp, lcp;
    SuffixArray(const string &str) {
        s = str;
        n = s.size();
        sa.resize(n);
        rankv.resize(n);
        tmp.resize(n);
        build();
        build_lcp();
    }
    void counting_sort(int k) {
        int maxi = max(256ll, (long long)n) + 5;
        vector<int> cnt(maxi, 0), sa2(n);
        for (int i = 0; i < n; i++) {
            int key = (i + k < n) ? rankv[i + k] + 1 : 0;
            cnt[key]++;
        }
        for (int i = 1; i < maxi; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            int key = (sa[i] + k < n) ? rankv[sa[i] + k] + 1 : 0;
            sa2[--cnt[key]] = sa[i];
        }
        sa.swap(sa2);
    }

    void build() {
        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rankv[i] = (unsigned char)s[i];
        }
        for (int k = 1; k < n; k <<= 1) {
            counting_sort(k);
            counting_sort(0);
            tmp[sa[0]] = 0;
            int r = 0;
            for (int i = 1; i < n; i++) {
                int cur1 = rankv[sa[i]], cur2 = (sa[i] + k < n ? rankv[sa[i] + k] : -1);
                int prev1 = rankv[sa[i - 1]], prev2 = (sa[i - 1] + k < n ? rankv[sa[i - 1] + k] : -1);
                if (cur1 != prev1 || cur2 != prev2) r++;
                tmp[sa[i]] = r;
            }
            rankv.swap(tmp);
            if (r == n - 1) break;
        }
    }

    void build_lcp() {
        lcp.assign(max(0, n - 1), 0);
        vector<int> inv(n);
        for (int i = 0; i < n; ++i) inv[sa[i]] = i;
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (inv[i] == n - 1) { k = 0; continue; }
            int j = sa[inv[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
            lcp[inv[i]] = k;
            if (k) --k;
        }
    }
};

void solve(const string &s, const string &t) {
    // build local combined string so we don't mutate inputs
    int n = s.size();
    string combined = s + '$' + t;
    int N = combined.size();

    SuffixArray sa(combined);
}
