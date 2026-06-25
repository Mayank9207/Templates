const ll MAX_N = 1000000LL;
vector<ll> spf(MAX_N + 1);

void summon_sieve() {
  iota(spf.begin(), spf.end(), 0LL);
  for (ll i = 2; i * i <= MAX_N; i++) {
    if (spf[i] == i) {
      for (ll j = i * i; j <= MAX_N; j += i) {
        if (spf[j] == j) spf[j] = i;
      }
    }
  }
}

vector<pair<ll, ll>> prm_fctrs(ll x) {
  vector<pair<ll, ll>> res;
  while (x > 1) {
    ll p = spf[x], cnt = 0;
    while (x % p == 0) { x /= p; cnt++; }
    res.emplace_back(p, cnt);
  }
  return res;
}
