/*
    分块 (例为静态区间众数)
 */

#define I(x) min((x)*blo, n)
const int N = 10010, M = 410;
int n, m, a[N]; vector<int> seq; P b[N];
void disc()
{
    sort(seq.begin(), seq.end());
    seq.erase(unique(seq.begin(), seq.end()), seq.end());
    rep(i, 0, n-1) a[i] = lbound(seq.begin(), seq.end(), a[i])-seq.begin();
}

int T = 0, flg[N], cnt[N], max_c, cur;
void upd(int x)
{
    if(flg[x] != T) cnt[x] = 0, flg[x] = T;
    cnt[x]++;
    if(cnt[x]>max_c || (cnt[x]==max_c && x<cur))
        cur = x, max_c = cnt[x];
}

int bl[N], blo, sz, f[M][M], g[M][M];
void init()
{
    rep(i, 0, n-1) b[i] = mkp(a[i], i);
    sort(b, b+n);
    
    blo = ceil(sqrt(n)); 
    rep(i, 0, n-1) bl[i] = i/blo;
    rep(i, 0, bl[n-1])
    {
        T++; max_c = 0; cur = 0;
        rep(j, I(i), n-1)
        {
            upd(a[j]);
            if(j==n-1 || (j+1)%blo == 0)
                f[i][bl[j]] = cur, g[i][bl[j]] = max_c;
        }
    }
}

int stk[N], top = 0; bool vis[N];
int calc(int l, int r)
{
    rep(i, l, min(I(bl[l]+1)-1, r))
        if(!vis[a[i]]) vis[a[i]] = 1, stk[++top] = a[i];
    if(bl[l] != bl[r])
        rep(i, I(bl[r]), r)
            if(!vis[a[i]]) vis[a[i]] = 1, stk[++top] = a[i];
    int ret = f[bl[l]+1][bl[r]-1], cur_c = g[bl[l]+1][bl[r]-1];
    rep(i, 1, top)
    {
        int lb = lbound(b, b+n, mkp(a[i], l)) - b,
            ub = ubound(b, b+n, mkp(a[i], r)) - b,
            len = ub-lb;
        if(len>cur_c || (len==cur_c && a[i]<ret)) cur_c = len, ret = a[i];
    }
    return ret;
}

int main()
{
    freopen("std.in", "r", stdin);
    // freopen("std.out", "w", stdout);
    read(n); read(m);
    rep(i, 0, n-1) read(a[i]), seq.pb(a[i]);
    disc(); init();

    // disp2(f, 0, blo, 0, blo);
    // disp2(g, 0, blo, 0, blo);
    
    int ans = 0;
    rep(i, 1, m)
    {
        int l, r; read(l); read(r);
        // l = (l+ans-1)%n; r = (r+ans-1)%n; if(l>r) swap(l, r);
        l--; r--;
        printf("%d\n", ans = seq[calc(l, r)]);
    }
}
