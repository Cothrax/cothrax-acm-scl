/*
  求满足x^k=a (mod p)的所有x, 不存在输出-1
  (sgu 261) k * ind(x) = ind(a) (mod phi(p))
            求ind(x)即可
  var:  p, k, a                 : 参数
        fac[N], sz              : p的因子, 栈顶指针
  func: extgcd(a, b, &x, &y)    : extgcd
        get_rt()                : 求p的原根g
        bsgs(g)                 : 求满足g^y=a (mod p)的y (求ind(a))
        solv(p, k, a)           : 接口
 */

namespace disc_log
{
    ll extgcd(ll a, ll b, ll &x, ll &y)
    {
        if(!b) { x = 1; y = 0; return a; }
        ll d = extgcd(b, a%b, y, x);
        y -= (a/b)*x;
        return d;
    }

    ll p, k, a, fac[N], sz = 0;
    ll get_rt()
    {
        ll n = p-1;
        for(int i = 2; i*i <= n; i++)
            if(n%i == 0)
            {
                fac[++sz] = i;
                while(n%i == 0) n/=i;
            }
        if(n != 1) fac[++sz] = n;
        n = p-1;
        rep(i, 1, n)
        {
            bool flg = 0;
            rep(j, 1, sz) if(Pow(i, n/fac[j], p) == 1) { flg = 1; break; }
            if(!flg) return i;
        }
    }
    
    map<ll, ll> hs;
    ll bsgs(ll g)
    {
        ll q = ceil(sqrt(p)), cur = 1;
        rep(i, 0, q-1) hs.insert(mkp(a*cur%p, i)), (cur*=g)%=p;
        ll tmp = Pow(g, q, p); cur = 1;
        rep(i, 0, q)
        {
            map<ll, ll>::iterator it = hs.find(cur);
            if(it != hs.end()) return q*i-(*it).Y;
            (cur*=tmp)%=p;
        }
        printf("-1"); exit(0);
    }
    
    void solv(ll k0, ll a0, ll p0)
    {
        a = a0; k = k0; p = p0; ll g = get_rt();

        ll t = bsgs(g);
        ll phi = p-1, x0, y0, d = extgcd(k, phi, x0, y0);
        if(t%d) { printf("-1"); return; }
        
        ll step = phi/d;
        x0 = x0*t/d%step;
        if(x0 < 0) x0 += step;
        printf("%lld", Pow(g, x0, p));
    }
}
