/*********************************
|               OWO              |
**********************************/
#pragma GCC optimize("Ofast,unroll-loops") 
#pragma GCC target("tune=native") 

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define int ll
const ll iinf=1e9;
const ll inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;

//Prefix: V - Vector,P - Pair,S - Set,M - Map
//Suffix: F - Create on templates
//Types: 2 letter=pair,T: template,D: double,I: int,S: string

#define VF(T) vector<T>
#define VPF(T) VF(PF(T))

#define PTTF(T1,T2) pair<T1,T2>
#define PF(T) PTTF(T,T)

#define SF(T) set<T>

#define MTTF(T1,T2) map<T1,T2>
#define MF(T) MTTF(T,T)

#define PTT PTTF(T,T1)
#define VTT VF(PTT)
#define VT VF(T)

typedef VF(int) VI;
typedef VF(string) VS;
typedef SF(int) SI;
typedef PF(int) PII;
typedef MF(int) MII;
typedef MTTF(int,VI) MIV;

//TEMPLATE DEFINES
#define TTT template<typename T,typename T1>
#define TT template<typename T>

//QoL Functions
#define all(x) x.begin(),x.end()
#define YES() std::cout<<"YES\n"
#define NO() std::cout<<"NO\n"

//LOOP STUFF
#define REPi(i,k,n,s) for(auto i=k;i<n;i+=s)
#define REPs(k,n,s) REPi(i,k,n,s)
#define REPk(k,n) REPs(k,n,1)
#define REP(n) REPk(0,n)
#define FOR(var,seq) for(auto&var:seq)

// BITWISE
/* a=target variable,b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))// '!!' to make sure this returns 0 or 1

#define BITMASK_SET(x,mask) ((x) |= (mask))
#define BITMASK_CLEAR(x,mask) ((x) &= (~(mask)))
#define BITMASK_FLIP(x,mask) ((x) ^= (mask))
#define BITMASK_CHECK_ALL(x,mask) (!(~(x) & (mask)))
#define BITMASK_CHECK_ANY(x,mask) ((x) & (mask))

//VECTOR/PAIR IO
TTT istream &operator>>(istream &cin,PTT &a){return cin>>a.first>>a.second;}
TT istream &operator>>(istream &cin,VT &a){FOR(c,a)cin>>c;return cin;}
TTT ostream &operator<<(ostream &cout,const PTT &a){return cout<<a.first<<' '<<a.second;}
TTT ostream &operator<<(ostream &cout,const VTT &a){FOR(c,a)cout<<c<<'\n';return cout;}
TT ostream &operator<<(ostream &cout,const VT &a){int n=a.size();if (!n)return cout;cout<<a[0];for (int i=1;i<n;i++)cout<<' '<<a[i];return cout;}
TT basic_string<T> operator*(const basic_string<T> &s,int m){auto r=s;m*=s.size();r.resize(m);for (int i=s.size();i<m;i++)r[i]=r[i-s.size()];return r;}

TT int len(const T&x){return x.size();}
TT VPF(T)ZIP(const T&a,const T&b){ll n=min(a.size(),b.size());VPF(T)v(n,{"",""});REP(n){v[i].first=a[i];v[i].second=b[i];} return v;} //Python style ZIP
TT T pop(VT &v){T tmp=v[v.size()-1];v.pop_back();return tmp;} //Python style pop: returns value on pop
TT T OR(const T&x,const T&y){return x?x:y;};TT T AND(const T&x,const T&y){return x?y:x;} //Python style and/or
TTT void cmin(T&x,const T1&y){if(x>y)x=y;};TTT void cmax(T&x,const T1&y){if(x<y)x=y;} // Change value on comp: x=f(x,y)

//MATH
//MATH
constexpr auto sieve(){int m=1e6+1,q=0;bool o[m]={};array<int,78498>primes={};memset(o,1,sizeof(o));for(int p=2;p*p<m;p++)if(o[p])REPi(i,p*p,m,p)o[i]=false;REPi(p,2,m,1)if(o[p])primes[q++]=p;return primes;}
ull pow(ull x,ull y,ull p){ull res=1;x %= p;if(x==0)return 0;while(y>0){if(y&1)res=(res*x)%p;y>>=1;x=(x*x)%p;}return res;} // Modulo Expo
ull ncr(const ll&n,ll r){if(n<1||r<1||r>=n)return 1;ull k=1;cmin(r,n-r);for(ll i=1;i<=r;i++)k=(k*(n-i+1))/i;return k;}
bool isPrime(const ll&n){if(n<3||n%2==0)return n==2;REPs(3,sqrt(n)+1,2)if(n%i==0)return false;return true;}
SI primeSet(){SI primes;for(auto&c:sieve())primes.insert(c);return primes;}
ld frac(const ld&a){return a-floor(a);} //Fractional part function
TT T gcd(const T&a,const T&b){return b?__gcd(a,b):a;}
TT T lcm(const T&a,const T&b){return a*b/gcd(a,b);}

namespace Structures{
TT class SegTree{
private: 
    VF(T)a;T d;const function<T(T,T)> cf;int s;
    void build(const VF(T)& q,int l,int r,int p){if(l==r){a[p]=q[l];return;}this->build(q,l,(l+r)/2,2*p);this->build(q,(l+r)/2+1,r,2*p+1);a[p]=cf(a[2*p],a[2*p+1]);}
    T query(int ql,int qr,int l,int r,int p=1){if(ql<=l&&qr>=r)return a[p];if(ql>r||qr<l)return d;T a=this->query(ql,qr,l,(l+r)/2,2*p),b=this->query(ql,qr,(l+r)/2+1,r,2*p+1);return cf(a,b);}
    void update(int ql,int qr,int l,int r,int v,int p=1){if(ql<=l&&qr>=r){a[p]=v;return;}if(ql>r||qr<l)return;this->update(ql,qr,l,(l+r)/2,v,2*p);this->update(ql,qr,(l+r)/2+1,r,v,2*p+1);a[p]=cf(a[2*p],a[2*p+1]);}
public:
    SegTree(const VF(T)&q,int d=INT_MAX,function<T(T,T)>cf=[](T x,T y){return(x<y)?x:y;}):cf(cf),d(d),s(q.size()){a=VF(T)(s*4+1,d);this->build(q,0,q.size()-1,1);}
    T query(int a,int b){return this->query(a,b,0,s-1);}void update(int idx,int v){update(idx,idx,0,s-1,v);}
};
}

void solve();

signed main(){
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int t;cin>>t;while(t--)solve();
    return 0;
}

bool helper(int n, int k, VI &arr, SI &st, int q){
    if(!k) return 1;
    if(st.count(q))return 1;
    if(arr[q]>n) return 0;
    st.insert(q);
    if(arr[q]<=q) q-=arr[q];
    else q=n-(arr[q]-q);
    return helper(n, k-1, arr, st, q);
}

void solve(){
    int n, k, pass=1, q; cin>>n>>k;
    VI arr(n); cin>>arr; SI st;
    if(helper(n, k, arr, st, n-1)) YES();
    else NO();
}