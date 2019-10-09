/*
  后缀自动机
  var:  sam.sz          : 节点数
        sam.lst         : 当前串末字符的节点
        sam.len         : 节点长度
        sam.par         : 后缀链接
        sam.ch          : 转移
  func: new_node(l)     : 新建一个长度l的节点
        init()          : 初始化sam
        extend(c)       : 向末尾添加字符c
        print()         : debug
        substr()        : 统计不同子串数
  note: 广义sam只需在做下一个串前sam.lst = 0
 */

struct SAM
{
    int sz, lst;
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
            lst = 0; 
        }
    
    void extend(int c)
        {
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
                    rep(j, 0, 25) ch[clone][j] = ch[q][j];
                    par[clone] = par[q];

                    for(; p != -1 && ch[p][c] == q; p = par[p])
                        ch[p][c] = clone;
                    par[q] = par[cur] = clone;
                }
            }
            lst = cur;
        }
    void print()
        {
            rep(i, 0, sz-1)
            {
                printf("%d: len=%d, par=%d\n", i, len[i], par[i]);
                rep(c, 0, 25) if(ch[i][c])
                    printf("\t -%c-> %d\n", c+'a', ch[i][c]);
            }
        }

    ll substr()
        {
            ll ret = 0;
            rep(i, 1, sz-1) ret += len[i] - len[par[i]];
            return ret;
        }
} sam;
