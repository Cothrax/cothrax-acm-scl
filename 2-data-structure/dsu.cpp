/*
  并查集
  写关系并查集时，注意n的大小
 */
struct dsu
{
    int par[N], siz[N]; //siz[i]为i所在集合的大小
    void init(int n)
        {
            for(int i = 1; i <= n; i++) par[i] = i, siz[i] = 1;
        }
    int find(int u) { return par[u]==u ? u : par[u] = find(par[u]); }
    void join(int u, int v) // v -> u
        {
            u = find(u); v = find(v);
            if(u == v) return;
            par[v] = u; siz[u] += siz[v];
        }
    int getsz(int u) {return siz[find(u)];}
} s;

/*
  可撤销并查集 O(logn)
  例为cf813F
  时间分治 + 可撤销并查集 每次操作增删一条边，判断是否为二分图
*/

const int N = 2e5+10;
struct DSU
{
	int par[N], rk[N];
	int stku[N], stkv[N], stkw[N], tot; // 历史记录栈
	void init(int n)
		{
			rep(i, 1, n) par[i] = i, rk[i] = 0;
			tot = 0;
		}
	int find(int u) { for(; u != par[u]; u = par[u]); return u; }
	bool join(int u, int v) // v -> u
		{
			u = find(u); v = find(v);
			if(u == v) return false;
			if(rk[v] > rk[u]) swap(u, v);
			stku[++tot] = u; stkv[tot] = v; par[v] = u;
			rk[u] += stkw[tot] = rk[u] == rk[v];
			return true;
		}
	void rollback(int lst_tot)	// 撤销
		{
			for(; tot != lst_tot; tot--)
			{
				// printf("roll back (%d, %d)\n", stku[tot], stkv[tot]);
				rk[stku[tot]] -= stkw[tot];
				par[stkv[tot]] = stkv[tot];
			}
		}
} dsu;

int n, m, q, uu[N], vv[N], st[N]; bool ans[N];
bool try_join(int u, int v)		// 关系并查集，尝试合并 (u, v)
{
	if(dsu.find(u) == dsu.find(v)) return false;
	dsu.join(u, v+n); dsu.join(u+n, v);
	return true;
}

struct Tree						// 线段树
{
	vector<int> v[N*4];
	void modify(int i, int b, int e, int l, int r, int k) // [l,r]时间内存在边k
		{
			// if(i == 1)
			// 	printf("%d(%d, %d) %d, %d\n", k, uu[k], vv[k], l, r);
			if(r < l || e < l || r < b) return;
			if(l <= b && e <= r)
			{
				v[i].push_back(k);
				return;
			}
			int mid = (b+e)>>1, lc = i<<1, rc = lc|1;
			modify(lc, b, mid, l, r, k);
			modify(rc, mid+1, e, l, r, k);
		}
	void walk(int i, int b, int e, bool res) // 分治计算结果，当前答案为res
		{
			int lst_tot = dsu.tot;
			if(res)
				for(auto x: v[i])
					if(!try_join(uu[x], vv[x])) { res = 0; break; }
			
			if(b == e)
			{
				ans[b] = res;
				dsu.rollback(lst_tot); // 不要忘了这里rollback
				return;
			}
			int mid = (b+e)>>1, lc = i<<1, rc = lc|1;
			walk(lc, b, mid, res);
			walk(rc, mid+1, e, res);
			dsu.rollback(lst_tot);
		}
} t;

map<pair<int, int>, int> mp;
int main()
{
	read(n); read(q);
	dsu.init(2*n);				// 注意大小
	// 将询问转换成："边k在[b, e] 的时间内存在" 的形式
	rep(i, 1, q)
	{
		int u, v; read(u); read(v);
		pair<int, int> cur = make_pair(u, v);
		if(mp[cur] == 0)
		{
			mp[cur] = ++m;
			uu[m] = u; vv[m] = v; st[m] = i;
		}
		else
		{
			t.modify(1, 1, q, st[mp[cur]], i-1, mp[cur]);
			mp[cur] = 0;
		}
	}
	for(auto x: mp)
		if(x.second)
			t.modify(1, 1, q, st[x.second], q, x.second);

	t.walk(1, 1, q, 1);
	rep(i, 1, q) printf(ans[i] ? "YES\n" : "NO\n");
}
