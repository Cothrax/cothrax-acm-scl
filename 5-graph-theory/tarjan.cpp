//强连通分量
int cc = 0, tim = 0, t = 0, scc[N], dfn[N], low[N], s[N], loc[N];
bool ins[N], vis[N];
void tarjan(int u)
{
    dfn[u] = low[u] = ++tim;
    ins[u] = vis[u] = 1; s[loc[u] = t++] = u;
    for(int i = head[u]; i; i = g[i].nxt)
    {
        int v = g[i].v;
        if(!vis[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if(ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        cc++;
        while(t != loc[u]) scc[s[--t]] = cc, ins[s[t]] = 0;
    }
}


//双连通分量
/*
关于割点
  1. 由于是无向图, 不需要ins的判断: 如果可达必定ins
     -> 若不需要标记分量则不用入栈
  2. rt需要单独判断
  3. *割点不可以出栈
  4. 缩点后是一颗黑白染色的树
关于桥
  1. 桥可以将图划分为不相交的连通块, 割点不可以
  2. 注意反向边的问题
 */
int n, m; int tim = 0, low[N], dfn[N];
//int stk[N], top = 0;
void tarjan(int u, int p)
{
    dfn[u] = low[u] = ++tim; //stk[++top] = u;
    int chd = 0; //特判rt(默认为1)
    for(int i = head[u], v; i; i = g[i].nxt)
        if((v = g[i].v) != p)
            if(!dfn[v])
            {
                tarjan(v, u); chd++; siz[u] += siz[v];
                low[u] = min(low[v], low[u]);
                if((u==1 && chd>1) || (u!=1 && low[v] >= dfn[u]))
                    solv(u); //u为割点, u不可以出栈
                if(low[v] > dfn[u])
                    solv(i); //i为桥, u不可出栈
            }
            else low[u] = min(dfn[v], low[u]);
    //如果只求边双连通分量, 同scc
    //if(low[u]==dfn[u]) solv(u);
}
