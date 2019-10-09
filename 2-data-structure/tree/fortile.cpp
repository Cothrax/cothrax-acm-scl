/*
  主席树(例为维护区间权值和)
  func: insert(&i, b, e, k, x)  : 单点修改
        query(i, b, e, k)       : 查询<=k的权值和
 */

struct Tree
{
    struct node { int l, r, w; } sgt[N*20];
    int p = 0, rt[N] = {0};
    void insert(int &i, int b, int e, int k, int x)
        {
            sgt[++p] = sgt[i]; i = p;
            sgt[i].w = max(sgt[i].w, x);
            if(b==e) return;
            int mid = (b+e)>>1;
            if(k<=mid) insert(sgt[i].l, b, mid, k, x);
            else insert(sgt[i].r, mid+1, e, k, x);
        }
    int query(int i, int b, int e, int k)
        {
            if(!i) return 0;
            if(b==e) return sgt[i].w;
            int mid = (b+e)>>1;
            if(k<=mid) return query(sgt[i].l, b, mid, k);
            else return max(sgt[sgt[i].l].w, query(sgt[i].r, mid+1, e, k));
        }
} t;
