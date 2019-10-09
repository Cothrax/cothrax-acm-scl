/*
  环形polya: m种颜色给n个珠子的项链涂色
  burnside: 轨道数 * |G| = sum{ f(g) | any g in G }
  polya:    f(g) = m^c(g)
  环形: 涂色数 * n = sum{ phi(k) * m^(n/k), k|d }
  带翻转的话就是Dn, 翻转分奇偶讨论即可

  var:  p[sz], cnt[sz]              : n的质因数分解
        ans                         : 答案
  func: factor(n)                   : 质因分解n
        dfs(x, val, phi)            : dfs计算答案(位置, 值, phi值)
 */
const int N = 1e6+10; const ll Z = 1e9+7;
ll p[N], cnt[N], sz = 0;
void factor(ll n)
{
    sz = 0;
    for(ll i = 2; i*i <= n; i++)
        if(n%i == 0)
        {
            p[++sz] = i; cnt[sz] = 0;
            while(n%i == 0) cnt[sz]++, n /= i;
        }
    if(n != 1) p[++sz] = n, cnt[sz] = 1;
}

ll n, m, ans = 0;
void dfs(int x, ll val, ll phi)
{
    // cout << x << ": " << val << ", " << phi << endl; 
    if(x > sz)
    {
        ll y = n/val;
        ll tmp = Pow(m, y, Z);
        (ans += phi * tmp % Z) %= Z;
        // printf("phi[%d]=%d\n", val, phi);
        return;
    }
    dfs(x+1, val, phi);
    ll cur = p[x];
    rep(i, 1, cnt[x])
    {
        ll new_phi = phi * (p[x]-1) * cur / p[x];
        dfs(x+1, val * cur, new_phi);
        cur *= p[x];
    }
}

int main()
{
    freopen("std.in", "r", stdin);
    // freopen("std.out", "w", stdout);
    while(scanf("%lld%lld", &n, &m) != EOF)
    {
        factor(n);
        ans = 0; dfs(1, 1, 1);
        // cout << n << ", " << m << ":" << ans << endl;
        printf("%lld\n", ans * Pow(n, Z-2, Z) % Z);
    }
}

