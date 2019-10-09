#include<bits/stdc++.h>
#define rep(i, l, r) for(ll i = (l); i <= (r); i++)
#define per(i, r, l) for(ll i = (r); i >= (l); i--)
#define foreach(i, x) for(auto i = x.begin(); i != x.end(); i++)
#define forG(i) for(int i = head[u], v; i; i = g[i].nxt)
typedef long long ll;
using namespace std;
#define X first
#define Y second
#define mkp(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define INF (ll)0x3f3f3f3f
#define EPS 1e-8
template<class T> inline void read(T &ret)
{
    T x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = x*10+ch-'0'; ch = getchar();}
    ret = x*f;
}

template<class T> inline T lowbit(T x) {return x&(-x);}
template<class T> T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<class T> inline T Pow(T a, T b, T p)
{T ret=1;a%=p;for(;b;b>>=1,a=a*a%p)if(b&1)(ret*=a)%=p;return ret;}
#define disp0(A){foreach(i,A)cout<<A[i]<<" ";cout<endl;}
#define disp(A, l, r) {rep(_i,l,r)cout<<A[_i]<<" ";cout<<endl;}
#define disp2(A, l, r, b, e){                                       \
        rep(_i,l,r){rep(_j,b,e)cout<<A[_i][_j]<<"\t";cout<<endl;}   \
        cout<<endl;                                                 \
    }

