/*
  离散化
  var:  a[N]        : 所有值
        b[N]        : 待离散化的数组, size为n
  func: discrete()  : 接口
*/

const int N = 1e5;
int n, b[N]; vector<int> a;
void discrete()
{
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    rep(i, 1, n) b[i] = lbound(a.begin(), a.end(), b[i]) - a.begin();
}
