/*
  fft 多项式卷积
  var:  w/w_rev[N]          : 单位根/单位根的逆
        n/m/tot             : deg(f)/deg(g)/补全到2^x
  func: bin_reverse(n, x[]) : 逆向二进制加法排序x[]
        init_w(n)           : init单位根
        fft(n, buf[], w[])  : fft(tot, 系数向量, 单位根)
  note: 注意多项式系数从0开始
        fft会更改buf的值, 多次卷积需要备份
        idft后的答案需要/tot
 */
typedef complex<db> cpx;
const int N = 3e6+10;
void bit_reverse(int n, cpx *x)
{
    for(int i = 0, j = 0; i < n; i++)
    {
        if(i<j) swap(x[i], x[j]);
        for(int l = n >> 1; (j ^= l) < l; l >>= 1);
    }
}
void fft(int n, cpx *buf, cpx *w)
{
    bit_reverse(n, buf);
    for(int i = 2; i <= n; i <<= 1)   
    {
        int m = i>>1;
        for(int j = 0; j < n; j += i)
            rep(k, 0, m-1)
            {
                cpx tmp = w[n/i*k]*buf[j+m+k];
                buf[j+m+k] = buf[j+k]-tmp; buf[j+k] += tmp;
            }
    }
}

cpx w[N], w_rev[N];
void init_w(int n)
{
    db pi = acos(-1);
    rep(k, 0, n-1)
    {
        w[k] = cpx(cos(2.0*pi*k/n), sin(2.0*pi*k/n));
        w_rev[k] = conj(w[k]);
    }
}

int n, m; cpx f[N], g[N];
int main()
{
    n = read(); m = read();
    rep(i, 0, n) { db x; scanf("%lf", &x); f[i].real(x); }
    rep(i, 0, m) { db x; scanf("%lf", &x); g[i].real(x); }
    int tot = 1<<(ll)ceil(log2(max(n, m))+1);

    init_w(tot);                    
    fft(tot, f, w); fft(tot, g, w); // dft
    rep(i, 0, tot-1) f[i] *= g[i];  // conj
    fft(tot, f, w_rev);             // idft
    rep(i, 0, n+m)
    {
        ll cur = round(f[i].real()/tot);
        printf("%lld ", cur);
    }
}
