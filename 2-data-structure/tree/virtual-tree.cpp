struct Graph
{
    struct edge{int v, w, nxt; } g[N*4];
    int head[N], sz;
    void add(int u, int v, int w)
        {
            g[++sz].v = v; g[sz].w = w;
            g[sz].nxt = head[u]; head[u] = sz;
        }
    void walk(int u, int p, int w, int dep) //debug用
        {
            for(int i = 1; i <= dep; i++) printf("  ");
            printf("(%d)%d\n", w, u);
            for(int i = head[u]; i; i = g[i].nxt)
                if(g[i].v != p) walk(g[i].v, u, g[i].w, dep+1);
        }
} T, V;
int dep[N], dfn[N], tim = 0, par[N][20], min_c[N][20], lgn;
void dfs(int u, int p) //dfs原树信息
{
    dep[u] = dep[p] + 1; dfn[u] = ++tim; par[u][0] = p; 
    for(int i = T.head[u], v; i; i = T.g[i].nxt)
        if((v = T.g[i].v) != p) dfs(v, u), min_c[v][0] = T.g[i].w;
}
int LCA(int u, int v) //原树lca
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
//根据lca计算dist
int dist(int u, int v) { return dep[u]+dep[v]-2*dep[LCA(u, v)];}
int get_min(int u, int p) //虚树边信息计算(例为边权最小值)
{
    int ret = INF;
    for(int i = lgn; i >= 0; i--)
        if(dep[par[u][i]] >= dep[p])
            ret = min(ret, min_c[u][i]), u = par[u][i];
    return ret;
}

int a[N], s[N], top = 0, vtx[N], tot = 0; //bool flg[N];
bool comp(int a, int b) { return dfn[a] < dfn[b]; }
void build()
{
    int k = read();
    for(int i = 1; i <= k; i++) flg[a[i] = read()] = 1;
    sort(a + 1, a + k + 1, comp);
    if(a[1] != 1) s[++top] = 1;
    for(int i = 1; i <= k; i++)
    {
        int cur = a[i], lca = 0/*, b = 1*/;
        while(top > 0)
        {
            lca = LCA(cur, s[top]);
            if(top > 1 && dep[lca] < dep[s[top-1]])
                V.add(s[top-1], s[top], get_min(s[top],s[top-1])),top--;
            else if(dep[lca] < dep[s[top]])
            {
                V.add(lca, s[top], get_min(s[top], lca)); top--; break;
            }
            else break;
        }
        if(lca != s[top]) s[++top] = lca;
        /*if(b)*/ s[++top] = cur;
    }
    while(top > 1)
        V.add(s[top-1], s[top], get_min(s[top], s[top-1])), top--;
}
void calc(int u, int p) //统计虚树中的点用于clear
{
    vtx[++tot] = u;
    for(int i = V.head[u], v; i; i = V.g[i].nxt)
        if((v = V.g[i].v) != p) calc(v, u);
}
int dp(int u, int p) //注意par[u][0]不是V内父节点
{
    //...
}

int main()
{
    for(int i = 0; i <= lgn; i++) //例为维护最小边权
        for(int j = 1; j <= n; j++) min_c[j][i] = INF;
    dfs(1, 0);
    for(int i = 1; i <= lgn; i++)
        for(int j = 1; j <= n; j++)
        {
            par[j][i] = par[par[j][i-1]][i-1];
            if(par[j][i]) min_c[j][i] = min(min_c[par[j][i-1]][i-1],
                                            min_c[j][i-1]);
        }
    int m = read();
    for(int i = 1; i <= m; i++)
    {
        build();
//      V.walk(1, 0, 0, 0);
        calc(1, 0);
        printf("%lld\n", dp(1, 0));
        for(int i = 1; i <= tot; i++) //一定是vtx[i]
            V.head[vtx[i]] /*= flg[vtx[i]]*/ = 0;
        top = tot = V.sz = 0;
    }
}

/*
  虚树小结
  1. 分清虚树和原树
     1) V or T? i or j?
     2) par[u][0] 是原树的par
  2. clear
     1) vtx记录节点要全 - build, dfs过程中的剪枝会影响vtx的记录
        i)  dfs: if(...)return inf -> 忽略子树节点
        ii) build: if(...) break -> 在dfs中记录不到但flg有标记
     2) i遍历vtx 用vtx[i]更新!!
 */
