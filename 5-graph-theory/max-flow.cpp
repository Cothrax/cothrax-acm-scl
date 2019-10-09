int q[N], d[N];
bool bfs(int s, int dest)
{
    fill(d, d + dest + 1, INF); d[s] = 0; q[0] = s;
    for(int h = 0, t = 1, u, v; h != t; h = (h+1)%N)
        for(int i = head[u = q[h]]; i; i = g[i].nxt)
            if(d[v = g[i].v] == INF && g[i].cap)
                d[v] = d[u] + 1, q[t++] = v, t %= N;
    return d[dest] != INF;
}
int dfs(int u, int t, int f)
{
    if(u == t) return f;
    int ret = 0;
    for(int i = head[u], v; i; i = g[i].nxt)
        if(g[i].cap && d[v = g[i].v] == d[u] + 1) //忘判g[i].cap
        {
            int tmp = dfs(v, t, min(f - ret, g[i].cap));
            g[i].cap -= tmp; g[i^1].cap += tmp; ret += tmp;
            if(!tmp) d[v] = INF; //勿忘
            if(ret == f) return ret;
        }
    return ret;
}
int mf(int s, int t)
{
    int ret = 0;
    while(bfs(s, t)) ret += dfs(s, t, INF);
    return ret;
}
