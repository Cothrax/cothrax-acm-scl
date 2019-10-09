/*
  多边形类
  method:   input(int)                      读入多边形(逆时针)
            p_in(point)                     判断点在形内(环顾法)
            area()                          面积
            mass_center()                   重心
            border_int_p()                  边上整点数
            inside_int_p()                  形内整点数
 */

struct polygon
{
    int n; point a[N];
    polygon(){}
    void input(int k)
        {
            n = k;
            rep(i, 0, n-1) a[i].input();
            a[n] = a[0];
        }
    int p_in(point t)
        {
            double sum = 0;
            rep(i, 0, n-1)
            {
                if(line(a[i], a[i+1]).p_on(t)) return 0;
                int sgn = cmp(det(a[i]-t, a[i+1]-t));
                double theta = acos(dot(a[i]-t, a[i+1]-t) /
                                    (dist(a[i], t) * dist(a[i+1], t)));
                sum += theta * sgn;
            }
            return fabs(sum) > PI/2 ? 1 : -1;
        }
    double area()
        {
            double ret = 0;
            rep(i, 0, n-1) ret += det(a[i+1], a[i]);
            return ret/2.;
        }
    point mass_center()
        {
            point ret = point(0, 0);
            if(cmp(area()) == 0) return ret;
            rep(i, 0, n-1) ret = ret + det(a[i+1], a[i])*(a[i]+a[i+1]);
            return ret/area()/6.;
        }

    int border_int_p()
        {
            int ret = 0;
            rep(i, 0, n-1)
            {
                point tmp = a[i+1]-a[i];
                ret += abs(gcd(int(tmp.x), int(tmp.y)));
            }
            return ret;
        }
    int inside_int_p() { return int(area()-border_int_p()/2.+1); }
};


