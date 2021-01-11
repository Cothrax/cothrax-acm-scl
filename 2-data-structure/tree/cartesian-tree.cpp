/*
  笛卡尔树 O(N) 内构造区间最小值构成的树
  e.g.
  4 2 5 1 3
       -1-
   -2-    3
  4   5
 */


int n, p[N], ch[N][2];
int build()
{
	static int stk[N];
	int top = 0;
	rep(i, 0, n) ch[i][0] = ch[i][1] = -1;
	rep(i, 0, n-1)
	{
		// 可以跳过一些没用的值
		// if(d[i] == p[i]%10) continue;
		
		int lst = -1; // 保存上一个退栈的节点
		while(top && p[stk[top]] > p[i])
		{
			if(lst != -1) add(stk[top], lst); // 退栈加边
			lst = stk[top--];
		}
		if(lst != -1) add(i, lst); // 加边
		stk[++top] = i;
	}
	while(top > 1) { add(stk[top-1], stk[top]); top--; } // 弹出最右链
	return top ? stk[top] : -1;	 // 树空返回-1 （可能全都跳过了）
}
