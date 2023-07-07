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

#define PTT PTTF(T,T2)
#define VTT VF(PTT)
#define VT VF(T)

typedef VF(int) VI;
typedef VF(string) VS;
typedef SF(int) SI;
typedef PF(int) PII;
typedef MF(int) MII;
typedef MTTF(int, VI) MIV;

//QoL Functions
#define all(x) x.begin(), x.end()
#define YES() std::cout << "YES\n"
#define NO() std::cout << "NO\n"

//TEMPLATE DEFINES
#define TTT template<typename T,typename T2>
#define TT template<typename T>

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

TT UNUSED int len(T&x){return x.size();}
TT UNUSED VPF(T) ZIP(T &a, T &b){ll n = min(a.size(), b.size()); VPF(T) v(n, {"",""}); REP(n){v[i].first=a[i]; v[i].second=b[i];} return v; } //Python style ZIP
TT UNUSED T pop(VT &v){T tmp = v[v.size()-1]; v.pop_back(); return tmp;} //Python style pop: returns value on pop
TT UNUSED T OR(T x,T y){return x?x:y;}; TT UNUSED T AND(T x,T y){return x?y:x;} //Python style and/or
TT UNUSED void cmin(T&x,T y){if(x>y)x=y;}; TT UNUSED void cmax(T&x,T y){if(x<y)x=y;} // Change value on comp: x=f(x,y)

//MATH
UNUSED ull ncr(ll n, ll r){if(n<1||r<1||r>=n) return 1; ull k=1;cmin(r,n-r); for(ll i=1;i<=r;i++)k=(k*(n-i+1))/i;return k;}
UNUSED bool isPrime(ll n){if(n<3||n%2==0)return n==2;REPs(3,sqrt(n)+1,2)if(n%i==0)return false;return true;}
UNUSED ld frac(ld&a){return a-floor(a);} //Fractional part function
TT UNUSED T gcd(T&a,T&b){return b?__gcd(a,b):a;}
TT UNUSED T lcm(T&a,T&b){return a*b/gcd(a,b);}

void solve();

signed main(){
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t; cin >> t; while(t--) solve(); 
    return 0;
}

typedef VF(PTTF(int,VI)) K;

void solve(){
    int n, m ,h; cin>>n>>m>>h;
    K arr(n);
    REP(n){
        int tim = 0, points=0, pen=0;
        VI prob(m); cin>>prob;
        sort(all(prob));
        FOR(c,prob){
            tim += c;
            if(tim > h) break;
            pen += tim;
            points++;
        }
        arr[i].first = i;
        arr[i].second = {points, pen};
    }
    sort(all(arr), [](auto&x, auto&y){
        if(x.second[0]>y.second[0]) return 1;
        if(x.second[0]<y.second[0]) return 0;        
       
        if(x.second[1]<y.second[1]) return 1;
        if(x.second[1]>y.second[1]) return 0;
        
        if(x.first==0) return 1;
        else return 0;
    });
    REP(n){
        if(arr[i].first==0){
            cout << i+1 << '\n';
            return;
        }
    }
}