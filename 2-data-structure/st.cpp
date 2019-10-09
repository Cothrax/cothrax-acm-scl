/*:
  st表rmq
  var:  st[i][j]        : [i, i+2^j-1] rmq
  func: init()          : 预处理O(NlogN)
        query(l, r)     : 查询rmq [l, r]
  note: 下标[0, n-1]亦可
 */
const int N = 1e6, lgN = 20;
struct ST
{
    int st[N][lgN];
    void init(int *w, int n)
        {
            int lgn = ceil(log2(n));
            rep(i, 1, n) st[i][0] = w[i]; 
            rep(j, 1, lgn) rep(i, 1, n)
            {
                st[i][j] = st[i][j-1]; int k = i+(1<<(j-1));
                if(k < n) st[i][j] = min(st[i][j], st[k][j-1]);
            }
        }
    ll query(int l, int r)
        {
            if(l > r) return INF;
            int len = r-l+1, t = lg2[len];
            return min(st[l][t], st[r-(1<<t)+1][t]);
        }
} rmq;
