const int N = 2e5+10, lgN = 20;
struct edge { int v, nxt; } g[N*2];
int head[N], sz = 0, w[N], loc[N];
void add(int u, int v) { g[++sz] = {v, head[u]}; head[u] = sz; }

int n, lgn;
namespace binary
{
    int par[N][lgN], dep[N];
    void dfs(int u, int p)
    {
        dep[u] = dep[p] + 1; par[u][0] = p;
        for(int i = head[u], v; i; i = g[i].nxt)
            if((v = g[i].v) != p) dfs(v, u);
    }
    void init()
    {
        dfs(1, 0);
        lgn = ceil(log2(n));
        rep(i, 1, lgn) rep(j, 1, n) par[j][i] = par[par[j][i-1]][i-1];
    }
    
    int lca(int u, int v)
    {
        if(dep[u] < dep[v]) swap(u, v);
        per(i, lgn, 0) if(dep[par[u][i]] >= dep[v]) u = par[u][i];
        if(u == v) return u;
        per(i, lgn, 0)
            if(par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
        return par[u][0];
    }
}

namespace st
{
    int lg2[2*N], st[2*N][20], dep[N], dfn[N], ord[2*N], tot = 0;
    void dfs(int u, int p)
    {
        dep[u] = dep[p] + 1; ord[++tot] = u; dfn[u] = tot;
        for(int i = head[u], v; i; i = g[i].nxt)
            if((v = g[i].v) != p) dfs(v, u), ord[++tot] = u;
    }
    int Min(int a, int b) { return dep[a]<dep[b] ? a : b; }
    void init()
    {
        lgn = ceil(log2(n));
        for(int i = 0; (1<<i) <= n; i++) lg2[1<<i] = i;
        rep(i, 1, n) lg2[i] = max(lg2[i], lg2[i-1]);
        rep(i, 1, n) st[i][0] = ord[i];
        rep(j, 1, lgn) rep(i, 1, n)
        {
            st[i][j] = st[i][j-1]; int k = i+(1<<(j-1));
            if(k < n) st[i][j] = Min(st[i][j], st[k][j-1]);
        }
    }

    int lca(int u, int v)
    {
        int l = dfn[u], r = dfn[v]; if(l > r) swap(l, r);
        int len = r-l+1, t = lg2[len];
        return Min(st[l][t], st[r-(1<<t)+1][t]);
    }
    
    bool ischd(int x, int p) { return lca(x, p) == p; }
    bool onpath(int l, int x, int r)
    {
        int p = lca(l, r);
        if(p != l && p != r) return onpath(l, x, p) || onpath(p, x, r);
        if(dep[l] < dep[r]) swap(l, r);
        return ischd(l, x) && ischd(x, r);
    }
}
