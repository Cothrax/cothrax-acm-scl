/*
  最小费用最大流
  var:  q[N], d[N], inq[N]      : spfa
        pre[i]                  : s->i的最短路上连向i的边
  func: spfa(int s, int dest)   : 找增广路, return 是否存在增广路
        mcmf(int s, int t)      : min_cost_max_flow(源点, 汇点)
  note: mcmf(s, t) t须为最大节点
 */

struct edge { int, v, w, nxt, cap; } g[N*2];
int sz = 1, head[N];
void __add(int u, int v, int cap, int w)
{
    g[++sz].nxt = head[u]; head[u] = sz;
    g[sz].w = w; g[sz].v = v; g[sz].cap = cap;
}
void add(int u, int v, int cap, int w)
{ __add(u, v, cap, w); __add(v, u, 0, -w); }

int q[N], d[N], pre[N]; bool inq[N];
bool spfa(int s, int dest)
{
    fill(d, d + dest + 1, INF);
    fill(pre, pre + dest + 1, 0);
    q[0] = s; d[s] = 0; inq[s] = 1;
    for(int h = 0, t = 1, u, v; h != t; h = (h+1)%N, inq[u] = 0)
        for(int i = head[u = q[h]]; i; i = g[i].nxt)
            if(g[i].cap && d[v = g[i].v] > d[u] + g[i].w)
            {
                d[v] = d[u] + g[i].w; pre[v] = i;
                if(!inq[v]) inq[v] = 1, q[t++] = v, t %= N;
            }
    return d[dest] != INF;
}
int mcmf(int s, int t)
{
    int ret = 0;
    while(spfa(s, t))
    {
        int tmp = INF, sum = 0;
        for(int i = pre[t]; i; i = pre[g[i^1].v])
            tmp = min(tmp, g[i].cap), sum += g[i].w;
        ret += tmp*sum;
        for(int i = pre[t]; i; i = pre[g[i^1].v])
            g[i].cap -= tmp, g[i^1].cap += tmp;
    }
    return ret;
}

