/*
  欧拉函数相关
  var:  phi[]           : 欧拉函数
        p[sz], flg[]    : 素数, 合数标记
  func: euler(n)        : 线性筛euler函数
 */

const int N = 1e7+10;
int phi[N], p[N], sz = 0; bool flg[N];
void euler(int n)
{
    phi[1] = 1;
    rep(i, 2, n)
    {
        if(!phi[i]) phi[i] = i-1, p[++sz] = i;
        for(int j = 1; i*p[j] <= n; j++)
            if(i%p[j]) phi[i*p[j]] = phi[i]*phi[p[j]];
            else { phi[i*p[j]] = phi[i]*p[j]; break; }
    }
}

/*
  euler定理: (a, m) = 1 => a^phi[m] = 1 (mod m)
  扩展euler: a^q = a^{ q mod phi[m] + phi[m] } (mod m)
 */
