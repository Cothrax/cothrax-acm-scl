/*
  三维偏序 - cdq分治 O(N(logN)^2)
  例为luogu p3157动态逆序对
  note: 第一维t 排序
        第二维pos 归并
        第三维val 用两个bit维护
  func: cdq(l, r)
 */

const int N = 100010;
struct node { int t, pos, val; } a[N], tmp[N];
bool comp(node x, node y) { return x.t < y.t; }
int n, m; ll ans[N];

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
} low, high;

void cdq(int l, int r)
{
    if(l == r) return;
    int mid = (l+r)>>1, p = l, q = mid+1;
    cdq(l, mid); cdq(mid+1, r);
    rep(i, mid+1, r) low.add(a[i].val, 1);
    rep(i, l, r)
        if(p>mid || (q<=r && a[q].pos<a[p].pos))
        {
            tmp[i] = a[q];
            low.add(a[q].val, -1); high.add(a[q++].val, 1);
        }
        else
        {
            tmp[i] = a[p];
            ll cur = low.ask(a[p].val)+high.ask(n+1)-high.ask(a[p].val);
            // printf("[%d, %d] p=%d, q=%d cur=%d\n", l, r, p, q, cur);
            ans[0] += cur; ans[a[p++].t] -= cur;
        }
    rep(i, mid+1,r) high.add(a[i].val, -1);
    rep(i, l, r) a[i] = tmp[i];
}

int main()
{
    freopen("std.in", "r", stdin);
    freopen("std.out", "w", stdout);
    read(n); read(m);
    rep(i, 1, n) a[i].val = i;
    rep(i, 1, n) { int x; read(x); a[x].pos = i; }
    rep(i, 1, m) { int x; read(x); a[x].t = i; }
    rep(i, 1, n) if(!a[i].t) a[i].t = n+1;
    sort(a+1, a+n+1, comp);
    cdq(1, n);
    rep(i, 1, m) ans[i] += ans[i-1];
    rep(i, 0, m-1) printf("%lld\n", ans[i]);
}
