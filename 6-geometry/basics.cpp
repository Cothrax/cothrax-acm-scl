/*
  点, 直线, 浮点修正
  func:     int cmp(double)                 判断double符号
            double rec(double, double)      四舍五入(避免负0)
            det(point, point)               叉积
            dot(point, point)               点积
            dist(point, point)              距离
  class:    point                           点
            line                            线段(直线)
  mathod:   line:p_dist(point)              点到直线距离
            line:p_on(point)                点是否在线段上
 */

int cmp(double x)
{
    if(fabs(x) < EPS) return 0;
    if(x > 0) return 1; else return -1;
}

inline double rec(double x, double prec)
{
    x = round(x*prec)/prec;
    return sgn(x) == 0 ? 0 : x;
}

struct point
{
    double x, y;
    point(){}
    point(double a, double b) : x(a), y(b) {}
    void input() { scanf("%lf%lf", &x, &y); }
    friend point operator + (const point &a, const point &b)
        { return point(a.x+b.x, a.y+b.y); }
    friend point operator - (const point &a, const point &b)
        { return point(a.x-b.x, a.y-b.y); }
    friend point operator *  (const double &a, const point &b)
        { return point(a*b.x, a*b.y); }
    double norm() { return sqrt(squ(x)+squ(y)); }
};

double det(const point &a, const point &b) { return a.x*b.y-a.y*b.x; }
double dot(const point &a, const point &b) { return a.x*b.x+a.y*b.y; }
double dist(const point &a, const point &b) { return (a-b).norm(); }

struct line
{
    point a, b;
    line() {};
    line(point x, point y): a(x), b(y) {}
    double p_dist(point x) { return fabs(det(x-a, x-b) / dist(a, b)); }
    bool p_on(point x)
        {
            return cmp(det(x-a, x-b)) == 0 && cmp(dot(x-a, x-b)) <= 0;
        }
};
