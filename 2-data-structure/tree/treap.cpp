/*
  带重复计数的treap
  var:  w[N]            : 随机值
        val[N]          : 元素值
        siz[N]          : 子树大小
        cnt[N]          : 重复值个数
        max_w/min_w[N]  : 子树最大/最小值
  func: upd(x)          : 维护x节点的信息
        rotate(x, l)    : 将ch[x][l]转到x的位置!
        insert(k)       : 插入k
        del(k)          : 删除一个k
        find(rk)        : return 排名rk的元素值
        rank(k)         : return k的排名
        pred/succ(k)    : return k的前驱/后继
 */

#define L(x) ch[x][0]
#define R(x) ch[x][1]
struct Treap
{
    int w[N], siz[N], cnt[N], ch[N][2], sz = 0, rt;
    int val[N], min_w[N] = {INF}, max_w[N] = {-INF};
    void upd(int x)
        {
            siz[x] = siz[L(x)] + siz[R(x)] + cnt[x];
            min_w[x] = min(min(min_w[L(x)], min_w[R(x)]), val[x]);
            max_w[x] = max(max(max_w[L(x)], max_w[R(x)]), val[x]);
        }
    void rotate(int &x, int l)
        {
            int r = 1-l, y = ch[x][l];
            ch[x][l] = ch[y][r]; ch[y][r] = x;
            upd(x); upd(y); x = y;
        }
    void __insert(int &x, int k)
        {
            if(!x) {val[x=++sz] = k; w[x] = rand(); cnt[x] = 1; upd(x);}
            else if(k == val[x]) {cnt[x]++; upd(x); }
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
                if(cnt[x] > 1) cnt[x]--;
                else if(L(x)*R(x) == 0) x = max(L(x), R(x));
                else
                {
                    int l = w[L(x)] < w[R(x)];
                    rotate(x, l); __del(ch[x][1-l], k);
                }
            }
            else __del(ch[x][k > val[x]], k);
            if(x) upd(x);
        }

    int __find(int x, int rk)
        {
            if(siz[L(x)] >= rk) return __find(L(x), rk);
            else if(siz[L(x)] + cnt[x] < rk)
                return __find(R(x), rk - siz[L(x)] - cnt[x]);
            else return val[x];
        }
    int __rank(int x, int k)
        {
            if(val[x] > k) return __rank(L(x), k);
            else if(val[x] == k) return siz[L(x)] + 1;
            else return siz[L(x)] + cnt[x] + __rank(R(x), k);
        }
    int __pred(int x, int k)
        {
            if(val[x] >= k) return __pred(L(x), k);
            else if(min_w[R(x)] >= k) return val[x];
            else return __pred(R(x), k);
        }
    int __succ(int x, int k)
        {
            if(val[x] <= k) return __succ(R(x), k);
            else if(max_w[L(x)] <= k) return val[x];
            else return __succ(L(x), k);
        }

    void insert(int k) { __insert(rt, k); }
    void del(int k) { __del(rt, k); }
    int find(int rk) { return __find(rt, rk); }
    int rank(int k) { return __rank(rt, k); }
    int pred(int k) { return __pred(rt, k); }
    int succ(int k) { return __succ(rt, k); }
} t;
