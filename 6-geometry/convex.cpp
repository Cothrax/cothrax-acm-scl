/*
  凸包
  func:     convex_hull(vector<point>)          求凸包(不保留共线点)
            convex_hull_stable(vector<point>)   求凸包(保留共线点)
            ploy_line_intersect::init           将凸包边的极角排序
            ploy_line_intersect::solv           O(logN)判断凸包与直线相交
  method:   convex:p_in                         O(logN)判断点在凸包内
            convex:area                         面积
            convex:p_in                         旋转卡壳(不允许共线点)
 */

#define succ(i) ((i+1)%n)
#define S(i, j, k) det(a[j]-a[i], a[k]-a[i])
struct convex
{
    point a[N]; int n;
    convex(int k = 0): n(k) {}
    int p_in(point b)
        {
            point g = (a[0] + a[n/3] + a[2*n/3]) / 3.;
            int l = 0, r = n;
            while(r - l > 1)
            {
                int mid = (l+r)>>1;
                if(cmp(det(a[l]-g, a[mid]-g)) > 0)
                {
                    if(cmp(det(a[l]-g, b-g))>=0 &&
                       cmp(det(a[mid]-g, b-g)<0)) r = mid;
                    else l = mid;
                }
                else
                {
                    if(cmp(det(a[l]-g, b-g))<0 &&
                       cmp(det(a[mid]-g, b-g))>=0) l = mid;
                    else r = mid;
                }
            }
            r %= n;
            return cmp(det(a[l]-b, a[r]-b));
        }
    double area()
        {
            double ret = 0;
            rep(i, 0, n-1) ret += det(a[i+1], a[i]);
            return abs(ret/2.);
        }

    // 不可以有共线点
    double diameter()
        {
            if(n == 1) return 0;
            double ret = 0;
            int j = 1;
            rep(i, 0, n-1)
            {
                while(cmp(S(i, succ(i), j)-S(i, succ(i), succ(j)))<0)
                    j = succ(j);
                ret = max(ret, dist(a[i], a[j]));
                ret = max(ret, dist(a[succ(i)], a[succ(j)]));
            }
            return ret;
        }
};

bool comp_h(const point &a, const point &b)
{
    return cmp(a.x-b.x)<0 || (cmp(a.x-b.x)==0 && cmp(a.y-b.y)<0);
}

convex convex_hull_stable(vector<point> a)
{
    convex ret = convex(2*a.size()+5);
    sort(a.begin(), a.end(), comp_h);
    a.erase(unique(a.begin(), a.end()), a.end());

    int m = 0;
    rep(i, 0, a.size()-1)
    {
        while(m>1 && cmp(det(ret.a[m-1]-ret.a[m-2], a[i]-ret.a[m-1]))<0)
            m--;
        ret.a[m++] = a[i];
    }
    int k = m;
    per(i, a.size()-1, 0)
    {
        while(ret.a[m-1]==a[i] ||
              (m>k&&(cmp(det(ret.a[m-1]-ret.a[m-2], a[i]-ret.a[m-1]))<0)))
            m--;
        ret.a[m++] = a[i];
    }
    ret.n = m - (a.size()!=1);
    return ret;
}

convex convex_hull(vector<point> a)
{
    convex ret = convex(2*a.size()+5);
    sort(a.begin(), a.end(), comp_h);
    a.erase(unique(a.begin(), a.end()), a.end());

    int m = 0;
    rep(i, 0, (int)a.size()-1)
    {
        while(m>1 && cmp(det(ret.a[m-1]-ret.a[m-2], a[i]-ret.a[m-1]))<=0)
            m--;
        ret.a[m++] = a[i];
    }
    int k = m;
    per(i, (int)a.size()-1, 0)
    {
        while(m>k&&(cmp(det(ret.a[m-1]-ret.a[m-2], a[i]-ret.a[m-1]))<=0))
            m--;
        ret.a[m++] = a[i];
    }
    ret.n = m - (a.size()!=1);
    return ret;
}

namespace ploy_line_intersect
{
    double angle(point p) { return atan2(p.y, p.x); }
    int n; vector<point> p;
    pair<double, int> seq[N];
    void init(convex &ploy)
    {
        // 这里的n是凸包的点数
        rep(i, 0, n-1) seq[i] = mkp(angle(ploy.a[i+1]-ploy.a[i]), i);
        sort(seq, seq+n);
        seq[n] = seq[0];
    }

    bool solv(convex &ploy, point s, point e)
    {
        int i = upper_bound(seq, seq+n, mkp(angle(e-s), 0)) - seq,
            j = upper_bound(seq, seq+n, mkp(angle(s-e), 0)) - seq;
        point p1 = ploy.a[seq[i].Y], p2 = ploy.a[seq[j].Y];
        return cmp(det(p1-s, e-s) * det(p2-s, e-s)) < 0;
    }
}
