struct ODT
{
    struct node 
    {
        int l, r; mutable ll v;
        node(int _l, int _r, ll _v): l(_l), r(_r), v(_v) {}
        inline bool operator<(const node &o) const { return l < o.l; }
    };
    set<node> odt;
    int n;
    void init(int _n, ll *w)
    {
        n = _n;
        odt.clear();
        
        int lst = 1;
        rep(i, 2, n) 
            if(w[i] != w[i-1]) 
            {
                odt.insert(node(lst, i-1, w[i-1]));
                lst = i;
            }
        odt.insert(node(lst, n, w[n]));
    }
    
    auto split(int x)
    {
        if(x > n) return odt.end();
        auto it = --odt.upper_bound(node(x, 0, 0));
        if(it->l == x) return it;
        int l = it->l, r = it->r; ll v = it->v;
        odt.erase(it);
        odt.insert(node(l, x-1, v));
        return odt.insert(node(x, r, v)).X;
    }
    void assign(int l, int r, ll v)
    {
        auto itr = split(r+1), itl = split(l);
        odt.erase(itl, itr);
        odt.insert(node(l, r, v));
    }
    void inc(int l, int r, ll k)
    {
        auto itr = split(r+1), itl = split(l);
        for(; itl != itr; ++itl) itl->v += k; 
    }
    ll kth(int l, int r, int k)
    {
        vector<pair<ll, int> > v;
        auto itr = split(r+1), itl = split(l);
        for(; itl != itr; ++itl) v.push_back(mkp(itl->v, itl->r-itl->l+1));
        sort(v.begin(), v.end());
        int pref = 0;
        foreach(j, v)
        {
            pref += j->Y;
            if(pref >= k) return j->X;
        }
    }
} t;
