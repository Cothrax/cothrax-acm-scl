/*
  2-SAT: Solve CNF formula (x1 or y1) and (x2 or y2) ... and (xn or yn)
  (x1 or y1) == (!x1 -> y1) and (!y1 -> x1)
  
  求强连通分量, 若任意!a 和 a不在一个分量内则可行
  拓扑序在前的赋值为false
 */
