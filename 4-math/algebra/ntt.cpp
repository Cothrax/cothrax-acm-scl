/*
  快速数论变换 (% 2^k+1)
  var:  w/w_rev[N]          : 单位根/单位根的逆
        n/m/tot             : deg(f)/deg(g)/次数上界
  func: init_w(n)           : init单位根
        ntt(n, buf[], w[])  : ntt(tot, 系数向量, 单位根)
  note: 注意多项式系数从0开始
        ntt会更改buf的值, 多次卷积需要备份
        idnt后的答案乘逆元! 
 */

const int N = 2e6+10; const ll Z = 998244353;
ll w[N], w_rev[N];
void init_w(int n)
{
    ll x = Pow(3, (Z-1)/n, Z), y = Pow(x, Z-2, Z);
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

int n, m; ll f[N];
int main()
{
    freopen("std.in", "r", stdin);
    //freopen("std.out", "w", stdout);
    n = read(); m = read();
    rep(i, 1, m) f[read()] = 1;
    int tot = 1<<(ll)ceil(log2(5*n)+1); // 例为多项式次幂

    init_w(tot); ntt(tot, f, w);             // 正变换
    rep(i, 0, tot) f[i] = Pow(f[i], n/2, Z); // do something
    ntt(tot, f, w_rev);                      // 逆变换
    ll x = Pow(tot, Z-2, Z);
    rep(i, 0, tot) (f[i]*=x) %=Z;            // 除tot^-1
}
