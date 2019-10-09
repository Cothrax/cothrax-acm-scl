/*
  Link Cut Tree (例为splay维护异或和)
  var:  sub[N]                      : splay子树异或和
        tag[N]                      : splay翻转标记
        prev[N]                     : path parent
  func: upd, pushdn, rotate, splay  : splay底层操作
        modify(x, k)                : splay中把点x的值改为k
        walk(x, k)                  : print一棵splay
        print(n)                    : print整棵lct(节点数量)
        pred(rt), succ(rt)          : 查询一个splay根的前驱/后继
        
        expose(x)                   : 砍掉x下端的链
        splice(x)                   : 将x所在链与prev[x]所在链连接
        evert(x)                    : 将x置为真实树的根
        access(x)                   : 将x到真实树的根的链抽出
        find_rt(x)                  : return x所在真实树的根
        link(u, v)                  : 连接u, v, 如果连通则return
        cut(u, v)                   : 砍掉e(u, v), 如果不存在则return
        query(u, v)                 : 查询u到v的路径的sub
  note: 加点trick: 维护边权可以把边也看成点 etc.
        在需要用到子节点前, 务必pushdn
        修改节点信息后, 务必upd
*/

const int N = 3e5+10;
#define L(x) ch[x][0]
#define R(x) ch[x][1]
struct LCT
{
    int sz = 0, ch[N][2], val[N], par[N], prev[N]; 
    int sub[N] = {0}; bool tag[N];
    inline void upd(int x) { sub[x] = sub[L(x)]^sub[R(x)]^val[x]; }
    inline void pushdn(int x)
        {
            if(!tag[x]) return;
            swap(L(x), R(x)); tag[x] = 0;
            if(L(x)) tag[L(x)] ^= 1;
            if(R(x)) tag[R(x)] ^= 1;
        }
    void rotate(int x)
        {
            // pushdn(par[x]); pushdn(x);
            int y = par[x], z = par[y], l = L(y)!=x, r = 1-l;
            if(!z) swap(prev[x], prev[y]); else ch[z][L(z)!=y] = x;
            par[x] = z; par[y] = x; par[ch[x][r]] = y;
            ch[y][l] = ch[x][r]; ch[x][r] = y;
            upd(y); upd(x);
        }
    void splay(int x)
        {
            static int stk[N]; int top = 0, cur = x;
            for(; cur; cur = par[cur]) stk[++top] = cur;
            while(top) pushdn(stk[top--]);
            
            while(par[x])
            {
                int y = par[x], z = par[y];
                if(par[y]) rotate((L(y)==x) ^ (L(z)==y) ?x:y);
                rotate(x);
            }
        }
    void modify(int x, int k) { splay(x); val[x] = k; upd(x); }
    void walk(int x, int dep)
        {
            if(!x) return;
            pushdn(x);
            walk(L(x), dep+1);
            rep(i, 0, dep) cout << "   ";
            cout << x << '[' << val[x] << "] p=" << par[x] << endl;
            walk(R(x), dep+1);
        }
    void print(int n)
        {
            rep(i, 1, n)
                if(!par[i])
                {
                    printf(":%d prev=%d\n", i, prev[i]);
                    walk(i, 0);
                }
        }
    int pred(int rt)
        {
            pushdn(rt); int ret = L(rt);
            while(R(ret)) ret = R(ret);
            return ret;
        }
    int succ(int rt)
        {
            pushdn(rt); int ret = R(rt);
            while(L(ret)) ret = L(ret);
            return ret;
        }
    
    void expose(int x)
        {
            splay(x); pushdn(x); if(!R(x)) return;
            par[R(x)] = 0; prev[R(x)] = x; R(x) = 0; upd(x);
        }
    bool splice(int x)
        {
            splay(x); if(!prev[x]) return false;
            expose(prev[x]);
            R(prev[x]) = x; par[x] = prev[x]; prev[x] = 0; upd(par[x]);
            return true;
        } 
    void access(int x) { expose(x); while(splice(x)); }
    void evert(int x) { access(x); splay(x); tag[x] ^= 1; }
    int find_rt(int x)
        {
            access(x);
            do pushdn(x), x = L(x); while(L(x));
            splay(x); return x;
        }
    void link(int u, int v)
        {
            evert(u); if(find_rt(v) != u) prev[u] = v;
        }
    void cut(int u, int v)
        {
            evert(u); access(v); if(pred(v) != u) return;
            splay(v); pushdn(v); par[L(v)] = 0; L(v) = 0; upd(v);
        }
    int query(int u, int v) { evert(u); access(v); return sub[v]; }
} t;
