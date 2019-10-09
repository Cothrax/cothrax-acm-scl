/*
  后缀数组
  var:  s[]                     : string
        rk[i]                   : rank, 保存s[i:]的排名
        sa[i]                   : 后缀数组, sa[rk[i]] = i
        ht[i]                   : ht[rk[i]] = LCP(s[i:], s[sa[rk[i]-1]:])
        st[][]                  : ht数组的st表
        lg2[x]                  : log2(x)
  func: init(n)                 : 初始化
        radix(str, a, b, n, m)  : 基数排序()
        Sa(str, n, m)           : 建后缀数组(串, 串长, 字符集大小)
        calc_ht(str, n)         : 计算height, 建st表
        query(l, r)             : lcp(s[i:], s[j:]) = query(rk[i], rk[j])
 */

const int N = 1e5+10;
int lg2[N]; //floor(log2(i))
struct suffix
{
    int rk[N], sa[N], ht[N], st[N][lgN];
    void init(int n)
        {
            fill(rk, rk + n + 1, 0);
            fill(sa, sa + n + 1, 0);
            fill(ht, ht + n + 1, 0);
        }
    void radix(int *str, int *a, int *b, int n, int m)
        {
            static int cnt[N];
            fill(cnt, cnt + m + 1, 0);
            rep(i, 0, n-1) cnt[str[a[i]]]++;
            rep(i, 1, m)  cnt[i] += cnt[i-1];
            per(i, n-1, 0) b[--cnt[str[a[i]]]] = a[i];
        }
    void Sa(int *str, int n, int m)
        {
            static int a[N], b[N];
            rep(i, 0, n-1) rk[i] = i;
            radix(str, rk, sa, n, m); rk[sa[0]] = 0;
            rep(i, 1, n-1)
                rk[sa[i]] = rk[sa[i-1]] + (str[sa[i]]!=str[sa[i-1]]);
            for(int i = 0; (1<<i) < n; i++)
            {
                rep(j, 0, n-1)
                {
                    a[j] = rk[j] + 1;
                    b[j] = (j+(1<<i)>=n) ? 0 : (rk[j+(1<<i)] + 1);
                    sa[j] = j;
                }
                //注意下面的字符集大小均为n
                radix(b, sa, rk, n, n); radix(a, rk, sa, n, n);
                rk[sa[0]] = 0;
                rep(j, 1, n-1) rk[sa[j]] = rk[sa[j-1]] +
                    (a[sa[j-1]]!=a[sa[j]] || b[sa[j-1]]!=b[sa[j]]);
                if(rk[sa[n-1]] == n-1) break;
            }
        }
    void calc_ht(int *str, int n)
        {
            int k = 0;
            rep(i, 0, n-1)
            {
                if(rk[i] == 0) k = 0;
                else
                {
                    if(k > 0) k--;
                    int j = sa[rk[i]-1];
                    while(i+k<n && j+k<n && str[i+k]==str[j+k]) k++;
                }
                ht[rk[i]] = k;
            }
            int lgn = ceil(log2(n));
            rep(i, 0, n-1) st[i][0] = ht[i];
            rep(j, 1, lgn) rep(i, 0, n-1)
            {
                st[i][j] = st[i][j-1]; int k = i+(1<<(j-1));
                if(k < n) st[i][j] = min(st[i][j], st[k][j-1]);
            }
        }
    int query(int l, int r)
        {
            if(l > r) swap(l, r);
            l++; int len = r-l+1, t = lg2[len];
            return min(st[l][t], st[r-(1<<t)+1][t]);
        }
} suf;

char s[N];
int main()
{
    for(int i = 0; (1<<i) < N; i++) lg2[1<<i] = i;
    for(int i = 1; i < N; i++) lg2[i] = max(lg2[i], lg2[i-1]);
    scanf("%s\n", s); int n = 0;
    for(int i = 0; s[i]; i++) str[n++] = s[i]-'0';
    suf.init(n);
    suf.Sa(str, n, 127);
    suf.clac_ht(str, n);
    //suf.query(suf.rk[i], suf.rk[j]);
}
