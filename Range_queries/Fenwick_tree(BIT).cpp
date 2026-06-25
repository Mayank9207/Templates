template <typename T>
struct Fenwick {
  int n;
  vector<T> tree;
  Fenwick(int n) : n(n), tree(n + 1, 0) {}

  void update(int i, T delta) {
    for (; i <= n; i += i & -i) tree[i] += delta;
  }

  T query(int i) {
    T sum = 0;
    for (; i > 0; i -= i & -i) sum += tree[i];
    return sum;
  }

  T query(int l, int r) {
    if (l > r) return 0;
    return query(r) - query(l - 1);
  }
};
//this defaults to sum, we can change it as per the requirements of the problem but it can handle invertible operations only
