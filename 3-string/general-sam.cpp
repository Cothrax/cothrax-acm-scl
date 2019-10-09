/*
  广义sam (trie上建sam)
  注意节点数量
*/

const int N = 100010, CSet = 10;
struct SAM
{
    int sz;
    int len[N*2], par[N*2], ch[N*2][CSet];
    int new_node(int l)
        {
            fill(ch[sz], ch[sz]+CSet, 0);
            len[sz] = l;
            return sz++;
        }
    void init()
        {
            sz = 0; new_node(0);
            par[0] = -1;
            // lst = 0; 
        }

    void clone_node(int p, int c, int clone)
        {
            int q = ch[p][c];
            rep(j, 0, 25) ch[clone][j] = ch[q][j];
            par[clone] = par[q];
            for(; p != -1 && ch[p][c] == q; p = par[p]) ch[p][c] = clone;
            par[q] = clone;
        }
    
    int extend(int c, int lst)
        {
            if(ch[lst][c])
            {
                int q = ch[lst][c];
                if(len[lst] + 1 == len[q]) lst = q;
                else
                {
                    int clone = new_node(len[lst]+1);
                    clone_node(lst, c, clone);
                    lst = clone;
                }
                return lst;
            }
            
            int cur = new_node(len[lst] + 1);
            int p = lst;
            
            for(; p != -1 && !ch[p][c]; p = par[p]) ch[p][c] = cur;
            if(p == -1) par[cur] = 0;
            else
            {
                int q = ch[p][c];
                if(len[p] + 1 == len[q]) par[cur] = q;
                else
                {
                    int clone = new_node(len[p] + 1);
                    clone_node(p, c, clone);
                    par[cur] = clone;
                }
            }
            lst = cur;
            return lst;
        }
    void print()
        {
            rep(i, 0, sz-1)
            {
                printf("%d: len=%d, par=%d\n", (int)i, len[i], par[i]);
                rep(c, 0, 25) if(ch[i][c])
                    printf("\t -%d-> %d\n", (int)c, ch[i][c]);
            }
        }
    ll calc()
        {
            ll ret = 0;
            rep(i, 1, sz-1) ret += len[i] - len[par[i]];
            return ret;
        }

} sam;



struct Trie
{
    int ch[NM][CSet], sz, cset;
    void init(int _cset)
        {
            cset = _cset;
            sz = 0;
        }
    int insert(int pos, int c)
        {
            if(!ch[pos][c]) ch[pos][c] = ++sz;
            return ch[pos][c];
        }
    void dfs(int u, int cur)
        {
            rep(c, 0, cset-1)
                if(ch[u][c])
                {
                    int nxt = sam.extend(c, cur);
                    dfs(ch[u][c], nxt);
                }
        }
} t;

int main()
{
    sam.init();
    t.dfs(0, 0);
    printf("%lld\n", sam.calc());
}

