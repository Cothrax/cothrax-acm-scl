/*
  二分图最大匹配
  var:  mat[N]      : 匹配节点, 缺省值0
        flg[N]      : 访问标记
        vs          :  version标记(用于检查flg)
  func: dfs(u)      : 增广(u)
        hungary()   : return 最大匹配数
  note: 其实mat只需要记录一边即可
        注意mat会和matrix变量冲突

  rmk:  二分图
        1) 最大匹配数 = 最小点覆盖
        2) 最少边覆盖 = 点数-最大匹配数 = 最大独立集
        DAG
        1) 最少不相交路径覆盖: V拆成(Vx, Vy), e(u,v)变成Uy->Vx
           = 原图点数 - 最大匹配
        2) 最小可相交: 先floyd后1)
        3) 最大独立集 = 最少不相交路径覆盖 (dilworth)
 */

int mat[N], flg[N], vs = 1;
bool dfs(int u)
{
    for(int i = head[u], v; i; i = g[i].nxt)
        if(flg[v = g[i].v] != vs)
        {
            flg[v] = vs;
            if(!mat[v] || dfs(mat[v]))
            {
                mat[u] = v; mat[v] = u;
                return true;
            }
        }
    return false;
}
int hungary()
{
    int cnt = 0;
    rep(i, 1, n) { vs++; if(dfs(i)) cnt++;}
    return cnt;
}

