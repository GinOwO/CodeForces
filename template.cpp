/*********************************
|               OWO              |
**********************************/
#ifndef _DEBUG
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("tune=native")
#endif

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define int ll
const int MOD = 1e9 + 7;
const int MOD2 = 998244353;
constexpr char dirs4[] = {0, -1, 0, 1, 0};
constexpr char dirs8[] = {0, -1, -1, 0,	 1, 1, 0,  -1, -1,
			  1, 1,	 -1, -1, 1, 1, -1, 0};

// Prefix: V - Vector, P - Pair
// Suffix: F - Create on templates

#define VF(T) vector<T>
#define VPF(T) VF(PF(T))

#define PTTF(T1, T2) pair<T1, T2>
#define PF(T) PTTF(T, T)

#define PTT PTTF(T, T1)
#define VTT VF(PTT)
#define VT VF(T)

typedef VF(int) VI;
typedef VF(VI) VVI;
typedef VF(string) VS;
typedef PF(int) PII;
typedef VPF(int) VII;

typedef tree<PII, null_type, less<PII>, rb_tree_tag,
	     tree_order_statistics_node_update>
	ordered_set;

//TEMPLATE DEFINES
#define TTT template <typename T, typename T1>
#define TT template <typename T>

//QoL Functions
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define YES() std::cout << "YES\n"
#define NO() std::cout << "NO\n"

//LOOP STUFF
#define REPk(i, n) for (int i = 0; i < n; i++)
#define REP(n) REPk(i, n)

//VECTOR/PAIR IO
TTT istream &operator>>(istream &cin, PTT &a)
{
	return cin >> a.first >> a.second;
}

TT istream &operator>>(istream &cin, VT &a)
{
	for (auto &c : a)
		cin >> c;
	return cin;
}

TTT ostream &operator<<(ostream &cout, const PTT &a)
{
	return cout << a.first << ' ' << a.second;
}

TTT ostream &operator<<(ostream &cout, const VTT &a)
{
	for (auto &c : a)
		cout << c << '\n';
	return cout;
}

TT ostream &operator<<(ostream &cout, const VT &a)
{
	int n = a.size();
	if (!n)
		return cout;
	cout << a[0];
	for (int i = 1; i < n; i++)
		cout << ' ' << a[i];
	return cout;
}

TT basic_string<T> operator*(const basic_string<T> &s, int m)
{
	auto r = s;
	m *= s.size();
	r.resize(m);
	for (int i = s.size(); i < m; i++)
		r[i] = r[i - s.size()];
	return r;
}

//MATH
constexpr auto sieve()
{
	constexpr int m = 1'299'710;
	constexpr int N = (m + 1) / 2;

	std::array<bool, N> is_prime{};
	is_prime.fill(true);
	is_prime[0] = false;

	for (int p = 3; p * p < m; p += 2) {
		if (is_prime[p / 2]) {
			for (int i = p * p; i < m; i += 2 * p)
				is_prime[i / 2] = false;
		}
	}

	std::array<int, 100'000> primes{};
	int q = 0;
	primes[q++] = 2;

	for (int p = 3; p < m; p += 2) {
		if (is_prime[p / 2])
			primes[q++] = p;
	}

	return primes;
}

ull pow(ull x, ull y, ull p)
{
	ull res = 1;
	x %= p;
	if (x == 0)
		return 0;
	while (y > 0) {
		if (y & 1)
			res = (res * x) % p;
		y >>= 1;
		x = (x * x) % p;
	}
	return res;
} // Modulo Expo

ull ncr(const ll &n, ll r)
{
	if (n < 1 || r < 1 || r >= n)
		return 1;
	ull k = 1;
	if (n - r < r)
		r = n - r;
	for (ll i = 1; i <= r; i++)
		k = (k * (n - i + 1)) / i;
	return k;
}

bool isPrime(const ll &n)
{
	if (n < 3 || n % 2 == 0)
		return n == 2;
	for (int i = 3; i < sqrt(n) + 1; i += 2)
		if (n % i == 0)
			return false;
	return true;
}

ull count_divisors(ull n)
{
	static const auto primes = sieve();
	ull ans = 1;

	for (int p : primes) {
		if (p * p > n)
			break;
		if (n % p == 0) {
			int exponent = 0;
			while (n % p == 0) {
				n /= p;
				exponent++;
			}
			ans *= (exponent + 1);
		}
	}
	return ans * (1 + (n > 1));
}

ld frac(const ld &a)
{
	return a - floor(a);
} //Fractional part function

TT T gcd(const T &a, const T &b)
{
	return b ? __gcd(a, b) : a;
}

TT T lcm(const T &a, const T &b)
{
	return a * b / gcd(a, b);
}

namespace Structures
{
TT class SegTree {
    private:
	VF(T) a;
	T d;
	const function<T(T, T)> cf;
	int s;
	void build(const VF(T) & q, int l, int r, int p)
	{
		if (l == r) {
			a[p] = q[l];
			return;
		}
		this->build(q, l, (l + r) / 2, 2 * p);
		this->build(q, (l + r) / 2 + 1, r, 2 * p + 1);
		a[p] = cf(a[2 * p], a[2 * p + 1]);
	}
	T query(int ql, int qr, int l, int r, int p = 1)
	{
		if (ql <= l && qr >= r)
			return a[p];
		if (ql > r || qr < l)
			return d;
		T a = this->query(ql, qr, l, (l + r) / 2, 2 * p),
		  b = this->query(ql, qr, (l + r) / 2 + 1, r, 2 * p + 1);
		return cf(a, b);
	}
	void update(int ql, int qr, int l, int r, int v, int p = 1)
	{
		if (ql <= l && qr >= r) {
			a[p] = v;
			return;
		}
		if (ql > r || qr < l)
			return;
		this->update(ql, qr, l, (l + r) / 2, v, 2 * p);
		this->update(ql, qr, (l + r) / 2 + 1, r, v, 2 * p + 1);
		a[p] = cf(a[2 * p], a[2 * p + 1]);
	}

    public:
	SegTree(
		const VF(T) & q, int d = INT_MAX,
		function<T(T, T)> cf = [](T x, T y) { return (x < y) ? x : y; })
		: cf(cf)
		, d(d)
		, s(q.size())
	{
		a = VF(T)(s * 4 + 1, d);
		this->build(q, 0, q.size() - 1, 1);
	}
	T query(int a, int b)
	{
		return this->query(a, b, 0, s - 1);
	}
	void update(int idx, int v)
	{
		update(idx, idx, 0, s - 1, v);
	}
};
}

void solve();

signed main()
{
#ifdef _DEBUG
	cout << "Debugging\n";
#else
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
#endif
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	int t;
	for (cin >> t; t > 0; t--)
		solve();
	return 0;
}

void solve()
{
}