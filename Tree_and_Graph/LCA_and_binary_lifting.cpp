struct LCA {
  int n, LOG;
  vector<vector<int>> up;
  vector<int> depth;

  LCA(const vector<vector<int>>& adj, int root = 0) {
    n = adj.size();
    LOG = 1;
    while ((1 << LOG) <= n) LOG++;

    up.assign(n, vector<int>(LOG, -1));
    depth.assign(n, 0);

    stack<int> st;
    vector<int> par(n, -1);
    depth[root] = 0;
    st.emplace(root);

    while (!st.empty()) {
      int node = st.top(); st.pop();
      for (auto ne : adj[node]) {
        if (ne == par[node]) continue;
        par[ne] = node;
        depth[ne] = depth[node] + 1;
        st.emplace(ne);
      }
    }

    for (int i = 0; i < n; i++) {
      up[i][0] = par[i];
    }

    for (int i = 1; i < LOG; i++) {
      for (int j = 0; j < n; j++) {
        if (up[j][i - 1] != -1) {
          up[j][i] = up[up[j][i - 1]][i - 1];
        }
      }
    }
  }

  int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];

    for (int i = 0; i < LOG; i++) {
      if (diff & (1 << i)) {
        a = up[a][i];
      }
    }

    if (a == b) return a;

    for (int i = LOG - 1; i >= 0; i--) {
      if (up[a][i] != -1 && up[a][i] != up[b][i]) {
        a = up[a][i];
        b = up[b][i];
      }
    }
    return up[a][0];
  }

  int dist(int a, int b) {
    int c = lca(a, b);
    return depth[a] + depth[b] - 2 * depth[c];
  }

  int kth_dad(int u, int k) {
    for (int i = 0; i < LOG; i++) {
      if (k & (1 << i)) {
        u = up[u][i];
        if (u == -1) break;
      }
    }
    return u;
  }
};
