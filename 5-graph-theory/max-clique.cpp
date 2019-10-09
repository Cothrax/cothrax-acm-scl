/*
  无向图最大团 (折半枚举)
  var:  n               : 顶点数
        g[u]            : 点u的相邻点的bitmask
        f[s]            : 子图s的最大团
        all, fir, sec   : all = 2^n-1, fir = 2^(n/2)-1, sec = all^fir
  func: clique()        : 返回最大团大小
  note: 枚举sec中的状态s0, calc(s0)计算包含s0的最大团数
 */

const int N = 1e5+10, M = 42, K = (ll)1<<20;
int n; ll g[N]; int f[K];
int dp(ll s)
{
    if(!s) return 0;
    if(f[s] != -1) return f[s];
    f[s] = 0; ll v = lowbit(s), idx = round(log2(v));
    return f[s] = max(dp(s^v), dp(g[idx]&s)+1);
}

ll fir, sec, all;
int calc(ll s0)
{
    ll sta = all, cnt = 0;
    for(ll s = s0; s; s -= lowbit(s))
    {
        ll v = lowbit(s), idx = round(log2(v));
        sta &= g[idx]|v; cnt++;
    }
    if((s0|sta) != sta) return 0;
    return dp(fir&sta) + cnt;
}

ll clique()
{
    int ans = 0, hlf = n/2;
    all = ((ll)1<<n)-1, fir = ((ll)1<<hlf)-1, sec = all^fir;
    fill(f, f + ((ll)1<<hlf), -1);
    for(ll i = sec; i; i = (i-1)&sec) ans = max(ans, calc(i));
    return ans;
}
