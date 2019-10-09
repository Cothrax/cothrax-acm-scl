/*
  lucas定理 求C(x, k)%p
  var:  fac[k]                  : k!%p
  func: extgcd(a, b, x, y)      : 扩展欧几里得
        inv(a, b)               : 求a的mod b下的逆元
        C(x, k)                 : C(x, k)%p
  
  x = sum { a_i * P^i }
  k = sum { b_i * P^i }
  C(x, k)%P = prod { C(a_i, b_i)%P }
 */

ll fac[N], p; 
void extgcd(ll a, ll b, ll &x, ll &y)
{
    if(!b) { x = 1; y = 0; return; }
    extgcd(b, a%b, y, x);
    y -= (a/b)*x;
}

ll inv(ll a, ll b)
{
    ll x, y; extgcd(a, b, x, y);
    return (x%b+b)%b;
}

inline ll __C(int x, int k)
{return (fac[x]*inv(fac[k])%p*inv(fac[x-k])%p+p)%p;}
ll C(ll x, ll k)
{
    ll ret = 1;
    for(; x; x /= p, k /= p)
    {
        ll a = x%p, b = k%p;
        if(a < b) return 0;
        ret = ret*__C(a, b)%p;
    }
    return ret;
}

int main()
{
    fac[0] = 1; rep(i, 1, n) fac[i] = (fac[i-1]*i)%p;
}
