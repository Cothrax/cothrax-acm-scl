/*
  Kirchhoff's theorem
  生成树个数 = 拉普拉斯矩阵L的|V|-1阶主子式的行列式
  l(u, v) = u的度数            u==v
            -1 * u和v间的边数  u!=v
  变元kirchhoff: 生成树边权积的和 = ...行列式

  例为luogu p3317：给出每条边连通的概率，求恰好生成一棵树的概率
  https://www.luogu.org/problemnew/solution/P3317
 */
#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld EPS = 1e-15; const int N = 55;
inline bool equ(ld a, ld b) { return abs(a-b)<EPS; }

ld a[N][N];
int gauss(int n)
{
    int ret = 1;
    for(int i = 1; i <= n; i++)
    {
        int l = i;
        for(int j = i+1; j <= n; j++) if(a[l][i]<a[j][i]) l = j;
        if(l != i) swap(a[l], a[i]), ret *= -1;
        for(int j = i+1; j <= n; j++)
            for(int k = i+1; k <= n; k++)
                a[j][k] -= a[j][i]*a[i][k]/max(EPS, a[i][i]);
    }
    return ret;
}

int main()
{
    freopen("std.in", "r", stdin);
    int n; scanf("%d\n", &n); ld tmp = 1;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            ld x; scanf("%Lf", &x);
            if(i == j) continue;
            if(j > i) tmp *= max(EPS, 1-x);
            a[i][j] = -x/max(EPS, 1-x);
        }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(i != j) a[i][i] -= a[i][j];
    // for(int i = 1; i <= n; i++, printf("\n"))
    //  for(int j = 1; j <= n; j++) printf("%0.2Lf\t", a[i][j]);

    ld ans = gauss(n-1)*tmp;
    for(int i = 1; i <= n-1; i++) ans *= a[i][i];
    printf("%0.8Lf", ans);
}
