/*
  点分治(统计长度=k的路径, 共m次询问)
  var:  siz[]           : 子树大小
        q[cnt]          : 每次分治的dist{u, rt}
        used[u]         : u是否被dfs计算过
  func: get_rt(u, p, min_sz, rt, sum)   : 计算重心(u, p, &, &, 树的总大小)
        get_dist(u, p, pre)             : 计算dist{u, rt}
        calc(u, ext, flg)               : 计算贡献
        dfs(u)                          : 点分治
  note: 1. 每次分治时重心也要计入答案
        2. 但计入答案时要使用ext
 */
int siz[N], q[N], cnt = 0; bool used[N];
int n, m, a[N], f[N];
void get_rt(int u, int p, int &min_sz, int &rt, int sum)
{
    int cur = 0;
    for(int i = head[u], v; i; i = g[i].nxt)
        if(!used[v = g[i].v] && v != p)
        {
            get_rt(v, u, min_sz, rt, sum);
            cur = max(cur, siz[v]);
        }
    cur = max(cur, sum - siz[u]);
    if(cur < min_sz) rt = u, min_sz = cur;
}

void get_sz(int u, int p)
{
    // printf("get_sz: %d\n", u);
    siz[u] = 1;
    for(int i = head[u], v; i; i = g[i].nxt)
        if(!used[v = g[i].v] && v != p)
        {
            get_sz(v, u);
            siz[u] += siz[v];
        }
}
void get_dist(int u, int p, int pre)
{
    for(int i = head[u], v; i; i = g[i].nxt)
        if((v = g[i].v) != p && !used[v])
        {
            q[++cnt] = pre + g[i].w;
            get_dist(v, u, q[cnt]);
        }
}
void calc(int u, int ext, int flg)
{
    q[cnt = 1] = ext; get_dist(u, 0, ext);
    sort(q + 1, q + cnt + 1);
    for(int i = 1; i <= m; i++) //原题要统计m个k
    {
        int ptr = 1;
        while(ptr < cnt && q[ptr] + q[cnt] < a[i]) ptr++;
        while(ptr < cnt && q[ptr] * 2 <= a[i])
        {
            int lb = lower_bound(q+ptr+1, q+cnt+1, a[i]-q[ptr]) - q,
                ub = upper_bound(q+ptr+1, q+cnt+1, a[i]-q[ptr]) - q;
            if(lb < ub) f[i] += (ub-lb)*flg;
            ptr++;
        }
    }
}
void dfs(int u)
{
    used[u] = 1; calc(u, 0, 1);
    get_sz(u, 0);
    for(int i = head[u], v; i; i = g[i].nxt)
        if(!used[v = g[i].v])
        {
            calc(v, g[i].w, -1);
            int min_sz = n+1, rt = 0;
            get_rt(v, u, min_sz, rt, siz[v]); dfs(rt);
        }
}

int main()
{
    int min_sz = n+1, rt = 0;
    get_sz(1, 0);
    get_rt(1, 0, min_sz, rt, n);
    dfs(rt);
}
