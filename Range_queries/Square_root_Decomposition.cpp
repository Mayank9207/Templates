#define ll long long

struct sqrtD {
    vll a, jmp, nxt;
    ll n, sz;

    sqrtD(vll& input_a) {
        this->a = input_a;
        n = a.size();
        sz = ceil(sqrt(n));
        jmp.resize(n);
        nxt.resize(n);

        for (ll i = n - 1; i >= 0; i--) {
            ll en = min(n - 1, (i / sz + 1) * sz - 1);
            
            if (a[i] + i <= en) {
                jmp[i] = jmp[i + a[i]] + 1;
                nxt[i] = nxt[i + a[i]];
            } else {
                jmp[i] = 1;
                nxt[i] = i + a[i];
            }
        }
    }

    void update(ll u, ll val) {
        a[u] = val;
        ll beg = (u / sz) * sz;
        ll en = min(n - 1, (u / sz + 1) * sz - 1);

        for (ll i = en; i >= beg; i--) {
            if (a[i] + i <= en) {
                jmp[i] = jmp[i + a[i]] + 1;
                nxt[i] = nxt[i + a[i]];
            } else {
                jmp[i] = 1;
                nxt[i] = i + a[i];
            }
        }
    }

    pair<ll, ll> query(ll id) {
        ll cnt = 0, lst = n;

        while (id < n) {
            cnt += jmp[id];
            lst = id;
            
            if (nxt[id] >= n) {
                while (id < n) {
                    lst = id;
                    id += a[id];
                }
            } else {
                id = nxt[id];
            }
        }
        return {lst, cnt};
    }
};

//We shall use segtree whenever possible but in following cases, sqrtD shines : 
// 1. We can't merge two segtree intervals in O(1) eg. the Holes problem CF
// 2. When heavy DS like hashmaps are used, it is easier to code sqrtD
// 3. Mo algorithm problems (offline range queries)
