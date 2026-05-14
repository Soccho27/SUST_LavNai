const int N = 3e5 + 9; // 1-base query
struct RangeBIT {
  int64_t M[N], A[N];
  RangeBIT() {
    memset(M, 0, sizeof(M));
    memset(A, 0, sizeof(A));
  }
  void update(int i, int64_t mul, int64_t add) {
    for (; i < N; i +=i & (-i)) {
      M[i] +=mul;
      A[i] +=add;
    }
  }
  void upd(int l, int r, int64_t x) {
    update(l, x, -x * (l - 1));
    update(r + 1, -x, x * r);
  }
  int64_t query(int i) {
    int64_t mul =0, add =0;
    for (; i > 0; i -=i & (-i)) {
      mul +=M[i];
      add +=A[i];
    }
    return (mul * i + add);
  }
  int64_t query(int l, int r) {
    return query(r) - query(l - 1);
  }
};
