/*
  半平面
  class:    plane                           半平面(表示s->e左侧)
  func:     hpi(plane[], int)               半平面交
            convex cut(convex, plane)       半平面和多边形交
            core(ploygon)                   多边形的核
  method:   plane:&                         直线求交
 */

struct plane
{
    point s,e; // 线段左侧的半平面
    double k;
    plane(){}
    plane(point _s,point _e)
        {
            s = _s; e = _e;
            k = atan2(e.y-s.y, e.x-s.x);
        }
    point operator &(const plane &b) const
        {
            point res = s;
            double t = det(s-b.s, b.s-b.e) / det(s-e, b.s-b.e);
            res.x += (e.x-s.x)*t;
            res.y += (e.y-s.y)*t;
            return res;
        }
};

bool hpi_cmp(const plane &a, const plane &b)
{
    if(fabs(a.k-b.k) > EPS) return a.k < b.k;
    return det(a.s-b.s, b.e-b.s) < 0;
}

plane q[N];
convex hpi(line ps[], int n)
{
    int tot = n;
    sort(ps, ps + n, hpi_cmp);
    
    tot = 1;
    rep(i, 1, n-1)
        if(fabs(ps[i].k - ps[i-1].k) > EPS) ps[tot++] = ps[i];
    int h = 0, t = 1;
    q[0] = ps[0]; q[1] = ps[1];
    rep(i, 2, tot-1)
    {
        if(fabs(det(q[t].e - q[t].s, q[t-1].e - q[t-1].s)) < EPS ||
           fabs(det(q[h].e - q[h].s, q[h+1].e - q[h+1].s)) < EPS)
            return convex(0);
        while(h < t &&
              det((q[t]&q[t-1])-ps[i].s, ps[i].e-ps[i].s) > EPS) t--;
        while(h < t &&
              det((q[h]&q[h+1])-ps[i].s, ps[i].e-ps[i].s) > EPS) h++;
        q[++t] = ps[i];
    }
    while(h < t &&
          det((q[t]&q[t-1])-q[h].s, q[h].e-q[h].s) > EPS) t--;
    while(h < t &&
          det((q[h]&q[h-1])-q[t].s, q[t].e-q[t].e) > EPS) h++;
    if(t <= h+1) return convex(0);

    convex ret(0);
    rep(i, h, t-1) ret.pb(q[i] & q[i+1]);
    if(h < t-1) ret.pb(q[h] & q[t]);
    return ret;
} 

#define succ(i) ((i+1)%n)
#define pred(i) (i?i-1:n-1)
convex cut(convex &ploy, plane &L)
{
    int n = ploy.n;
    convex ret;
    rep(i, 0, n-1)
        if(cmp(L.calc(ploy.a[i])) < 0) ret.pb(ploy.a[i]);
        else
        {
            if(cmp(det(L.e-L.s, pred(i)-L.s)) > 0)
                ret.pb(L & plane(ploy.a[pred(i)], ploy.a[i]));
            if(cmp(det(L.e-L.s, succ(i)-L.s)) > 0)
                ret.pb(L & plane(ploy.a[i], ploy.a[succ(i)]));
        }
    return ret;
}

// ploy逆时针
convex core(polygon &ploy)
{
    convex ret;
    ret.push_back(point(-INF, -INF));
    ret.push_back(point(INF, -INF));
    ret.push_back(point(INF, INF));
    ret.push_back(point(-INF, INF));
    int n = ploy.n;
    rep(i, 0, n-1)
    {
        plane L(ploy.a[i], ploy.a[succ(i)]);
        ret = cut(ret, L);
    }
    return ret;
}
