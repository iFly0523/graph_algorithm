#ifndef HUNGARIAN_HPP
#define HUNGARIAN_HPP
#include "MinSpanTree.hpp"

typedef char VertexType;
typedef int EdgeType;
#define MaxVex 100

// 边表结点
typedef struct EdgeNode {
    int adjvex; // 邻接点域，存储邻接顶点对应的下标
    EdgeType weight; // 用于存储权值，对于非网图可以不需要
    struct EdgeNode* next; // 链域，指向下一个邻接点
} EdgeNode;

// 顶点表结点
typedef struct VertexNode {
    VertexType data; // 顶点域，存储顶点信息
    EdgeNode* firstedge; // 边表头指针
} VertexNode, AdjList[MaxVex];

// 图的邻接表
typedef struct {
    AdjList adjList;
    int numVertexes, numEdges; // 图中当前顶点数和边数
} GraphAdjList;

unsigned int (*AdjMatrix(unsigned int edges[][3]))[vexCounts];
void PrintAdjList(const GraphAdjList& G);

GraphAdjList* CreatAdjList(unsigned int (*edges)[3], GraphAdjList& G);

void InitGraph(unsigned int (*edges)[3],GraphAdjList& G);

GraphAdjList* AdjMatrix2AdjList(unsigned int graph[][vexCounts]);

bool bfs(int s, GraphAdjList& G, int* color);

bool isBipartite(GraphAdjList& G);

bool dfs(int u, GraphAdjList& G, bool* visited, int* match);

void hungarian(GraphAdjList& G);

bool isCompleteBipartite(GraphAdjList& G);

bool dfs_KM(int u, GraphAdjList& G, bool* visited, int* match);

void KM_OptimalMatch(GraphAdjList& G);

bool DMP(GraphAdjList& G);

int countFaces(GraphAdjList& G);

bool BFS(GraphAdjList& G, int start, bool* visited);

#endif