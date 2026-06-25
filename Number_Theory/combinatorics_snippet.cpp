#define ll long long 

//it is dependent on the binpow function

namespace SaiyaNCr {
  ll mod = 1000000007LL;
  ll COMB_MAXN = 1000000;
  vector<ll> fac;
  vector<ll> inv_fac;

  ll modinv(ll a) {
    if (mod <= 1) return 0;
    return binpow(a, mod - 2, mod);
  }

  void awaken(ll maxn = 1000000) {
    COMB_MAXN = maxn;
    if (mod == 0) return;
    fac.assign(COMB_MAXN, 0);
    inv_fac.assign(COMB_MAXN, 0);
    fac[0] = 1;
    for (int i = 1; i < COMB_MAXN; ++i) fac[i] = fac[i - 1] * i % mod;
    inv_fac[COMB_MAXN - 1] = modinv(fac[COMB_MAXN - 1]);
    for (int i = COMB_MAXN - 2; i >= 0; --i) inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
  }

  ll nCr_fast(ll n, ll r) {
    return fac[n] * inv_fac[r] % mod * inv_fac[n - r] % mod;
  }

  ll nCr_on_the_fly(ll n, ll r) {
    ll num = 1;
    ll n_mod = n % mod;
    for (ll i = 0; i < r; i++) {
      num = num * (n_mod - i + mod) % mod;
    }
    return num * inv_fac[r] % mod;
  }

  ll nCr_lucas(ll n, ll r) {
    if (r == 0) return 1;
    ll ni = n % mod, ri = r % mod;
    if (ri > ni) return 0;
    ll current_digit_nCr = nCr_fast(ni, ri);
    return current_digit_nCr * nCr_lucas(n / mod, r / mod) % mod;
  }

  ll nCr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (mod == 0) {
      r = min(r, n - r);
      ll res = 1;
      for (ll i = 1; i <= r; ++i) res = res * (n - i + 1) / i;
      return res;
    }
    if (mod == 1) return 0;
    r = min(r, n - r);
    if (n < COMB_MAXN && (ll)fac.size() > n) {
      return nCr_fast(n, r);
    }
    else if (mod < COMB_MAXN && (ll)fac.size() > mod) {
      return nCr_lucas(n, r);
    }
    else {
      return nCr_on_the_fly(n, r);
    }
  }

  vector<ll> get_divisors(ll n, bool sorted = true) {
    vector<ll> divs;
    for (ll i = 1; i * i <= n; ++i) {
      if (n % i == 0) {
        divs.push_back(i);
        if (i != n / i) divs.push_back(n / i);
      }
    }
    if (sorted) sort(divs.begin(), divs.end());
    return divs;
  }
}
