/*
  树状数组(例为前缀和)
  note: 常数优化可以考虑把<N换成<=n
 */

struct BIT
{
    ll bit[N];
    void add(int x, ll k)
        {
            if(!x) return;
            for(; x < N; x += lowbit(x)) bit[x] += k;
        }
    ll ask(int x)
        {
            ll ret = 0;
            for(; x; x -= lowbit(x)) ret += bit[x];
            return ret;
        }
} t;
