/*
  异或(F2)空间线性基
  var:  K               : 最大位数
        a[N]            : data
        b[i]            : 最高位i的基向量
  func: gauss(int n)    : 高斯消元(a[]的大小)
        intersect       : 线性基求交 (a交b->ans)
  note: https://blog.sengxian.com/algorithms/linear-basis
 */
const int N = 100010, K = 63;
ll a[N], b[K];
void gauss(int n)
{
    rep(i, 1, n) per(j, K-1, 0)
        if((a[i]>>j)&1)
        {
            if(b[j]) a[i] ^= b[j];
            else
            {
                b[j] = a[i];
                // 为得到各位无重复的基 O(N^3)
                per(k, j-1, 0) if(b[k] && (b[j]>>k)&1) b[j] ^= b[k];
                rep(k, j+1, K-1) if((b[k]>>j)&1) b[k] ^= b[j];
                break;
            }
        }
}

void intersect(uint *a, uint *b, uint *ans)
{
    fill(ans, ans+up, 0);
    uint c[K], d[K];
    rep(i, 0, up-1) c[i] = d[i] = b[i];
    rep(i, 0, up-1)
    {
        uint x = a[i];
        if(!x) continue;
        int j = i; uint T = 0;
        for(; j >= 0; j--)
            if((x>>j)&1)
            {
                if(c[j]) x ^= c[j], T ^= d[j];
                else break;
            }
        if(!x) ans[i] = T; else c[j] = x, d[j] = T;
    }
}
