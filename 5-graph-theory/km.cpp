/*
  km (二分图最大权匹配) O(N^3)
  var:  g[N][N]             : g[u][v] = x_u和y_v间的边 !
        vis_x/vis_y[N]      : 访问标记
        lx/ly[N]            : 顶标 (lx[u]+ly[v]>=g[u][v])
        slack[N]            : slack[v] = min{lx[u]+ly[v]-g[u][v]}
        mat[N]              : Y集合中节点的匹配
  func: dfs(u)              : 增广(u) return 是否成功
        km()                : 最大权完备匹配
  note: 这里的g不是邻接矩阵(行标为x集合, 列标为y集合)
        不完备匹配可以通过补0边和空节点得到
        最小权匹配将不等式反向, slack换成max即可 ?
        稠密图下表现良好, 稀疏图的效率不如费用流
 */

bool vis_x[N], vis_y[N];
ll g[N][N], lx[N], ly[N], slack[N]; int mat[N];
bool dfs(int u)
{
    vis_x[u] = 1;
    rep(v, 1, n)
    {
        if(vis_y[v]) continue;
        ll tmp = lx[u]+ly[v]-g[u][v];
        if(tmp == 0)
        {
            vis_y[v] = 1;
            if(mat[v] == -1 || dfs(mat[v]))
            {  mat[v] = u; return true; }
        } else slack[v] = min(slack[v], tmp);
    }
    return false;
}

ll km()
{
    rep(i, 1, n) rep(j, 1, n) lx[i] = max(lx[i], g[i][j]);
    fill(ly+1, ly+n+1, 0); fill(mat+1, mat+n+1, -1);
    rep(u, 1, n)
    {
        fill(slack, slack+n+1, INF);
        for(;;)
        {
            fill(vis_x, vis_x+n+1, 0); fill(vis_y, vis_y+n+1, 0); 
            if(dfs(u)) break;
            ll delta = INF;
            rep(v, 1, n) if(!vis_y[v]) delta = min(delta, slack[v]);
            rep(i, 1, n) if(vis_x[i]) lx[i] -= delta;
            rep(i, 1, n)
                if(vis_y[i]) ly[i] += delta; else slack[i] += delta;
        }
    }
    ll ret = 0;
    rep(v, 1, n) ret += g[mat[v]][v];
    return ret;
}


