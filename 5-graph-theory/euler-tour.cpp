/*
  无向图欧拉序 O(E)
  var:  deg[]           : 度数
        seq[top]        : 存放求出的euler序
  func: euler(n)        : 欧拉序(点数n) return是否存在
  note: 这里利用了head指针递增的trick, 保证每条边只被遍历一次
 */

const int N = 2e5+10;
struct edge{ int v, nxt; bool flg; } g[N*2];
int head[N], sz = 1;
void add(int u, int v)
{
    g[++sz].v = v; g[sz].flg = 1;
    g[sz].nxt = head[u]; head[u] = sz;
}

int deg[N];
int seq[N], top = 0;
void dfs(int u)
{
    // printf(" -> %d\n", u);
    while(head[u])
    {
        int i = head[u];
        head[u] =  g[i].nxt;
        if(g[i].flg)
        {
            // printf("%d", u);
            g[i].flg = g[i^1].flg = 0;
            dfs(g[i].v);
        }
    }
    seq[++top] = u;
} 

bool euler(int n)
{
    vector<int> sta;
    rep(i, 1, n) if(deg[i]%2) sta.pb(i);
    if(sta.size() == 2) dfs(sta[0]);
    else if(sta.size() == 0) dfs(1);
    else return 0;
    
    if(top != n) return 0; else return 1;
}
