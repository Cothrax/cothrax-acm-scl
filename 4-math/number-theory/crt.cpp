/*
  中国剩余定理
  var:  求最小非负的x  x = a[i] (mod m[i]) 1<=i<=n
  func: extgcd(a, b, x, y)      : 扩展欧几里得
        inv(a, b)               : 求a的mod b下的逆元
        crt()                   : 普通crt (m[i]两两互素)
        extcrt()                : 扩展crt (无解返回-1)
 */

typedef __int128 big;
const int N = 1e5+10;
big a[N], m[N]; int n;

big extgcd(big a, big b, big &x, big &y)
{
    if(!b) { x = 1; y = 0; return a; }
    big d = extgcd(b, a%b, y, x);
    y -= (a/b)*x;
    return d;
}

big inv(big a, big b)
{
    big x, y; extgcd(a, b, x, y);
    return (x%b+b)%b;
}

big crt()
{
    big M = 1, ans = 0;
    rep(i, 1, n) M *= m[i];
    rep(i, 1, n) (ans += a[i]*(M/m[i])*inv(M/m[i], m[i])) %=M;
    return (ans+M)%M;
}

bool calc(int i)
{
    // x = a[i] + m[i]*y1 = a[i+1] - m[i+1]*y2
    //     m[i]*y1 + m[i+1]*y2 = a[i+1] - a[i];
    big y1, y2, d = extgcd(m[i], m[i+1], y1, y2);
    if((a[i+1]-a[i]) % d) return 0;
    big b0 = a[i] + (a[i+1]-a[i])/d*y1*m[i],
        a0 = m[i]/d*m[i+1];
    b0 = (b0%a0+a0)%a0;
    m[i+1] = a0; a[i+1] = b0;
    return 1;
}

big extcrt()
{
    rep(i, 1, n-1) if(!calc(i)) return -1;
    big x, y; extgcd(1, m[n], x, y);
    return (x*a[n]%m[n] + m[n])%m[n];
}

