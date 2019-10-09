/*
  单调队列 (例为定窗长最大值)
  var:  h, t        : [h, t)
        q[N]        : 元素值队列
        d[N]        : 标号队列
  func: init()      : init
        upd_h(x)    : 用左端点x更新队头
        upd_t(x)    : 用新元素值x更新队尾
        ins(x, i)   : 向队尾插入一个值为x, 标号i的元素
        top()       : 返回队尾值
  note: 一般流程:   k<j: 
                    1. upd_h
                    2. f[i][j] = ...q.top()...
                    3. upd_t
                    4. ins
        k<=j: 将2换到最后
        注意dp初始条件,及init
        empty时务必特判
 */

struct Queue
{
    int h, t, q[N], d[N]; //d记录从头出队信息
    void init() { h = t = 0; }
    void upd_h(int x) { while(h != t && d[h] < x) h++; }
    void upd_t(int x) { while(h != t && q[t-1] <= x)) t--; }
    void ins(int x, int i) { q[t] = x; d[t++] = i; }
    int top() { return (h != t) ? q[h] : -INF; } 
} q;
