#ifndef MYTREE_HPP
#define MYTREE_HPP

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
#define INFINITE std::numeric_limits<int>::max()
#define VertexData unsigned int  //顶点数据
#define UINT  unsigned int
#define vexCounts 8  //顶点数量
#define edgeCounts 16
extern char vextex[];

struct myinfo
{
    int ID;
    int sore;
    std::string name;
};

struct node 
{
    VertexData data;
    unsigned int lowestcost;
}; //Prim算法中的辅助信息


typedef struct 
{
    VertexData u;
    VertexData v;
    unsigned int cost;  //边的代价
}Arc;  //原始图的边信息

void MiniSpanTree_Prim(unsigned int adjMat[][vexCounts], unsigned int s);

int Minmum(struct node * closedge);

void ReadArc(unsigned int  adjMat[][vexCounts],vector<Arc> &vertexArc); //保存图的边代价信息

bool compare(Arc  A, Arc  B);

bool FindTree(VertexData u, VertexData v,vector<vector<VertexData> > &Tree);

void MiniSpanTree_Kruskal(unsigned int adjMat[][vexCounts]);

void Myinfo();

void printAdjMatrix(unsigned int graph[][vexCounts]);

class MyTree {
public:
    std::string m_Name;
    MyTree(const std::string& name);  // 构造函数声明
    ~MyTree(); // 析构函数声明

    // 其他成员函数声明
    void test01();

private:
    // 可以在这里声明树的私有成员
};

#endif // MYTREE_HPP