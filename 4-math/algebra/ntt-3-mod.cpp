/*
  三模数模数ntt
  var:  t[3]        : 三个不同模数的ntt
        f,g         : 原系数向量
        fg          : 卷积后的点值表达
        p           : deg上界
  func: NTT.calc(p, f[], g[], opt[])    : 单个ntt计算, 输出到opt
        crt(x[])                        : 求三个数的crt
 */

const __int128 Z[3] = {469762049, 998244353, 1004535809};
struct NTT
{
    ll Z, g, w[N], w_rev[N];
    NTT() {}
    void init(ll Z0, ll g0) { Z = Z0; g = g0; }
    void init_w(int n)
        {
            ll x = Pow((ll)3, (Z-1)/n, Z), y = Pow(x, Z-2, Z);
            w[0] = w_rev[0] = 1;
            rep(i, 1, n)
                (w[i] = w[i-1]*x) %=Z,
                (w_rev[i] = w_rev[i-1]*y) %=Z;
        }
    void ntt(int n, ll *buf, ll *w)
        {
            for(int i = 0, j = 0; i < n; i++)
            {
                if(i < j) swap(buf[i], buf[j]);
                for(int l = n>>1; (j^=l) < l; l >>= 1);
            }
            for(int i = 2; i <= n; i <<= 1)
            {
                int m = i>>1;
                for(int j = 0; j < n; j += i)
                    rep(k, 0, m-1)
                    {
                        ll tmp = w[n/i*k]*buf[j+m+k]%Z;
                        (buf[j+m+k] = (buf[j+k]-tmp)%Z+Z) %=Z;
                        (buf[j+k] += tmp) %=Z;
                    }
            }
        }
    void calc(int p, ll *f, ll *g, ll *opt)
        {
            static ll fy[N], gy[N];
            rep(i, 0, p-1) fy[i] = f[i], gy[i] = g[i];
            init_w(p); ntt(p, fy, w); ntt(p, gy, w);
            rep(i, 0, p-1) opt[i] = fy[i]*gy[i]%Z;
            ntt(p, opt, w_rev);
            
            ll r = Pow((ll)p, Z-2, Z);
            rep(i, 0, p-1) opt[i] = opt[i]*r%Z;
        }
} t[3];

__int128 crt(__int128 *x)
{
    __int128 m = Z[0]*Z[1]*Z[2];
    __int128 ans = 0;
    rep(i, 0, 2)
    {
        __int128 Mi = m/Z[i], r = Pow(Mi, Z[i]-2, Z[i]);
        (ans += Mi*r%m*x[i]%m) %=m;
    }
    return ans;
}

ll f[N], g[N], fg[3][N], ans[N]; __int128 z0;
int n, m, p;
int main()
{
    freopen("std.in", "r", stdin);
    freopen("std.out", "w", stdout);
    n = read(); m = read(); z0 = read();
    rep(i, 0, n) f[i] = read();
    rep(i, 0, m) g[i] = read();

    p = 1<<((ll)ceil(log2(max(n, m)))+1);
    rep(i, 0, 2)
    {
        t[i].init(Z[i], 3);
        t[i].calc(p, f, g, fg[i]);
        //disp(fg[i], 0, p-1);
    }

    __int128 tmp[3];
    rep(i, 0, n+m)
    {
        rep(j, 0, 2) tmp[j] = fg[j][i];
        printf("%lld ", (ll)(crt(tmp)%z0));
    }
}

