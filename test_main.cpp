#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include "MinSpanTree.hpp"
#include "ShortestPath.hpp"
#include "Hungarian.hpp"
//匈牙利算法和最优匹配的函数与相关的变量都存在了"Hungarian.hpp"之中。在平面性判断中的几个函数也都放在了Hungarian.hpp之中

using namespace std;
#define INF std::numeric_limits<int>::max()
unsigned int adjMat[vexCounts][vexCounts] = {0};
unsigned int AdjMat[][vexCounts] = {0};

unsigned int (*AdjMatrix(unsigned int edges[][3]))[vexCounts]  //邻接矩阵表示法
{
    for (int i = 0; i < vexCounts; i++)   //初始化邻接矩阵
        for (int j = 0; j < vexCounts; j++)
        {
            adjMat[i][j] = INF;
        }

    //给每条边赋予权值
    for (int i = 0; i < edgeCounts; i++) {
            int start = edges[i][0];
            int end = edges[i][1];
            int wight = edges[i][2];

            adjMat[start][end] = wight;
            adjMat[end][start] = wight;
    }


    for (int i = 0; i < vexCounts; ++i) {
        for (int j = 0; j < vexCounts; ++j) {
        AdjMat[i][j] = adjMat[i][j];
        }
    }

    return adjMat;
}

int main()
{
    Myinfo();
    //一般简单图的边信息
    // unsigned int edges[edgeCounts][3] = {{0, 1, 3}, {0, 3, 2}, {3, 1, 1}, {2, 0, 4}, {2, 3, 3}, {4, 3, 2}, {4, 2, 3}};
    // unsigned int edges[edgeCounts][3] = {{0, 1, 6}, {0, 2, 1}, {0, 3, 5}, {1, 2, 5}, {1, 4, 3}, {2, 3, 3}, {2, 4, 6}, {2, 5, 4}, {3, 5, 2}, {4, 5, 6}};
    // //一般偶图的边信息
    // unsigned int edges[edgeCounts][3] = {{0, 4, 3}, {0, 6, 3}, {1, 4, 2}, {1, 5, 3}, {1, 7, 4}, {2, 5, 2}, {3, 6, 1}};
    //完全偶图的边信息
    unsigned int edges[edgeCounts][3] = {{0, 4, 3}, {0, 5, 3}, {0, 6, 2}, {0, 7, 3}, {1, 4, 1}, {1, 5, 2}, {1, 6, 4}, {1, 7, 3}, {2, 4, 3}, {2, 5, 3}, {2, 6, 2}, {2, 7, 3},{3, 4, 1}, {3, 5, 2}, {3, 6, 4}, {3, 7, 3}};
    
    
    unsigned int (*adjMat)[vexCounts] = AdjMatrix(edges);
    //邻接矩阵
    // printAdjMatrix(adjMat);

    // cout << "*************************最短路算法测试*************************" << endl;
    // int start = 3;
    // std::cout << "Dantzig 最短路径：" << std::endl;
    // Dantzig(AdjMat, start);
    // std::cout << "Dijkstra 最短路径：" << std::endl;
    // dijkstra(AdjMat, start);
    // std::cout << std::endl;
    // std::cout << "Ford 最短路径：" << std::endl;
    // ford(AdjMat, start);

    // cout << "*************************最小生成树算法测试*************************" << endl;
    // cout << "Kruskal :" << endl;
    // MiniSpanTree_Kruskal(adjMat); //Prim算法，从顶点2开始.
    // cout << "-------------" << endl << "Prim:" << endl;
    // MiniSpanTree_Prim(adjMat,4);//Kruskal算法

    // cout << "*************************匈牙利算法测试*************************" << endl;
    // //在初始化的时候，给定一个偶图的边信息二维矩阵
    // GraphAdjList G;
    // InitGraph(edges,G);
    // cout << "图的邻接表对应的信息如下："<< endl;
    // PrintAdjList(G);
    // hungarian(G);

    cout << "*************************最优匹配算法测试*************************" << endl;
    // //在初始化的时候，给定一个完全偶图的边信息二维矩阵
    GraphAdjList G1;
    InitGraph(edges,G1);
    PrintAdjList(G1);
    KM_OptimalMatch(G1);
    
    cout << "Press any key to exit...";
    cin.get();
    return 0;
}