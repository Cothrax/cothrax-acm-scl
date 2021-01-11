/*
  二维ST表
 */
int n, m, logn, logm;
int a[305][305];
int st[505][505][10][10];

inline int query(int x1, int y1, int x2, int y2)
{
    int k1 = log2(x2 - x1 + 1), k2 = log2(y2 - y1 + 1);
    return max(st[x1][y1][k1][k2], max(st[x2-(1<<k1)+1][y1][k1][k2], max(st[x1][y2-(1<<k2)+1][k1][k2], st[x2-(1<<k1)+1][y2-(1<<k2)+1][k1][k2])));
}

int main()
{
    read(n); read(m);
	logn = ceil(log2(n));
	logm = ceil(log2(m));
	
    for (int i = 1 ; i <= n ; ++i)
        for (int j = 1 ; j <= m ; ++j)
            st[i][j][0][0] = a[i][j] = read();
    for (int p = 0 ; p <= logn; p ++)
        for (int q = 0 ; q <= logm; q ++)
            if (p != 0 or q != 0)
                for (int i = 1 ; i + (1<<p) - 1 <= n ; i ++)
                    for (int j = 1 ; j + (1<<q) - 1 <= m ; j ++)
                        if (!p) st[i][j][p][q] = max(st[i][j][p][q - 1], st[i][j+(1<<(q-1))][p][q - 1]);
                        else st[i][j][p][q] = max(st[i][j][p-1][q], st[i+(1<<(p-1))][j][p-1][q]);
    int q = read();
    while(q--)
    {
		int x1, y1, x2, y2;
		read(x1); read(y1); read(x2); read(y2);
        printf("%d\n", query(x1,y1,x2,y2));
    }
}
