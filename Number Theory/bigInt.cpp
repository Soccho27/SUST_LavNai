struct biginteger {
    string s;
    biginteger() { s = ""; }
    biginteger(string x) { s = x; }
    biginteger operator%(const int mod) {
        biginteger ret;
        int total = 0;
        for (int i = 0; i < s.size(); i++) {
            total = total * 10 + (s[i] - '0');
            total %= mod;
        }
        ret.s = to_string(total);
        return ret;
    }
    biginteger operator+(biginteger t) {
        biginteger ret;
        string ss = s;
        reverse(ss.begin(), ss.end());
        reverse(t.s.begin(), t.s.end());
        while (ss.size() != t.s.size()) {
            if (ss.size() < t.s.size()) ss.push_back('0');
            else t.s.push_back('0');
        }
        int carry = 0;
        for (int i = 0; i < ss.size(); i++) {
            int val = (carry + ss[i] - '0' + t.s[i] - '0');
            ret.s.push_back(val % 10 + '0');
            carry = val / 10;
        }
        if (carry) ret.s.push_back(carry + '0');
        reverse(ret.s.begin(), ret.s.end());
        return ret;
    }
    biginteger operator*(const biginteger &t) {
        biginteger ret;
        for (int i = 0; i < t.s.size(); i++) {
            if (t.s[i] == '0') continue;
            int dig = t.s[i] - '0';
            int carry = 0;
            biginteger tmp;
            for (int j = s.size() - 1; j >= 0; j--) {
                int val = dig * (s[j] - '0') + carry;
                tmp.s.push_back((val % 10) + '0');
                carry = val / 10;
            }
            if (carry) tmp.s.push_back(carry + '0');
            reverse(tmp.s.begin(), tmp.s.end());
            for (int j = 0; j < t.s.size() - 1 - i; j++) {
                tmp.s.push_back('0');
            }
            ret = ret + tmp;
        }
        return ret;
    }
};
biginteger bigmod(biginteger a, int b, int mod) {
    if (b == 1) return a % mod;
    biginteger res = bigmod(a, b / 2, mod);
    res = (res * res) % mod;
    if (b % 2) res = (res * a) % mod;
    return res;
}
void construct(vector<biginteger> &v, vector<biginteger> &pref, vector<biginteger> &suf, int n, int mod) {
    for (int i = 0; i < n; i++) {
        v[i] = v[i] % mod;
    }
    pref[0] = v[0] % mod;
    suf[n - 1] = v[n - 1] % mod;
    for (int i = 1; i < n; i++) {
        pref[i] = pref[i - 1] * v[i];
        pref[i] = pref[i] % mod;
    }
    for (int i = n - 2; i >= 0; i--) {
        suf[i] = suf[i + 1] * v[i];
        suf[i] = suf[i] % mod;
    }
}
bool get(int i, vector<biginteger> &v, vector<biginteger> &pref, vector<biginteger> &suf, int n, int mod) {
    biginteger val, val2;
    if (i != 0) {
        val = pref[i - 1];
    }
    if (i != n - 1) {
        if (val.s.empty()) {
            val = suf[i + 1];
        } else {
            val = val * suf[i + 1];
            val = val % mod;
        }
    }
    val2 = bigmod(v[i], n - 1, mod);
    return (val.s == val2.s);
}