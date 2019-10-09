/*
  普通莫队 O(N^(3/2)) (例为离线区间众数)
*/
namespace moq1
{
    int n, m, lst, b[N], bl[N], blo; P a[N];
    struct node { int x, y, i; } ask[N];
    bool comp(node a, node b)
    { return (bl[a.l]<bl[b.l])||(bl[a.l]==bl[b.l]&&a.r<b.r); }

    int ans[N], num[N], cnt[N], cur = 0;
    void inc(int x)
    {
        if(cur == num[x]) cur++;
        cnt[num[x]++]--; cnt[num[x]]++;
    }
    void dec(int x)
    {
        if(cur == num[x] && cnt[num[x]] == 1) cur--;
        cnt[num[x]--]--; cnt[num[x]]++;
    }

    void solv()
    {
        n = read(); m = read(); blo = sqrt(n)+1;
        for(int i = 1; i <= n; i++) bl[i] = (i-1)/blo; //分块编号
        for(int i = 1; i <= n; i++) fi(a[i]) = read(), se(a[i]) = i;
        for(int i = 1; i <= m; i++)
            ask[i].l = read(), ask[i].r = read(), ask[i].i = i;
        sort(ask + 1, ask + m + 1, comp);

        sort(a + 1, a + n + 1); lst = 0; //离散化
        for(int i = 1; i <= n; i++)
        {
            if(i == 1 || fi(a[i]) != fi(a[i-1])) lst++;
            b[se(a[i])] = lst;
        }
    
        int l = 1, r = 0; //two-pointer
        for(int i = 1; i <= m; i++)
        {
            while(l < ask[i].l) dec(b[l++]); //注意映射关系!
            while(r < ask[i].r) inc(b[++r]);
            while(l > ask[i].l) inc(b[--l]);
            while(r > ask[i].r) dec(b[r--]);
            ans[ask[i].i] = cur; //注意ask[i].i!
        }
        for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    }
}

/*
  带修莫队(例为统计区间不同元素个数) O(N^(5/3))
  var:  bl[N], blo          : 分块编号, 块数
        cnt[N], tot         : 计数变量
        p, q                : 查询数, 修改数
        col[N]              : 原序列
        idx[N], val[N]      : 修改信息, 第x个为将idx[x]改为val[x]
        ask[N]{l,r,tim,i}   : 查询信息
  func: inc(c)              : 增点
        dec(c)              : 删点
        modify(x, l, r)     : 执行第x次修改, 当前区间为[l, r]
        unmod(x, l, r)      : 撤销第x次修改, 当前区间为[l, r]
        solv()              : 接口
 */
namespace moq2
{
    const int N = 2e6+10;
    struct node {int l, r, tim, i; } ask[N];

    int bl[N], blo;
    bool comp(node a, node b)
    {
        return (bl[a.l]==bl[b.l]) ?
            (bl[a.r]==bl[b.r] ? a.tim<b.tim : a.r<b.r) : a.l<b.l;
    }

    int cnt[N], tot = 0;
    int lstv[N], idx[N], val[N], col[N], pre[N];
    void inc(int c) { cnt[c]++; if(cnt[c] == 1) tot++; }
    void dec(int c) { cnt[c]--; if(!cnt[c]) tot--; }
    inline void modify(int x, int l, int r)
    {
        col[idx[x]] = val[x];
        if(idx[x]<l || r<idx[x]) return; //修改点不在当前区间中
        dec(lstv[x]); inc(val[x]);
    }
    inline void unmod(int x, int l, int r)
    {
        col[idx[x]] = lstv[x];
        if(idx[x]<l || r<idx[x]) return;
        dec(val[x]); inc(lstv[x]);
    }

    int p, q, n, m, ans[N];
    void solv()
    {
        freopen("std.in", "r", stdin);
        // freopen("std.out", "w", stdout);
        read(n); read(m); blo = pow(n, 2.0/3);
        rep(i, 1, n) read(col[i]);
        rep(i, 1, n) bl[i] = i/blo;
        p = q = 0;
        rep(i, 1, m)
        {
            char c; scanf("%c", &c);
            if(c == 'Q')
            {
                read(ask[++p].l); read(ask[p].r);
                ask[p].i = p; ask[p].tim = q;
            }
            else
            {
                read(idx[++q]); read(val[q]); int x = idx[q];
                lstv[q] = pre[x] ? val[pre[x]] : col[x]; pre[x] = q;
            }
        }
        sort(ask+1, ask+p+1, comp);
        int l = 1, r = 0, cur = 0;
        rep(i, 1, p)
        {
            while(cur < ask[i].tim) modify(++cur, l, r);
            while(cur > ask[i].tim) unmod(cur--, l, r);
            while(l > ask[i].l) inc(col[--l]);
            while(r < ask[i].r) inc(col[++r]);
            while(l < ask[i].l) dec(col[l++]);
            while(r > ask[i].r) dec(col[r--]);
            ans[ask[i].i] = tot;
        }
        rep(i, 1, p) printf("%d\n", ans[i]);
    }
}

