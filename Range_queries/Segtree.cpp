//------S-----E-----G-----T-----R-----E-----E------

struct SegTree {
  using node = ll; 
  node neutral = 0;
  int n;
  vector<node> tree;

  SegTree(int _n = 0) : n(_n) {
    tree.assign(4 * n + 1, neutral);
  }

  node merge(node a, node b) {
    return a + b;
  }

  template <typename T>
  void _build(const vector<T>& a, int v, int tl, int tr) {
    if (tl == tr) {
      tree[v] = a[tl];
      return;
    }
    int tm = (tl + tr) / 2;
    _build(a, 2 * v, tl, tm);
    _build(a, 2 * v + 1, tm + 1, tr);
    tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
  }

  node _query(int v, int tl, int tr, int l, int r) {
    if (l > r) return neutral;
    if (l == tl && r == tr) return tree[v];
    int tm = (tl + tr) / 2;
    return merge(_query(2 * v, tl, tm, l, min(r, tm)),
                 _query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
  }

  void _update(int v, int tl, int tr, int pos, node new_val) {
    if (tl == tr) {
      tree[v] = new_val;
      return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm) _update(2 * v, tl, tm, pos, new_val);
    else _update(2 * v + 1, tm + 1, tr, pos, new_val);
    tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
  }

  template <typename T>
  void build(const vector<T>& a) {
    if (n > 0) _build(a, 1, 0, n - 1);
  }

  node query(int l, int r) {
    return _query(1, 0, n - 1, l, r);
  }

  void update(int pos, node new_val) {
    _update(1, 0, n - 1, pos, new_val);
  }
};
//------------------------------------------------
//Supports non commutative and non invertible operations as well eg. RMQ.
