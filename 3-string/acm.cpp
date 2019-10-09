/*
  ac自动机 (例为统计在text出现次数最多的pattern串)
  var:  N                   : pattern数
        M                   : pattern长度
        NM = N*M            : trie节点数
        K                   : text长度
        acm.vs, flg[u][c]   : 访问标号, 边[u][c]的访问标记
  func: init()              : init, 更新vs
        ins(s, x)           : 向trie插入一个编号为x的pattern
        build()             : 建fail指针
        query(cnt, s)       : 查询text s, cnt为记录答案的数组
        walk(u, c, dep)     : debug
  note: fail树 -> fail指针构成的树
        trie图 -> ACm转移规则构成的图
        u后缀与fail[u]匹配, fail[u]上的标记需要拷贝到u上 (查询时回溯亦可)  
 */

const int N = 155, M = 75, K = 5+1E6, NM = N*M;
struct ACM
{
    int sz = 0, vs = 0, ch[NM][27], fail[NM], flg[NM][27];
    vector<int> tag[NM];
    void init() { sz = 0; vs++; }
    void ins(char *s, int x)
        {
            int u = 0;
            for(int i = 0; s[i]; i++)
            {
                int c = s[i] - 'a';
                if(flg[u][c] != vs)
                {
                    flg[u][c] = vs; ch[u][c] = ++sz;
                    fail[sz] = 0; tag[sz].clear();
                }
                u = ch[u][c];
            }
            tag[u].push_back(x);
        }
    int q[NM];
    void build()
        {
            for(int h = 0, t = 1, u; h != t; h++)
                rep(c, 0, 25)
                {
                    if(flg[u = q[h]][c] != vs) continue; // 忽略空节点
                    int v = ch[u][c];
                    if(!u) fail[v] = 0;
                    else
                    {
                        u = fail[u];
                        while(u && flg[u][c] != vs) u = fail[u];
                        int w = fail[v] = flg[u][c]==vs ? ch[u][c] : 0;
                        for(int i = 0; i < tag[w].size(); i++)
                            tag[v].push_back(tag[w][i]);
                    }
                    q[t++] = v;
                }
        }
    void query(int *cnt, char *s)
        {
            int u = 0;
            for(int i = 0; s[i]; i++)
            {
                int c = s[i] - 'a';
                if(flg[u][c] == vs) u = ch[u][c];
                else
                {
                    while(u && flg[u][c] != vs) u = fail[u];
                    u = flg[u][c]==vs ? ch[u][c] : 0;
                }
                for(int i = 0; i < tag[u].size(); i++)
                    cnt[tag[u][i]]++;
            }
        }
    void walk(int u, int c, int dep)
        {
            for(int i = 0; i < dep; i++) printf("  ");
            printf("%d(%d)(t=%d,f=%d)\n", c, u, tag[u].size(), fail[u]);
            for(int i = 0; i < 26; i++)
                if(flg[u][i] == vs) walk(ch[u][i], i, dep + 1);
        }
} acm;

int n, cnt[N]; char txt[K], pat[N][M];
int main()
{
    freopen("std.in", "r", stdin);
    while(1)
    {
        scanf("%d\n", &n); if(!n) break;
        acm.init();
        rep(i, 1, n) scanf("%s\n", pat[i]), acm.ins(pat[i], i);
        scanf("%s\n", txt);

        acm.build();
//      acm.walk(0, 0, 0);
        fill(cnt, cnt + n + 1, 0);
        acm.query(cnt, txt);

        //统计答案
        int ans = 0;
        rep(i, 1, n) ans = max(ans, cnt[i]);
        printf("%d\n", ans);
        rep(i, 1, n) if(cnt[i] == ans) printf("%s\n", pat[i]);
    }
}
