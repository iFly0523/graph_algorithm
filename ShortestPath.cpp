#include <iostream>
#include <vector>
#include "ShortestPath.hpp"

void dijkstra(const unsigned int adjMat[][vexCounts], int start) {
    std::vector<int> dist(vexCounts, INFINITE); // 用于保存起始点到各点的最短距离
    std::vector<int> parent(vexCounts, -1); // 用于保存最短路径中的父节点
    std::vector<bool> visited(vexCounts, false); // 用于标记是否已经访问过该点

    dist[start] = 0; // 起始点到自身的距离为0

    for (int count = 0; count < vexCounts - 1; ++count) {
        int minDist = INFINITE, minIndex = -1;

        // 选择未访问的点中距离最小的点
        for (int i = 0; i < vexCounts; ++i) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }

        // 标记该点已经访问
        visited[minIndex] = true;

        // 更新起始点到其他点的距离
        for (int i = 0; i < vexCounts; ++i) {
            if (!visited[i] && adjMat[minIndex][i] != INFINITE &&
                dist[minIndex] + adjMat[minIndex][i] < dist[i]) {
                dist[i] = dist[minIndex] + adjMat[minIndex][i];
                parent[i] = minIndex;
            }
        }
    }

    // 输出结果
    for (int i = 0; i < vexCounts; ++i) {
        if (i != start) {
            std::cout << start << " -> " << i << ": ";
            std::vector<int> path;
            int cur = i;
            while (cur != start) {
                path.push_back(cur);
                cur = parent[cur];
            }
            std::cout << start;
            for (int j = path.size() - 1; j >= 0; --j) {
                std::cout << " -> " << path[j];
            }
            std::cout << ", 距离为 " << dist[i] << std::endl;
        }
    }
}

void ford(const unsigned int adjMat[][vexCounts], int start) {
    std::vector<int> dist(vexCounts, INFINITE); // 用于保存起始点到各点的最短距离
    std::vector<int> parent(vexCounts, -1); // 用于保存最短路径中的父节点

    dist[start] = 0; // 起始点到自身的距离为0

    // 重复 |V|-1 次松弛操作
    for (int count = 0; count < vexCounts - 1; ++count) {
        // 对每一条边进行松弛操作
        for (int i = 0; i < vexCounts; ++i) {
            for (int j = 0; j < vexCounts; ++j) {
                if (adjMat[i][j] != INFINITE && dist[i] != INFINITE &&
                    dist[i] + adjMat[i][j] < dist[j]) {
                    dist[j] = dist[i] + adjMat[i][j];
                    parent[j] = i;
                }
            }
        }
    }

    // 检查是否存在负权回路
    for (int i = 0; i < vexCounts; ++i) {
        for (int j = 0; j < vexCounts; ++j) {
            if (adjMat[i][j] != INFINITE && dist[i] != INFINITE &&
                dist[i] + adjMat[i][j] < dist[j]) {
                std::cerr << "图中存在负权回路" << std::endl;
                return;
            }
        }
    }

    // 输出结果
    for (int i = 0; i < vexCounts; ++i) {
        if (i != start) {
            std::cout << start  << " -> " << i << ": ";
            std::vector<int> path;
            int cur = i;
            while (cur != start) {
                path.push_back(cur);
                cur = parent[cur];
            }
            std::cout << start;
            for (int j = path.size() - 1; j >= 0; --j) {
                std::cout << " -> " << path[j];
            }
            std::cout << ", 距离为 " << dist[i] << std::endl;
        }
    }
}

void Dantzig(unsigned int adjMat[][vexCounts] ,UINT start ) {
    std::vector<int> dist(vexCounts, INFINITE);
    std::vector<bool> visited(vexCounts, false);
    std::vector<int> prev(vexCounts, -1);

    dist[start] = 0;

    for (UINT i = 0; i < vexCounts; i++) {
        // Find the vertex with the minimum distance
        int u = -1;
        for (UINT j = 0; j < vexCounts; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INFINITE) {
            break;
        }

        visited[u] = true;

        // Update distances to neighboring vertices
        for (UINT v = 0; v < vexCounts; v++) {
            if (!visited[v] && adjMat[u][v] != INFINITE && dist[u] + adjMat[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMat[u][v];
                prev[v] = u;
            }
        }
    }

    // Output the results
    for (UINT i = 0; i < vexCounts; i++) {
        if (i != start) {
            std::cout << start << " -> " << i << ": ";
            if (dist[i] == INFINITE) {
                std::cout << "不可达" << std::endl;
            } else {
                std::cout << start;
                for (int v = i; prev[v] != -1; v = prev[v]) {
                    std::cout << " -> " << prev[v];
                }
                std::cout << ", 距离为 " << dist[i] << std::endl;
            }
        }
    }
}