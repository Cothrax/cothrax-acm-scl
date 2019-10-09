/*
  树链剖分 (例为维护路径点权和, 及最大值)
  var:  son[]                       : 重儿子
        top[]                       : 所在树链顶端节点
        dfn[], idx[]                : dfs序, idx[dfn[u]] = u
  func: dfs(u, p), dfs2(u, top)     : 树剖核心过程
        query(u, v, flg)            : flg==0求max, flg==1求sum
        lca(u, v)                   : 求lca
  bonus:维护边权? w[u] = w(par[u]->u), query时排除lca
        维护子树? 树剖本身也是dfs序
        query有顺序要求? 先求出lca(u, v), 分开做, 注意lca只能算一次
 */

int par[N], dep[N], siz[N], son[N], top[N], idx[N], dfn[N], w[N], tot=0;
void dfs(int u, int p)
{
    par[u] = p; dep[u] = dep[p] + 1; siz[u] = 1;
    int cur = 0, v;
    for(int i = head[u], v; i; i = g[i].nxt)
        if((v = g[i].v) != p)
        {
            dfs(v, u); siz[u] += siz[v];
            if(siz[v] > cur) cur = siz[v], son[u] = v;
        }
}
void dfs2(int u, int tp)
{
    dfn[u] = ++tot; idx[tot] = u; top[u] = tp;
    if(son[u]) dfs2(son[u], top[u]);
    for(int i = head[u], v; i; i = g[i].nxt)
        if((v = g[i].v) != par[u] && v != son[u]) dfs2(v, v);
}

//线段树
struct Tree
{
    int sum[N*4], max_w[N*4];
    void build(int i, int b, int e)
        {
            if(b == e) { sum[i] = max_w[i] = w[idx[b]]; return; }
            int mid = (b+e)>>1, lc = i<<1, rc = lc|1;
            build(lc, b, mid); build(rc, mid+1, e);
            sum[i] = sum[lc] + sum[rc];
            max_w[i] = max(max_w[lc], max_w[rc]);
        }
    int query_sum(int i, int b, int e, int l, int r)
        {
            if(e<l || r<b) return 0;
            if(l<=b && e<=r) return sum[i];
            int mid = (b+e)>>1, lc = i<<1, rc = lc|1;
            return query_sum(lc, b, mid, l, r) +
                query_sum(rc, mid+1, e, l, r);
        }
    int query_max(int i, int b, int e, int l, int r)
        {
            if(r<l || e<l || r<b) return -INF;
            if(l<=b && e<=r) return max_w[i];
            int mid = (b+e)>>1, lc = i<<1, rc = lc|1;
            return max(query_max(lc, b, mid, l, r),
                       query_max(rc, mid+1, e, l, r));
        }
    void upd(int i, int b, int e, int x, int k)
        {
            if(b == e) { sum[i] = max_w[i] = k; return; }
            int mid = (b+e)>>1, lc = i<<1, rc = lc|1;
            if(x<=mid) upd(lc, b, mid, x, k);
            else upd(rc, mid+1, e, x, k);
            sum[i] = sum[lc]+sum[rc];
            max_w[i] = max(max_w[lc], max_w[rc]);
        }
    void walk(int i, int b, int e, int dep)
        {
            int mid = (b+e)>>1, lc = i<<1, rc = lc|1;
            if(b!=e) walk(lc, b, mid, dep+1);
            for(int i = 0; i < dep; i++) printf("  ");
            printf("%d[%d,%d]%d;%d\n", i, b, e, sum[i], max_w[i]);
            if(b!=e) walk(rc, mid+1, e, dep+1);
        }
} t;

//查询, flg==1求sun, flg==0求max
int query(int u, int v, int flg)
{
    int p = top[u], q = top[v], ret = flg ? 0 : -INF;
    while(p != q)
    {
        if(dep[p] < dep[q]) swap(p, q), swap(u, v);
        if(flg) ret += t.query_sum(1, 1, tot, dfn[p], dfn[u]);
        else ret = max(ret, t.query_max(1, 1, tot, dfn[p], dfn[u]));
        u = par[p]; p = top[u];
    }
    if(dep[u] > dep[v]) swap(u, v);
    if(flg) ret += t.query_sum(1, 1, tot, dfn[u], dfn[v]);
    else ret = max(ret, t.query_max(1, 1, tot, dfn[u], dfn[v]));
    return ret;
}

int lca(int u, int v)
{
    int p = top[u], q = top[v];
    while(p != q)
    {
        if(dep[p]<dep[q]) swap(p, q), swap(u, v);
        u = par[p]; p = top[u];
    }
    return dep[u]<dep[v] ? u : v;
}

//若u->v有顺序要求则先求lca, 在将u->lca和lca->v分开做
int calc(int u, int v, int x)
{
    int p = lca(u, v);
    //more here
    //注意lca不可以处理两次, 在lca->v中dfn[lca]+1
}

int main()
{
    dfs(1, 0); dfs2(1, 1); //注意是1
    t.build(1, 1, tot);
}
