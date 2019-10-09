/*
  带内存回收的带修主席树
  var:  MAX                 最大允许内存
        mem[MAX]            管理内存的栈
        tot                 mem栈顶指针
  func: init()              初始化mem
        push(x)             回收一个节点
        pop()               return 一个新节点
        
        ins(&i, b, e, x, k  权值线段树 - x处单点插值
        query(i, b, e, l, r)            - [l, r]区间查询
        ask(a, b, c, d)     二维数点 bit中[a, b] 线段树中[c, d]
        modify(x, val, k)   单点修改, (x, val)位置+k
*/

const int N = 2e5+10, lgN = ceil(log2(N));
const int MAX = 32250007; // 手动测试最大值
int n, m;
struct Tree
{
    int rt[N];
    struct node { int l, r, w; } sgt[MAX];

    int mem[MAX], tot = 0;
    void init() { rep(i, 0, MAX-1) mem[i] = i; tot = MAX; }
    inline void push(int x) { mem[tot++] = x; }
    inline int pop() { return mem[--tot]; }
    
    void ins(int &i, int b, int e, int x, int k)
        {
            if(!i) i = pop(); sgt[i].w += k;
            if(b < e)
            {
                int mid = (b+e)>>1;
                if(x <= mid) ins(sgt[i].l, b, mid, x, k);
                else ins(sgt[i].r, mid+1, e, x, k);
            }
            if(!sgt[i].w)  { sgt[i] = {0, 0, 0}; push(i); i = 0; }
        }
    int query(int &i, int b, int e, int l, int r)
        {
            if(!i || e < l || r < b) return 0;
            if(l <= b && e <= r) return sgt[i].w;
            int mid = (b+e)>>1, lc = sgt[i].l, rc = sgt[i].r;
            return query(lc, b, mid, l, r) + query(rc, mid+1, e, l, r);
        }
    int ask(int a, int b, int c, int d)
        {
            int ret = 0;
            for(int i = b; i; i -= lowbit(i))
                ret += query(rt[i], 1, n, c, d);
            for(int i = a-1; i; i -= lowbit(i))
                ret -= query(rt[i], 1, n, c, d);
            return ret;
        }
    void modify(int x, int val, int k)
        {
            for(int i = x; i <= n; i += lowbit(i))
                ins(rt[i], 1, n, val, k);
        }
} t;

int main()
{
    t.init();
}
