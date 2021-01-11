/*
  二分图最大匹配 O(nm)
  var:  mat[N]      : 匹配节点, 缺省值0
        flg[N]      : 访问标记
        vs          : version标记(用于检查flg)
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

/*
  Hopcroft O(\sqrt{n}m)
  例子顶点编号[0, n)
 */

#define CLR(x, y) memset(x, y, sizeof(x))
int n;
int mx[N],my[N],vis[N];
int dis;
int dx[N],dy[N];

bool searchp() {
	queue<int>q;
	dis=INF;
	CLR(dx,-1);
	CLR(dy,-1);
	for(int i=0;i<n;i++) {
		if(mx[i]==-1) {
			q.push(i);
			dx[i]=0;
		}
	}
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		if(dx[u]>dis) break;
		for(int i=head[u];i;i=g[i].nxt) {
			int v=g[i].v;
			if(dy[v]==-1) {
				dy[v]=dx[u]+1;
				if(my[v]==-1) dis=dy[v];
				else {
					dx[my[v]]=dy[v]+1;
					q.push(my[v]);
				}
			}
		}
	}
	return dis!=INF;
}

bool dfs(int u) {
	for(int i=head[u];i;i=g[i].nxt) {
		int v=g[i].v;
		if(vis[v]||(dy[v]!=dx[u]+1)) continue;
		vis[v]=1;
		if(my[v]!=-1&&dy[v]==dis) continue;
		if(my[v]==-1||dfs(my[v])) {
			my[v]=u;
			mx[u]=v;
			return true;
		}
	}
	return false;
}

int maxMatch() {
	int res = 0;
	CLR(mx,-1);
	CLR(my,-1);
	while(searchp()) {
		CLR(vis,0);
		for(int i=0;i<n; i++)
		{
			if(mx[i] == -1 && dfs(i))
				res++;
		}
	}
	return res;
}

