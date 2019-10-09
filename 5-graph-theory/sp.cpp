// dijkstra
bool used[N];
typedef pair<ll, int> Pli;
void dij(int s, ll *d)
{
    priority_queue<Pli, vector<Pli>, greater<Pli> > q;
    fill(used, used + n + 1, 0);
    fill(d, d + n + 1, INF);
    d[s] = 0; q.push(make_pair((ll)0, s));
    while(!q.empty())
    {
        int u = q.top().second; q.pop();
        if(used[u]) continue; used[u] = 1;
        for(int i = head[u], v; i; i = g[i].nxt)
            if(d[v = g[i].v] > d[u] + g[i].w)
            {
                d[v] = d[u] + g[i].w;
                q.push(make_pair(d[v], v));
            }
    }
}

// spfa
int q[N]; bool inq[N];
void spfa(int s, ll *d) 
{
    fill(inq, inq+n+2, false);
    fill(d, d+n+2, INF);
    d[s] = 0; inq[s] = true; q[0] = s;
    int u, v;
    for(int h = 0, t = 1; h!=t; inq[q[h]] = false, h = (h+1)%N)
        for(int i = head[u = q[h]]; i; i = g[i].nxt)
            if(d[v = g[i].v]>d[u]+g[i].w)
            {
                d[v] = d[u]+g[i].w;
                if(!inq[v]) q[t] = v, inq[v] = true, t = (t+1)%N; 
            }
}


// floyd
void floyd()
{
    //要初始化
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                f[i][j] = min(f[i][j], f[i][k]+f[k][j]);
}

//路径输出的floyd; g[i][j]为i->j的第一个节点
int f[N][N], g[N][N];
void floyd()
{  
    for(int k = 1; k <= n; k ++)
        for(int i = 1; i <= n; i ++)
            for(int j = 1, cur; j <= n; j ++)
                if(f[i][j] >= (cur = f[i][k] + f[k][j])) //字典序最小
                {
                    if(f[i][j] == cur && g[i][j] <= g[i][k]) continue;
                    f[i][j] = cur; g[i][j] = g[i][k];
                }
}

// floyd求最小环
int min_circuit()
{
    int ans = INF;
    rep(k, 1, n)
    {
        rep(i, 1, k-1) rep(j, i+1, k-1)
            ans = min(ans, f[i][j] + g[i][k] + g[k][j]);
        rep(i, 1, n) rep(j, 1, n)
            f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    }
    return ans;
}
