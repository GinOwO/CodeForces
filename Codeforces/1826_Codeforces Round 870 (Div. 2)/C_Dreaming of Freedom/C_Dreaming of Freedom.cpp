#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#pragma ide diagnostic ignored "modernize-use-emplace"
#pragma GCC optimize("Ofast")
#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<utility>
#include<algorithm>
#include<random>
#include<chrono>
using namespace std;

#define UNUSED [[maybe_unused]]
UNUSED mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
UNUSED uniform_real_distribution<> pp(0.0,1.0);
#define ll long long
#define ull unsigned ll
#define ld long double

#define PF(T) pair<T,T>
#define PTTF(a,b) pair<a,b>
#define PDD PF(ld)
#define PII PF(ll)
#define PTt PF(T1)
#define PTT PTTF(T1,T2)
#define PIII PTTF(int,pii)
#define PSS PF(string)

#define VF(T) vector<T>
#define VPF(T) VF(PF(T))
#define VII VF(PII)
#define VTT VF(PTT)
#define VT VF(T1)
#define VI VF(ll)
#define VD VF(ld)
#define VS VF(string)
#define VSS VF(PSS)


#define FI first
#define SE second
#define PUSH push_back
#define POP pop_back
#define RET return

#define YES() std::cout << "YES\n"
#define NO() std::cout << "NO\n"

#define TTT template<typename T1,typename T2>
#define TT template<typename T1>

#define REPk(k, n) for(int i=k; i<n; i++)
#define REP(n) REPk(0, n)
#define FOR(var,seq) for(auto&var:seq)

TTT istream &operator>>(UNUSED istream &cin,PTT &a) { RET cin>>a.FI>>a.SE; }
TT istream &operator>>(UNUSED istream &cin, UNUSED VT &a) { FOR(c,a) cin>>c; RET cin; }
TTT ostream &operator<<(ostream &cout,const PTT &a) { RET cout<<a.FI<<' '<<a.SE; }
TTT ostream &operator<<(UNUSED ostream &cout,UNUSED const VTT &a) { FOR(c,a) cout<<c<<'\n'; RET cout; }
TT ostream &operator<<(ostream &cout,const VT &a) { int n=a.size(); if (!n) RET cout; cout<<a[0]; for (int i=1; i<n; i++) cout<<' '<<a[i]; RET cout; }
TT basic_string<T1> operator*(const basic_string<T1> &s,int m) { auto r=s; m*=s.size(); r.resize(m); for (int i=s.size(); i<m; i++) r[i]=r[i-s.size()]; RET r; }

TT UNUSED VT range(T1 l,T1 r,T1 step=1) { assert(step>0); int n=(r-l+step-1)/step,i; VT res(n); for (i=0; i<n; i++) res[i]=l+step*i; RET res; }
TT UNUSED VPF(T1) ZIP(T1 &a, T1 &b){ll n = min(a.size(), b.size()); VPF(T1) v(n, {"",""}); REP(n){v[i].FI=a[i]; v[i].SE=b[i];} RET v; }
TT UNUSED T1 pop(VT &v){T1 tmp = v[v.size()-1]; v.POP(); RET tmp;}
TT UNUSED T1 OR(T1&x,T1&y){return x?x:y;}; TT UNUSED T1 AND(T1&x,T1&y){return x?y:x;}
TT UNUSED void cmin(T1&x,T1&y){if(x>y)x=y;}; TT UNUSED void cmax(T1&x,T1&y){if(x<y)x=y;}


UNUSED ld frac(ld a){RET a-floor(a);}
UNUSED const ll inf=1e18;
UNUSED const int mod=998244353;
UNUSED const int mod2=1e9+7;

void solve();

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t; while(t--) solve(); RET 0;
}

void solve(){
    int n, m; cin >> n >> m;
    if(n&1)YES();
    else NO();
}