#include <iostream>
#include <vector>
#include <cstring>
#include "MinSpanTree.hpp"
#include "Hungarian.hpp"


using namespace std;

// 手动初始化图的邻接表
GraphAdjList* CreatAdjList(unsigned int (*edges)[3], GraphAdjList& G) {
    
        for (int i = 0; i < G.numEdges; ++i) {
        int start = edges[i][0];
        int end = edges[i][1];
        int mywight = edges[i][2];
        // 创建边表结点
        EdgeNode* edge = new EdgeNode;
        edge->adjvex = end;
        edge->weight = mywight; // 假设权值都为1
        edge->next = G.adjList[start].firstedge; // 将新结点插入到边表头部
        G.adjList[start].firstedge = edge;
    }
    for (int i=0; i < G.numEdges; ++i) {
        int start = edges[i][1];
        int end = edges[i][0];

        EdgeNode* edge = new EdgeNode;
        edge->adjvex = end;
        edge->weight = 1; // 假设权值都为1
        edge->next = G.adjList[start].firstedge; // 将新结点插入到边表头部
        G.adjList[start].firstedge = edge;
    }
    return &G;
}

void InitGraph(unsigned int (*edges)[3],GraphAdjList& G) {
    // 顶点数和边数在头文件 “MinSpanTree.h中修改”
    G.numVertexes = vexCounts;
    G.numEdges = edgeCounts;

    // 初始化顶点
    for (int i = 0; i < G.numVertexes; ++i) {
        G.adjList[i].data = '0' + i; // 顶点信息从'A'开始依次递增
        G.adjList[i].firstedge = nullptr; // 边表头指针初始化为空
    }

    // 调用CreatAdjList生成邻接表
    CreatAdjList(edges, G);
}

// 打印图的邻接表
void PrintAdjList(const GraphAdjList& G) {
    for (int i = 0; i < G.numVertexes; ++i) {
        cout << "顶点 " << G.adjList[i].data << " 的邻接点有：";
        EdgeNode* edge = G.adjList[i].firstedge;
        while (edge) {
            cout << G.adjList[edge->adjvex].data << "  ";
            edge = edge->next;
        }
        cout << endl;
    }
}

GraphAdjList* AdjMatrix2AdjList(unsigned int graph[][vexCounts]){
    GraphAdjList* G = NULL;
    
    return G;
}

bool bfs(int s, GraphAdjList& G, int* color) {
    queue<int> q;
    q.push(s);
    color[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (EdgeNode* e = G.adjList[u].firstedge; e; e = e->next) {
            int v = e->adjvex;
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                q.push(v);
            } else if (color[v] == color[u]) {
                return false; // 发现相邻节点颜色相同，说明不是二分图
            }
        }
    }

    return true;
}

// 判断图是否是二部图
bool isBipartite(GraphAdjList& G) {
    int color[MaxVex];
    memset(color, -1, sizeof(color)); // 初始化颜色数组为-1

    for (int i = 0; i < G.numVertexes; ++i) {
        if (color[i] == -1) {
            if (!bfs(i, G, color)) {
                return false; // 发现不是二分图，返回false
            }
        }
    }

    return true; // 遍历完所有连通分量都没有问题，说明是二分图
}

