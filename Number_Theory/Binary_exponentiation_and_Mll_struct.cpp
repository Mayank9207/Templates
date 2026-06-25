//------------------------------------------------
template<typename T>
T binpow(T a, ll b) {
  T res = 1;
  while (b > 0) {
    if (b & 1) res = res * a;
    a = a * a;
    b >>= 1;
  }
  return res;
}

template<typename T>
T binpow(T a, ll b, T mod) {
  T res = 1;
  a %= mod;
  while (b > 0) {
    if (b & 1) res = (res * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return res;
}

//------------------------------------------------
const int MOD = 1e9 + 7;
//------------------------------------------------

struct Mll {
  ll v;
  Mll(ll _v = 0) : v((_v % MOD + MOD) % MOD) {}

  Mll operator+(Mll o) const { return Mll(v + o.v); }
  Mll operator-(Mll o) const { return Mll(v - o.v); }
  Mll operator*(Mll o) const { return Mll(v * o.v); }
  Mll inv() const { return binpow(*this, MOD - 2); }
  Mll operator/(Mll o) const { return *this * o.inv(); }

  friend istream& operator>>(istream& is, Mll& m) { ll _v; is >> _v; m = Mll(_v); return is; }
  friend ostream& operator<<(ostream& os, const Mll& m) { return os << m.v; }
};
//------------------------------------------------
