/*
  排列相关算法
  func:  merge(b, l, r)     : return 逆序数(归并排序)
 */

int merge(int *b, int l, int r)
{
    static int c[N];
    if(l>=r) return 0;
    int mid = (l+r)>>1;
    int ret = merge(b, l, mid) + merge(b, mid+1, r);
    int p = l, q = mid+1;
    rep(i, l, r)
    {
        if(p>mid || (q<=r && b[q]<b[p])) c[i] = b[q++], ret += mid-p+1;
        else c[i] = b[p++];
    }
    rep(i, l, r) b[i] = c[i];
    return ret;
}