bool dfs(int u, GraphAdjList& G, bool* visited, int* match) {
    for (EdgeNode* e = G.adjList[u].firstedge; e; e = e->next) {
        int v = e->adjvex;
        if (!visited[v]) {
            visited[v] = true;
            if (match[v] == -1 || dfs(match[v], G, visited, match)) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void hungarian(GraphAdjList& G) {
    if (!isBipartite(G)) {
        cout << endl;
        cout << "警告：该邻接表对应的图不是一个二分图!" << endl;
        return;
    }

    cout << "该邻接表对应的图是一个二分图" <<endl;
    int match[MaxVex];
    bool visited[MaxVex];
    memset(match, -1, sizeof(match)); // 初始化匹配数组为-1

    int maxMatching = 0;
    for (int u = 0; u < G.numVertexes; ++u) {
        memset(visited, false, sizeof(visited)); // 初始化visited数组为false
        if (dfs(u, G, visited, match)) {
            maxMatching++;
        }
    }
    cout << "匹配结果：" << endl;
    for (int v = 0; v < G.numVertexes; ++v) {
        if (match[v] != -1 && match[v] < v) { // 只输出顶点值较小的一侧
            cout << match[v] << " - " << v << endl;
        }
    }
    cout << "该结果属于" << (maxMatching == G.numVertexes ? "完美匹配" : "最大匹配") << endl;
}

bool isCompleteBipartite(GraphAdjList& G) {
    for (int i = 0; i < G.numVertexes; ++i) {
        int count = 0;
        for (EdgeNode* e = G.adjList[i].firstedge; e; e = e->next) {
            count++;
        }
        if (count != G.numVertexes / 2) {
            return false;
        }
    }
    return true;
}

bool dfs_KM(int u, GraphAdjList& G, bool* visited, int* match) {
    for (EdgeNode* e = G.adjList[u].firstedge; e; e = e->next) {
        int v = e->adjvex;
        if (!visited[v]) {
            visited[v] = true;
            if (match[v] == -1 || dfs(match[v], G, visited, match)) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void KM_OptimalMatch(GraphAdjList& G) {
    if (!isCompleteBipartite(G)) {
        cout << "该邻接表对应的图不是一个完全偶图" << endl;
        return;
    }

    int match[MaxVex];
    bool visited[MaxVex];
    int weight = 0; // 记录最优匹配的权重
    memset(match, -1, sizeof(match)); // 初始化匹配数组为-1

    int maxMatching = 0;
    for (int u = 0; u < G.numVertexes; ++u) {
        memset(visited, false, sizeof(visited)); // 初始化visited数组为false
        if (dfs(u, G, visited, match)) {
            maxMatching++;
        }
    }

    cout << "属于" << (maxMatching == G.numVertexes ? "完美匹配" : "最大匹配") << endl;
    cout << "匹配结果：" << endl;
    for (int v = 0; v < G.numVertexes; ++v) {
        if (match[v] != -1 && match[v] < v) { // 只输出顶点值较小的一侧
            cout << match[v] << " - " << v << " (代价：" << G.adjList[match[v]].firstedge->weight << ")" << endl;
            weight += G.adjList[match[v]].firstedge->weight; // 累加权重
        }
    }
    cout << "最优匹配的总代价为：" << weight << endl;
}

bool BFS(GraphAdjList& G, int start, bool* visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (EdgeNode* e = G.adjList[u].firstedge; e; e = e->next) {
            int v = e->adjvex;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    // 检查是否所有顶点都被访问到了
    for (int i = 0; i < G.numVertexes; ++i) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

// 欧拉公式计算图的面数
int countFaces(GraphAdjList& G) {
    int v = G.numVertexes;
    int e = G.numEdges;
    return 2 - v + e;
}

// DMP 算法
bool DMP(GraphAdjList& G) {
    if (G.numEdges == 0 || G.numVertexes < 3) {
        return false; // 边数为0或者顶点数小于3，不是可平面图
    }

    bool visited[MaxVex];
    memset(visited, false, sizeof(visited));

    // 检查图的连通性
    if (!BFS(G, 0, visited)) {
        return false; // 图不是连通的，不是可平面图
    }

    // 检查图是否是二部图
    if (!isBipartite(G)) {
        return false; // 不是二部图，不是可平面图
    }

    // 计算图的面数
    int faces = countFaces(G);

    // 检查欧拉公式是否成立
    if (faces != 2) {
        return false; // 不是可平面图
    }

    return true;
}




















// int main() {
//     //边的连接状态，{0，1}表示节点0和节点1无向连接
//     // unsigned int edges[edgeCounts][3] = {{0, 1, 3}, {0, 3, 2}, {1, 2, 3}, {1, 3, 4}, {2, 4, 1}, {3, 2, 2}, {3, 4, 3}};
//     unsigned int edges[edgeCounts][3] = {{0, 4, 3}, {0, 1, 3}, {1, 4, 2}, {1, 5, 3}, {1, 7, 4}, {2, 5, 2}, {3, 6, 1}};
//     GraphAdjList G;
//     InitGraph(edges,G);
//     PrintAdjList(G);

//     hungarian(G);



//     std::cout << "Press any key to exit...";
//     std::cin.get();
//     return 0;
// }
