struct dsu
{
    int par[N], siz[N]; //siz[i]为i所在集合的大小
    void init(int n)
        {
            for(int i = 1; i <= n; i++) par[i] = i, siz[i] = 1;
        }
    int find(int u) { return par[u]==u ? u : par[u] = find(par[u]); }
    void join(int u, int v) //u -> v
        {
            u = find(u); v = find(v);
            if(u == v) return;
            par[u] = v; siz[v] += siz[u];
        }
    int getsz(int u) {return siz[find(u)];}
} s;
