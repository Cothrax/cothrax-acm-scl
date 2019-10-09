Pll operator+(const Pll&a, const Pll&b) {return mkp(a.X+b.X, a.Y+b.Y);}
Pll operator-(const Pll&a, const Pll&b) {return mkp(a.X-b.X, a.Y-b.Y);}
Pll operator*(const Pll&a, const Pll&b) {return mkp(a.X*b.X, a.Y*b.Y);}
Pll operator%(const Pll&a, const Pll&b) {return mkp(a.X%b.X, a.Y%b.Y);}
inline Pll C(ll x) { return mkp(x, x); }

const int N = 510;
Pll s[N], bn[30], B, Z;

/*
素数
61, 83, 113, 151, 211, 281, 379, 509683, 911
1217, 1627, 2179, 2909, 3881, 6907, 9209
12281, 16381, 21841, 29123, 38833, 51787, 69061, 92083
122777, 163729, 218357, 291143, 388211, 517619, 690163, 999983
1226959, 1635947, 2181271, 3877817, 5170427, 6893911, 9191891
12255871, 16341163, 29050993, 38734667, 51646229, 68861641, 91815541
1e9+7, 1e9+9
122420729, 163227661, 217636919, 290182597, 386910137, 687840301, 917120411
1222827239, 1610612741, 3221225473ul, 4294967291ul
*/
