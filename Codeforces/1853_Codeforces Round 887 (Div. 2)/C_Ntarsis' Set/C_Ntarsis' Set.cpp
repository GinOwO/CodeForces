/*********************************
|               OWO              |
**********************************/
#pragma GCC optimize("Ofast,unroll-loops") 
#pragma GCC target("avx,avx2,fma") 

#include<bits/stdc++.h>
using namespace std;

#define UNUSED [[maybe_unused]]
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define int ll
UNUSED const ll iinf=1e9;
UNUSED const ll inf=1e18;
UNUSED const int mod=998244353;
UNUSED const int mod2=1e9+7;

//Prefix: V - Vector, P - Pair, S - Set, M - Map
//Suffix: F - Create on templates
//Types: 2 letter = pair, T: template, D: double, I: int, S: string

#define VF(T) vector<T>
#define VPF(T) VF(PF(T))

#define PTTF(T1,T2) pair<T1,T2>
#define PF(T) PTTF(T,T)

#define SF(T) set<T>

#define MTTF(T1, T2) map<T1, T2>
#define MF(T) MTTF(T,T)

#define PTT PTTF(T,T1)
#define VTT VF(PTT)
#define VT VF(T)

typedef VF(int) VI;
typedef VF(string) VS;
typedef SF(int) SI;
typedef PF(int) PII;
typedef MF(int) MII;
typedef MTTF(int, VI) MIV;

//TEMPLATE DEFINES
#define TTT template<typename T,typename T1>
#define TT template<typename T>
#define TTU TT UNUSED

//QoL Functions
#define all(x) x.begin(), x.end()
#define YES() std::cout << "YES\n"
#define NO() std::cout << "NO\n"

//LOOP STUFF
#define REPi(i,k,n,s) for(auto i=k; i<n; i+=s)
#define REPs(k,n,s) REPi(i,k,n,s)
#define REPk(k,n) REPs(k,n,1)
#define REP(n) REPk(0, n)
#define FOR(var,seq) for(auto&var:seq)

// BITWISE
/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))// '!!' to make sure this returns 0 or 1

#define BITMASK_SET(x, mask) ((x) |= (mask))
#define BITMASK_CLEAR(x, mask) ((x) &= (~(mask)))
#define BITMASK_FLIP(x, mask) ((x) ^= (mask))
#define BITMASK_CHECK_ALL(x, mask) (!(~(x) & (mask)))
#define BITMASK_CHECK_ANY(x, mask) ((x) & (mask))

//VECTOR/PAIR IO
TTT istream &operator>>(UNUSED istream &cin,PTT &a) { return cin>>a.first>>a.second; }
TT istream &operator>>(UNUSED istream &cin, UNUSED VT &a) { FOR(c,a) cin>>c; return cin; }
TTT ostream &operator<<(ostream &cout,const PTT &a) { return cout<<a.first<<' '<<a.second; }
TTT ostream &operator<<(UNUSED ostream &cout,UNUSED const VTT &a) { FOR(c,a) cout<<c<<'\n'; return cout; }
TT ostream &operator<<(ostream &cout,const VT &a) { int n=a.size(); if (!n) return cout; cout<<a[0]; for (int i=1; i<n; i++) cout<<' '<<a[i]; return cout; }
TT basic_string<T> operator*(const basic_string<T> &s,int m) { auto r=s; m*=s.size(); r.resize(m); for (int i=s.size(); i<m; i++) r[i]=r[i-s.size()]; return r; }

TTU int len(T&x){return x.size();}
TTU VPF(T) ZIP(T &a, T &b){ll n = min(a.size(), b.size()); VPF(T) v(n, {"",""}); REP(n){v[i].first=a[i]; v[i].second=b[i];} return v; } //Python style ZIP
TTU T pop(VT &v){T tmp = v[v.size()-1]; v.pop_back(); return tmp;} //Python style pop: returns value on pop
TTU T OR(T x,T y){return x?x:y;}; TTU T AND(T x,T y){return x?y:x;} //Python style and/or
TTU void cmin(T&x,T y){if(x>y)x=y;}; TTU void cmax(T&x,T y){if(x<y)x=y;} // Change value on comp: x=f(x,y)

//MATH
UNUSED ull ncr(ll n, ll r){if(n<1||r<1||r>=n) return 1; ull k=1;cmin(r,n-r); for(ll i=1;i<=r;i++)k=(k*(n-i+1))/i;return k;}
UNUSED bool isPrime(ll n){if(n<3||n%2==0)return n==2;REPs(3,sqrt(n)+1,2)if(n%i==0)return false;return true;}
UNUSED ld frac(ld&a){return a-floor(a);} //Fractional part function
TTU T gcd(T&a,T&b){return b?__gcd(a,b):a;}
TTU T lcm(T&a,T&b){return a*b/gcd(a,b);}

void solve();

signed main(){
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t; cin >> t; while(t--) solve(); 
    return 0;
}

void solve(){
    int n;cin>>n;
    VI a(n); cin>>a;
    if(a[0]!=1){
        cout << 1 << '\n';
        return;
    }
    
}