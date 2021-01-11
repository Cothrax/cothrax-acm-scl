/*
  Rolling Hash
  func:	StrHash(base)	基数为base
		init(s)			计算字符串s的hash
		get(l, r)		获取子串[l, r]的hash
 */
struct StrHasher
{
	ull B, hs[N], bn[N];
	StrHasher(ll base)
		{
			B = base;
			bn[0] = 1;
			rep(i, 1, N-1) bn[i] = bn[i-1] * B;
		}

	void init(char *s)
		{
			hs[0] = s[0] - 'a';
			for(int i = 1; s[i]; i++) hs[i] = hs[i-1] * B + (s[i] - 'a');
		}

	ull get(int l, int r)
		{
			return hs[r] - (l ? hs[l-1] * bn[r-l+1] : 0);
		}
} hsr1(83), hsr2(61);


/*
  手动 unordered_map<pair<ull, ull>, int>
  var:	val			值
		key			键
  func:	clear()		利用flg版本标记清空 O(1)
		get_idx(k)	获取键k在表中的下表
		[k]			获取val[get_idx(k)]的引用

  note:	如果要改成单hash: 改hashk定义，改get_idx第一行的下标生产逻辑
 */
const int SIZE = 999983;		// hash表大小
const int N = 6e5+10;			// 可能元素的个数
typedef pair<ull, ull> hashk;
struct HashTable
{
	hashk key[N]; int val[N], nxt[N], sz;
	int head[SIZE], flg[SIZE], vs;
	HashTable()
		{
			memset(flg, 0, sizeof(flg));
			vs = 1; sz = 0;
		}
	void clear()
		{
			sz = 0; vs++;
		}
	int get_idx(hashk k)
		{
			int u = k.first % SIZE;
			if(flg[u] != vs)
			{
				flg[u] = vs;
				head[u] = ++sz;
				key[sz] = k; val[sz] = 0; nxt[sz] = 0;
				return sz;
			}

			int i;
			for(i = head[u]; i; i = nxt[i]) if(key[i] == k) break;
			if(i) return i;

			key[++sz] = k; val[sz] = 0;
			nxt[sz] = head[u]; head[u] = sz;
			return sz;
		}
	
	int& operator[](hashk k) { return val[get_idx(k)]; }
} mp;

// 重载pair运算符
Pll operator+(const Pll&a, const Pll&b) {return mkp(a.X+b.X, a.Y+b.Y);}
Pll operator-(const Pll&a, const Pll&b) {return mkp(a.X-b.X, a.Y-b.Y);}
Pll operator*(const Pll&a, const Pll&b) {return mkp(a.X*b.X, a.Y*b.Y);}
Pll operator%(const Pll&a, const Pll&b) {return mkp(a.X%b.X, a.Y%b.Y);}
inline Pll C(ll x) { return mkp(x, x); }

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
