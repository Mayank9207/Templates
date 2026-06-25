//------S-----P-----A-----R-----S-----E------

template <typename T>
struct Sparse {
  int n, k;
  vector<vector<T>> st;

  T merge(T a, T b) {
    return min(a, b);
  }

  Sparse(const vector<T>& a) {
    n = a.size();
    k = __lg(n) + 1;
    st.assign(n, vector<T>(k));

    for (int i = 0; i < n; i++) st[i][0] = a[i];

    for (int j = 1; j < k; j++) {
      for (int i = 0; i + (1 << j) <= n; i++) {
        st[i][j] = merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  T query(int l, int r) {
    int j = __lg(r - l + 1);
    return merge(st[l][j], st[r - (1 << j) + 1][j]);
  }
};
//-------------------------------------------
// Typically, segment tree can handle all the stuff that sparse table does but it shall be used exclusively when the requirements are as follows : 
// 1. The query space is static.
// 2. The query operation is idempotent (smth which doesn't change on overlap)
// 3. (Most imp) When O(1) time per query is required strictly. Segment tree gives O(log n) but it fails when the number of queries are large and 
// the constant factor soars high.
