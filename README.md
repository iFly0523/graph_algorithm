# graph_algorithm
电子科技大学图论作业


| 文件名  | 简介 |
| ------ | ------ |
| Hungarian.cpp | 匈牙利算法与最优匹配算法的定义  |
| Hungarian.hpp | 匈牙利算法与最优匹配算法的声明  |
| MinSpanTree.cpp | 最小生成树算法的函数定义  |
| MinSpanTree.hpp  | 最小生成树算法的函数声明  |
| ShortestPath.cpp  | 最短路算法的函数定义  |
| ShortestPath.hpp  | 最短路算法的函数声明  |
| test_main.cpp   | 主要测试主文件 |


1.编写了三种最短路算法（Dantzig、dijkstra、ford）； 
2.编写了两种最小生成树算法测试（Kruskal、Prim） 
3.编写了匈牙利算法（hungarian） 
4.编写了最优匹配算法（KM_OptimalMatch） 

算法结构：

## 1.图的输入形式：
使用一个二维数组表示边的信息，unsigned int edges[edgeCounts][3]。edgeCounts表示该图一共有多少个边。Edges[i][0]表示第𝑖个边的起点节点，Edges[1][1]表示第𝑖个边的终点节点，Edges[i][0]表示第𝑖个边的权值。

## 2.图的表达形式：
调用函数AdjMatrix(edges)，会将该二维数组转化为一个邻接矩阵 adjMat。邻接
矩阵adjMat将用于最短路算法和最小生成树算法。 
调用函数InitGraph(edges,G)，会将该二维数组转化为一个邻接链表adjList。邻接链表adjList 将会用于匈牙利算法和最优匹配算法。printAdjMatrix(adjMat)和 PrintAdjList(G)两个函数分别用于输出对应图的邻接矩阵和邻接链表。 

## 3.算法测试： 
在test_main.cpp 中会引用上述算法所对应的头文件并对所有的算法进行测试。 
不同的unsigned int edges[edgeCounts][3]可以进行多组测试，但是由于本人代码
水平有限，每启用一个 edges，需要去往 MinSpanTree.hpp 中手动更改顶点数量
vexCounts 和边数edgeCounts。 
