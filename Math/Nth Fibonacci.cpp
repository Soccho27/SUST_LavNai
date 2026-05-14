map<int64_t, int64_t> dp;     // works for n<=1e18
int64_t f(int64_t n) {
    if (n <=2) return n >=1; // depends on problem
    if (dp.count(n)) return dp[n];
    auto a =f(n / 2);
    auto b =f(n / 2 + 1);
    if (n % 2 ==0) {
        dp[n] =((((b*2LL)%mod - (a%mod)+mod))%mod * a)%mod;
    } else {
        dp[n] =((a * a)%mod + (b * b)%mod)%mod;
    } return dp[n];
}
