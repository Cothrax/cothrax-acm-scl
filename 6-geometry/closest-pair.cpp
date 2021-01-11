/*
  平面最近点对 - 标准分治做法 O(NlogN)
 */

const int N = 2e5+10;
double x[N], y[N];
bool comp1(int a, int b) { return x[a] < x[b]; }
double dist(int a, int b)
{
	return sqrt((x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b])); 
}

int n, a[N], b[N], c[N];
// double ans = 1e18;
double solv(int l, int r)
{
	if(l == r) return 1e18;
	int mid = (l+r)>>1;
	double mid_d = x[a[mid]];
	double delta = min(solv(l, mid), solv(mid+1, r));

	double ans = delta;

	int i = l, j = mid+1, p = l;
	while(i <= mid || j <= r)
	{
		while(i <= mid && fabs(x[a[i]] - mid_d) > delta) i++;
		while(j <= r && fabs(x[a[j]] - mid_d) > delta) j++;
		if(!(i <= mid || j <= r)) break;
		
		if(j > r || (i <= mid && y[a[i]] < y[a[j]])) b[p++] = a[i++];
		else b[p++] = a[j++];
	}

	for(int k = l; k < p; k++)
	{
		int up = min(k+12, p);
		for(int q = k+1; q < up; q++) ans = min(ans, dist(b[k], b[q]));
	}

	i = l, j = mid+1, p = l;
	while(i <= mid || j <= r)
	{
		if(j > r || (i <= mid && y[a[i]] < y[a[j]])) b[p++] = a[i++];
		else b[p++] = a[j++];
	}

	
	for(int k = l; k <= r; k++) a[k] = b[k];
	return ans;
}

int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%lf%lf", x+i, y+i), a[i] = i;
	sort(a, a+n, comp1);
	double ans = solv(0, n-1);
	printf("%.3lf\n", ans);
}

/*
  随机做法
  将坐标系随机转一个方向，按x坐标排序后取相邻5个中最近的
 */


const int N = 2e5+10;
int n;
double x[N], y[N], x0[N];
const double pi = acos(-1.0);
inline bool comp1(const int a, const int b) { return x0[a] < x0[b]; }
inline double dist(int a, int b)
{
	return (x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]); 
}

int a[N];
double solv(double c, double s)
{
	rep(i, 0, n-1) x0[i] = x[i] * c - y[i] * s;
	sort(a, a+n, comp1);
	double ret = 1e20;
	rep(i, 0, n-1)
	{
		int up =  min(i+5, n-1);
		rep(j, i+1, up) ret = min(ret, dist(a[i], a[j]));
	}
	// cout << d << " " << ret << endl;
	return ret;
}

int main()
{
	scanf("%d", &n);
	rep(i, 0, n-1) scanf("%lf%lf\n", x+i, y+i);
	rep(i, 0, n-1) a[i] = i;
	srand(time(0));

	double d = (double)(rand()%360)/ 180.0 * pi;
	double ans = sqrt(solv(cos(d), sin(d))) / 2;
	printf("%.3lf\n", ans);
}

