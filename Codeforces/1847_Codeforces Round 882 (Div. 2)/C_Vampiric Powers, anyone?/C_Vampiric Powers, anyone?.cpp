#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#pragma ide diagnostic ignored "modernize-use-emplace"
#pragma GCC optimize("Ofast,unroll-loops") 
#pragma GCC target("avx,avx2,fma")

#include<bits/stdc++.h>
using namespace std;

#define UNUSED [[maybe_unused]]
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define int ll
#define all(x) x.begin(), x.end()
UNUSED const ll inf=1e18;
UNUSED const int mod=998244353;
UNUSED const int mod2=1e9+7;

//Prefix: V - Vector, P - Pair
//Suffix: F - Create on type
//Types: 2 letter = pair, T: template, D: double, I: int, S: string

#define PTTF(T1,T2) pair<T1,T2>
#define PF(T) PTTF(T,T)
#define VF(T) vector<T>
#define VPF(T) VF(PF(T))
#define PTT PTTF(T,T2)
#define VTT VF(PTT)
#define VT VF(T)

typedef PF(ld) PDD;
typedef PF(ll) PII;
typedef PTTF(int,PII) PIII;
typedef PF(string) PSS;

typedef VF(ll) VI;
typedef VF(PII) VII;
typedef VF(ld) VD;
typedef VF(string) VS;
typedef VF(PSS) VSS;

#define RET return
#define YES() std::cout << "YES\n"
#define NO() std::cout << "NO\n"

//TEMPLATE DEFINES
#define TTT template<typename T,typename T2>
#define TT template<typename T>

//LOOP STUFF
#define REPs(k,n,s) for(int i=k; i<n; i+=s)
#define REPk(k, n) REPs(k,n,1)
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
TTT istream &operator>>(UNUSED istream &cin,PTT &a) { RET cin>>a.first>>a.second; }
TT istream &operator>>(UNUSED istream &cin, UNUSED VT &a) { FOR(c,a) cin>>c; RET cin; }
TTT ostream &operator<<(ostream &cout,const PTT &a) { RET cout<<a.first<<' '<<a.second; }
TTT ostream &operator<<(UNUSED ostream &cout,UNUSED const VTT &a) { FOR(c,a) cout<<c<<'\n'; RET cout; }
TT ostream &operator<<(ostream &cout,const VT &a) { int n=a.size(); if (!n) RET cout; cout<<a[0]; for (int i=1; i<n; i++) cout<<' '<<a[i]; RET cout; }
TT basic_string<T> operator*(const basic_string<T> &s,int m) { auto r=s; m*=s.size(); r.resize(m); for (int i=s.size(); i<m; i++) r[i]=r[i-s.size()]; RET r; }

TT UNUSED int len(T&x){RET x.size();}
TT UNUSED VPF(T) ZIP(T &a, T &b){ll n = min(a.size(), b.size()); VPF(T) v(n, {"",""}); REP(n){v[i].first=a[i]; v[i].second=b[i];} RET v; } //Python style ZIP
TT UNUSED T pop(VT &v){T tmp = v[v.size()-1]; v.pop_back(); RET tmp;} //Python style pop: returns value on pop
TT UNUSED T OR(T x,T y){return x?x:y;}; TT UNUSED T AND(T x,T y){return x?y:x;} //Python style and/or
TT UNUSED void cmin(T&x,T y){if(x>y)x=y;}; TT UNUSED void cmax(T&x,T y){if(x<y)x=y;} // Change value on comp: x=f(x,y)

//MATH
UNUSED ull ncr(ll n, ll r){if(n<1||r<1||r>=n) RET 1; ull k=1;cmin(r,n-r); for(ll i=1;i<=r;i++)k=(k*(n-i+1))/i;RET k;}
UNUSED bool isPrime(ll n){if(n<3||n%2==0)RET n==2;REPs(3,sqrt(n)+1,2)if(n%i==0)RET false;RET true;}
UNUSED ld frac(ld&a){RET a-floor(a);} //Fractional part function
TT UNUSED T gcd(T&a,T&b){RET b?__gcd(a,b):a;}
TT UNUSED T lcm(T&a,T&b){RET a*b/gcd(a,b);}

void solve();

signed main(){
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t; cin >> t; while(t--) solve(); RET 0;
}

class TrieNode {
public:
    TrieNode* child[2];
    TrieNode() {
        child[0] = child[1] = nullptr;
    }
};

void insert(TrieNode* root, int n) {
    TrieNode* cur = root;
    for (int i = 7; i >= 0; i--) {
        int bit = (n >> i) & 1;
        if (cur->child[bit] == nullptr)
            cur->child[bit] = new TrieNode();
        cur = cur->child[bit];
    }
}

int findMaxXOR(TrieNode* root, int n) {
    TrieNode* cur = root;
    int res = 0;
    for (int i = 7; i >= 0; i--) {
        int bit = (n >> i) & 1;
        int oppositeBit = 1 - bit;
        if (cur->child[oppositeBit] != nullptr) {
            res |= (1 << i);
            cur = cur->child[oppositeBit];
        } else {
            cur = cur->child[bit];
        }
    }
    return res;
}


void solve() {
    int n, res=0, tmp=0; cin >> n;
    VI arr(n); cin>>arr;
    // Subarry with longest XOR gives the answer owo
    // 1st case: 2^5 = 7
    // 2nd case: 1^2 = 3 
    // 3rd case: 8^4^2 = 14
    // As always the explanation for sample test cases is a red herring smh
    // This is gonna be awkward if I get it wrong
    // Welp here goes nothing
    // F, that didnt work, so heres a try with a trie. If this doesnt work then rip me.
    TrieNode* root = new TrieNode();
    insert(root, 0);
    for (int i = 0; i < n; i++) {
        tmp ^= arr[i];
        insert(root, tmp);
        int curMaxXOR = findMaxXOR(root, tmp);
        res = max(res, curMaxXOR);
    }

    cout << res << endl;
}