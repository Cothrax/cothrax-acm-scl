/*
  矩阵
  var:  n                   : 行数(列数)
  func: mul(a, b, p)        : a = a*b mod p
        mat_pow(a, b, p)    : a = a^b mod p
        gauss(a)            : 解方程a[n][n+1], 解为a[][n+1],
                                返回系数矩阵的det
  note: gauss需要判断无解的情况 (出现0除法)
        mul, mat_pow为ll, gauss为db
 */
const int N = 105;
namespace matrix
{
    int n;
    void mul(ll a[][N], ll b[][N], ll p)
    {
        ll c[N][N];
        rep(i, 1, n) rep(j, 1, n)
        {
            c[i][j] = 0;
            rep(l, 1, n) (c[i][j] += a[i][l]*b[l][j]%p) %=p;
        }
        rep(i, 1, n) rep(j, 1, n) a[i][j] = c[i][j];
    }
    void mat_pow(ll a[][N], ll b, ll p)
    {
        ll ret[N][N];
        rep(i, 1, n) ret[i][i] = 1;
        for(; b; b >>= 1, mul(a, a, p)) if(b&1) mul(ret, a, p);
        rep(i, 1, n) rep(j, 1, n) a[i][j] = ret[i][j];
    }

    db gauss(db a[][N])
    {
        db ret = 1;
        rep(i, 1, n)
        {
            int p = i;
            rep(j, i+1, n) if(a[p][i] < a[j][i]) p = j;
            if(p != i) swap(a[p], a[i]), ret *= -1;
            ret *= a[i][i];
            rep(j, i+1, n+1) a[i][j] /= a[i][i];
            rep(j, 1, n) if(j != i)
                rep(k, i+1, n+1) a[j][k] -= a[j][i]*a[i][k];
        }
        return ret;
    }
}
