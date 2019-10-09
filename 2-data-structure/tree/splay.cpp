/*
  维护集合的splay
  func: init()          : 初始化, 添加哨兵元素[-1, INF]
        pred(x, k)      : x=rt, return min{ y | y <= k}
        succ(x, k)      : x=rt, return max{ y | y >= k}
        insert(w)       : 插入w
        query(l, r)     : 查询[l, r]内数的个数
        del(w)          : 删除所有w
        walk(x, dep)    : debug
  rmk:  半成品, 由维护一簇集合的splay修改而成
 */

#define L(x) ch[x][0]
#define R(x) ch[x][1]
struct Splay
{
    int sz = 0, rt, ch[M][2], siz[M], val[M], par[M];
    int min_w[M] = {INF}, max_w[M] = {-INF};
    inline void upd(int x)
        {
            siz[x] = siz[L(x)] + siz[R(x)] + 1;
            min_w[x] = min(min(min_w[L(x)], min_w[R(x)]), val[x]);
            max_w[x] = max(max(max_w[L(x)], max_w[R(x)]), val[x]);
        }
    void init()
        {
            rt = ++sz; val[sz] = -1;
            R(rt) = ++sz; val[sz] = INF; par[sz] = rt;
            upd(sz); upd(rt);
        }
    
    void rotate(int x, int &k)
        {
            int y = par[x], z = par[y], l = L(y)!=x, r = 1-l;
            if(y == k) k = x; else ch[z][L(z)!=y] = x;
            par[x] = z; par[y] = x; par[ch[x][r]] = y;
            ch[y][l] = ch[x][r]; ch[x][r] = y;
            upd(y); upd(x);
        }
    void splay(int x, int &k)
        {
            static int stk[N]; int top = 0, cur = x;
            for(; cur; cur = par[cur]) stk[++top] = cur;
            while(top) upd(stk[top--]);
            
            while(x != k)
            {
                int y = par[x], z = par[y];
                if(y != k) rotate((L(y)==x) ^ (L(z)==y) ?x:y, k);
                rotate(x, k);
            }
        }
    
    int pred(int x, int k)
        {
            for(;;)
            {
                if(val[x] > k) x = L(x);
                else if(val[x] == k || min_w[R(x)] > k) return x;
                else x = R(x);
            }
        }
    int succ(int x, int k)
        {
            for(;;)
            {
                if(val[x] < k) x = R(x);
                else if(val[x] == k || max_w[L(x)] < k) return x;
                else x = L(x);
            }
        }
    
    void insert(int w)
        {n
            int l = pred(rt, w), r = succ(rt, w);
            splay(l, rt);
            splay(r, R(l));
            val[++sz] = w;
            L(r) = sz; par[sz] = r;
            upd(sz); upd(r); upd(l);
        }
    int query(int l, int r)
        {
            int dn = succ(rt, l), up = pred(rt, r);
            splay(dn, rt);          
            if(dn == up) return 1;
            if(val[dn] > val[up]) return 0;
            splay(up, R(dn));
            return siz[L(up)] + 2;
        }
    void del(int w)
        {
            int l = pred(rt, w-1), r = succ(rt, w+1);
            splay(l, rt[x]); splay(r, R(l));
            L(r) = 0; upd(r); upd(l);
        }
    void walk(int x, int dep)
        {
            if(!x) return;
            walk(L(x), dep+1);
            rep(i, 0, dep) cout << "   ";
            cout << x << '[' << val[x] << ']' << '(' << siz[x] << ") p=" << par[x] << endl;
            walk(R(x), dep+1);
        }
} t;

/*
  维护序列的splay
  func: build(l, r, p)      : 构建区间[l, r], 父节点为p
        find(x, rk)         : 返回排名rk的元素
        reverse(l, r)       : 翻转[l, r]
 */
#define L(x) ch[x][0]
#define R(x) ch[x][1]
struct Splay
{
    int sz = 0, rt, ch[N][2], par[N], siz[N]; bool tag[N];
    void upd(int x) { siz[x] = siz[L(x)] + siz[R(x)] + 1; }
    inline void pushdn(int x)
        {
            if(!tag[x]) return;
            swap(L(x), R(x)); tag[x] = 0;
            if(L(x)) tag[L(x)] ^= 1;
            if(R(x)) tag[R(x)] ^=1;
        }
    void rotate(int x, int &k)
        {
            pushdn(par[x]); pushdn(x);
            int y = par[x], z = par[y], l = L(y)!=x, r = 1-l;
            if(y == k) k = x; else ch[z][L(z)!=y] = x;
            par[x] = z; par[y] = x; par[ch[x][r]] = y;
            ch[y][l] = ch[x][r]; ch[x][r] = y;
            upd(y); upd(x);
        }
    void splay(int x, int &k)
        {
            static int stk[N]; int top = 0, cur = x;
            for(; cur != k; cur = par[cur]) stk[++top] = cur;
            while(top) pushdn(stk[top--]);

            while(x != k)
            {
                int y = par[x], z = par[y];
                if(y != k) rotate((L(y)==x) ^ (L(z)==y) ?x:y, k);
                rotate(x, k);
            }
        }
    int build(int l, int r, int p)
        {
            if(l > r) return 0;
            if(l == r) {par[l] = p; siz[l] = 1; return l; }
            int mid = (l+r)>>1;
            L(mid) = build(l, mid-1, mid);
            R(mid) = build(mid+1, r, mid);
            par[mid] = p; upd(mid); return mid;
        }

    int find(int x, int rk)
        {
            pushdn(x);
            if(siz[L(x)] >= rk) return find(L(x), rk);
            else if(siz[L(x)] + 1 == rk) return x;
            else return find(R(x), rk - siz[L(x)] - 1);
        }
    void reverse(int l, int r)
        {
            int u = find(rt, l-1), v = find(rt, r+1);
            splay(u, rt); splay(v, R(u)); tag[L(v)] ^= 1;
        }
    void print(int x, int tot)
        {
            if(!x) return;
            pushdn(x);
            print(L(x), tot);
            if(x != 1 && x != tot) printf("%d ", x-1);
            print(R(x), tot);
        }
} t;

int main()
{
    t.rt = t.build(1, n+2, 0);
}
