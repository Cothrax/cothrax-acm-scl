/*
  无向图最小割 O(n^3) Stoer-Wagner
  func: Mincut(n): 最小割(顶点数)
 */
int vis[N];
int dist[N], node[N], g[N][N];
int Mincut(int n)
{
	fill(vis, vis+n+1, 0);
	int prev, maxj, res = INF;
	for (int i = 0; i < n; i++) node[i] = i;
	for (int vs = 1; n > 1; vs++)
	{
		int maxj = 1;
		for (int i = 1; i < n; i++)
		{ //初始化 到已选集合的距离
			dist[node[i]] = g[node[0]][node[i]];
			if (dist[node[i]] > dist[node[maxj]]) maxj = i;
		}
		
		prev = 0;
		vis[node[0]] = vs;
		for (int i = 1; i < n; i++)
		{
			if (i == n - 1)
			{ //只剩最后一个没加入集合的点，更新最小割
				res = min(res, dist[node[maxj]]);
				// 合并最后两个点的边
				// (v, prev) <- (v, prev) + (v, maxj)
				for (int k = 0; k < n; k++)
					g[node[k]][node[prev]] = (g[node[prev]][node[k]] += g[node[k]][node[maxj]]);
				// 缩点，删除maxj，把n-1挪到maxj这
				node[maxj] = node[--n];
			}
			vis[node[maxj]] = vs;
			prev = maxj;
			maxj = -1;
			for (int j = 1; j < n; j++)
				if (vis[node[j]] != vs)
				{ //将上次求的maxj加入集合，合并与它相邻的边到割集
					dist[node[j]] += g[node[prev]][node[j]];
					if (maxj == -1 || dist[node[maxj]] < dist[node[j]]) maxj = j;
				}
		}
	}
	return res;
}