/*
  处理路径询问的树上莫队 (例为询问路径上不同元素个数)
  note: 基本思路:   找出u-v (lft[u] < lft[v]) 对应的询问区间[l, r]
                    使u-v上的点都出现1次, 其余点出现0次或2次
                    case1: 当lca(u, v) == u时, [lft[u], lft[v]]
                    case2: 当lca(u, v) != u时, [rgt[u], lft[v]] 外加lca(u, v)
        (注意序列长度为2*n)
  var:  N                       : 点数*2
        M                       : 询问数
        lft[N], rgt[N], seq[N]  : dfs 进出时间戳, 得到的序列(长度2*n)
        lca[N]                  : 第i个询问在case2下的lca
  func: inc(c)                  : 增点
        dec(c)                  : 删点
  bouns:处理子树询问? 普通dfs序即可 [dfn[u], dfn[u]+siz[u]-1] 
*/
namespace moq3
{
    const int N = 40010*2, M = 100010;
    // 图部分
    struct edge{int v, nxt;} g[N];
    int head[N], sz = 0;
    void add(int u, int v)
    {
        g[++sz].v = v; g[sz].nxt = head[u]; head[u] = sz;
    }

    int n, m, a[N], bl[N], blo, lgn; int lca[M], ans[M];
    int lft[N], rgt[N], seq[N], dep[N], par[N][20], tim = 0;
    void dfs(int u, int p)
    {
        lft[u] = ++tim; seq[tim] = u;
        par[u][0] = p; dep[u] = dep[p] + 1;
        for(int i = head[u], v; i; i = g[i].nxt)
            if((v = g[i].v) != p) dfs(v, u);
        rgt[u] = ++tim; seq[tim] = u;
    }
    int lca(int u, int v)
    {
        if(dep[u] < dep[v]) swap(u, v);
        for(int i = lgn; i >= 0; i--)
            if(dep[par[u][i]] >= dep[v]) u = par[u][i];
        if(u == v) return u;
        for(int i = lgn; i >= 0; i--)
            if(par[u][i] != par[v][i])
                u = par[u][i], v = par[v][i];
        return par[u][0];
    }

    // 莫队部分
    struct node { int l, r, i; } ask[M];
    bool comp(node a, node b)
    { return (bl[a.l] < bl[b.l]) || (bl[a.l] == bl[b.l] && a.r <= b.r); }

    int cnt[N], cur = 0, flg[N];
    void _inc(int x) { if(cnt[x]++ == 0) cur++; }
    void _dec(int x) { if(--cnt[x] == 0) cur--; }
    void inc(int k) { (flg[k]++ == 1) ?  _dec(a[k]) : _inc(a[k]); }
    void dec(int k) { (flg[k]-- == 1) ?  _dec(a[k]) : _inc(a[k]); }

    void solv()
    {
        read(n); read(m); lgn = log2(n)+1; blo = sqrt(n*2);
        for(int i = 1; i <= n*2; i++) bl[i] = i/blo;
        for(int i = 1; i <= n; i++) read(a[i]);
        for(int i = 1; i < n; i++)
        {
            int u = read(), v = read();
            add(u, v); add(v, u);
        }
        init(); dfs(1, 0);
        for(int i = 1; i <= lgn; i++)
            for(int j = 1; j <= n; j++)
                par[j][i] = par[par[j][i-1]][i-1];
        
        for(int i = 1; i <= m; i++)
        {
            int u = read(), v = read(), p = lca(u, v);
            ask[i].i = i; if(lft[u] > lft[v]) swap(u, v);
            if(u == v) ask[i].l = ask[i].r = lft[u];
            else if(u == p) ask[i].l = lft[u], ask[i].r = lft[v];
            else ask[i].l = rgt[u], ask[i].r = lft[v], lca[i] = p;
        }
        sort(ask + 1, ask + m + 1, comp);
        int l = 1, r = 0;
        for(int i = 1; i <= m; i++)
        {
            while(l > ask[i].l) inc(seq[--l]);
            while(r < ask[i].r) inc(seq[++r]);
            while(l < ask[i].l) dec(seq[l++]);
            while(r > ask[i].r) dec(seq[r--]);
            int j = ask[i].i;
            if(lca[j]) inc(lca[j]); //单独处理lca
            ans[j] = cur;
            if(lca[j]) dec(lca[j]);
        }
        for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    }
}
