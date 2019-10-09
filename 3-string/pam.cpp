/*
  回文自动机
  var:  ch[sz][CSet]    : 转移
        fail[sz]        : fail指针
        len[sz]         : 节点长度
        cnt[sz]         : 节点计数
        s[n]            : 原串
        lst             : 末尾节点
  func: new_node(l)     : 新建长为l的节点
        init()          : 初始化pam
        get_fail(x)     : 从fail链上找满足s[n-len[x]-1] == s[n]的节点
        insert(c)       : 向末尾插入字符c
        calc_cnt()      : 计算每个回文串出现次数
 */

const int N = 300010, CSet = 27;
struct PAM
{
    int ch[N][CSet], fail[N], len[N], cnt[N], s[N];
    int sz, n, lst;

    int new_node(int l)
        {
            fill(ch[sz], ch[sz]+CSet, 0);
            len[sz] = l; cnt[sz] = 0;
            return sz++;
        }
    void init()
        {
            sz = 0; new_node(0); new_node(-1); 
            fail[0] = 1; s[0] = -1;
            lst = n = 0;
        }
    int get_fail(int x, int pos)
        {
            while(s[pos-len[x]-1] != s[pos]) x = fail[x];
            return x;
        }
    void insert(int c)
        {
            s[++n] = c;
            int cur = get_fail(lst, n);
            if(!ch[cur][c])
            {
                int now = new_node(len[cur]+2);
                fail[now] = ch[get_fail(fail[cur], n)][c];
                ch[cur][c] = now;
            }
            cnt[lst = ch[cur][c]]++;
        }

    void print()
        {
            rep(i, 0, sz-1)
            {
                printf("%d len=%d, fail=%d\n", i, len[i], fail[i]);
                rep(j, 0, 25) if(ch[i][j])
                    printf("\t-%c-> %d\n", j+'a', ch[i][j]);
            }
        }

    void calc_cnt()
        {
            static int q[N], deg[N];
            fill(deg, deg+sz+1, 0);
            rep(i, 0, sz-1) deg[fail[i]]++;
            int h = 0, t = 0;
            rep(i, 0, sz-1) if(deg[i] == 0) q[t++] = i;
            
            for(; h != t; h++)
            {
                int u = q[h];
                cnt[fail[u]] += cnt[u];
                deg[fail[u]]--;
                if(deg[fail[u]] == 0) q[t++] = fail[u];
            }
        }
} pam;

char s[N];
int main()
{
    pam.init();
    for(int i = 0; s[i]; i++) pam.insert(s[i]);
    pam.calc_cnt();
}
