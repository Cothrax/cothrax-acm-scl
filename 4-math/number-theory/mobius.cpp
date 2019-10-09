/*
  mobius相关
  var:  mu[]                : mobius函数
        p[sz], flg[]        : 素数, 合数标记
  func: calc_mu(n)          : 线性筛mobius
        calc_val(n)         : 数论分块
        calc_pref(n)        : 杜教筛
 */

const int N = 50010;
ll mu[N], p[N], sz = 0; bool flg[N];
void calc_mu(int n)
{
    mu[1] = 1;
    rep(i, 2, n)
    {
        if(!flg[i]) p[++sz] = i, mu[i] = -1;
        rep(j, 1, sz)
        {
            if(p[j]*i > 5e4) break;
            flg[p[j]*i] = 1;
            if(i%p[j]) mu[i*p[j]] = mu[i]*mu[p[j]];
            else { mu[i*p[j]] = 0; break; }
        }
    }
}

/*
  calc_val(n) = sum { floor(n/i) * f(i) | 1 <= i <= n }
  F(x) 为 f(x)的前缀和
 */
ll calc_val(ll n)
{
    ll ans = 0;
    for(ll i = 1, j; i <= n; i = j + 1)
    {
        j = n/(n/i);
        ans += (n/i) * (F(j) - F(i-1));
    }
    return ans;
}

/*
  calc_pref(n) = sum { f(i) | 1<=i<=n } 即f的前缀和
  h = f*g, H为h的前缀和, G为g的前缀和

  up = N^(2/3)
  g1 = g(1)
 */
ll up, f[N], g1; map<ll, ll> mp;
int calc_pref(ll n) {
    if(n <= up) return pref_f[n];
    auto it = mp.find(n); if(it != mp.end()) return it->Y;
    int ans = H(n); 
    for (ll i = 2, j; i <= n; i = j + 1)
    {
        j = n/(n/i);
        ans -= (G(j) - G(i-1)) * calc_pref(n/i);
    }
    ans /= g1;
    return mp[n] =  ans;
}
