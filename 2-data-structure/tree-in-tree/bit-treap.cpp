/*
  bit套treap 二维数点
  func: __low(x, k)                 : 统计<=k的数的个数
        add(x, k)                   : 插入值k
        del(x, k)                   : 删除值k
        ask(l, r, p, q)             : 二维数点 bit中[l, r], treap中[p, q]
 */

const int N = 2e5+10, M = N*3*20;
#define L(x) ch[x][0]
#define R(x) ch[x][1]
int n;
struct Treap
{
    int w[M], siz[M], ch[M][2], sz = 0, val[M];
    inline void upd(int x) {  siz[x] = siz[L(x)] + siz[R(x)] + 1; }
    void rotate(int &x, int l)
        {
            int r = 1-l, y = ch[x][l];
            ch[x][l] = ch[y][r]; ch[y][r] = x;
            upd(x); upd(y); x = y;
        }
    void __insert(int &x, int k)
        {
            if(!x) {val[x=++sz] = k; w[x] = rand(); upd(x); }
            else
            {
                int l = k > val[x];
                __insert(ch[x][l], k); upd(x);
                if(w[ch[x][l]] > w[x]) rotate(x, l);
            }
        }
    void __del(int &x, int k)
        {
            if(!x) return;
            else if(k == val[x])
            {
                if(L(x)*R(x) == 0) x = max(L(x), R(x));
                else
                {
                    int l = w[L(x)] < w[R(x)];
                    rotate(x, l); __del(ch[x][1-l], k);
                }
            }
            else __del(ch[x][k > val[x]], k);
            if(x) upd(x);
        }
    int __low(int x, int k)
        {
            int ret = 0;
            for(; x;)
            {
                if(val[x] > k) x = L(x);
                else
                {
                    ret += siz[L(x)] + 1;
                    if(val[x] == k) break;
                    x = R(x);
                }
            }
            return ret;
        }

    int rt[N];
    void add(int x, int k)
        { for(; x <= n; x += lowbit(x)) __insert(rt[x], k); }
    void del(int x, int k)
        { for(; x <= n; x += lowbit(x)) __del(rt[x], k); }
    int ask(int l, int r, int p, int q)
        {
            int ret = 0;
            for(int i = r; i; i -= lowbit(i))
                ret += __low(rt[i], q) - __low(rt[i], p-1);
            for(int i = l-1; i; i -= lowbit(i))
                ret -= __low(rt[i], q) - __low(rt[i], p-1);
            return ret;
        }
} t;
