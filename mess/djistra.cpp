#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <iomanip>
using namespace std;

// 打印最短路径
void printPath(const vector<int>& prev, int start, int end) {
    vector<int> path;
    for (int at = end; at != -1; at = prev[at])
        path.push_back(at);
    reverse(path.begin(), path.end());

    if (path[0] != start) {
        cout << "从顶点v" << (start + 1) << "到顶点v" << (end + 1) << "没有路径" << endl;
        return;
    }

    cout << "从顶点v" << (start + 1) << "到顶点v" << (end + 1) << "的最短路径: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << "v" << (path[i] + 1);
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

// Dijkstra算法实现
vector<int> dijkstra(const vector<vector<int>>& graph, int start, vector<int>& prev) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    prev.assign(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0;

    for (int i = 0; i < n - 1; ++i) {
        // 找到未访问顶点中距离最小的
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }

        if (dist[u] == INT_MAX) break;

        visited[u] = true;

        // 更新相邻顶点的距离
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX) {
                int newDist = dist[u] + graph[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                }
            }
        }
    }

    return dist;
}

int main() {
    // 邻接矩阵表示有向网图
    vector<vector<int>> graph = {
        {0, 45, 15, 0, 15, 0},
        {0, 0, 10, 30, 15, 15},
        {10, 0, 0, 60, 0, 0},
        {0, 20, 0, 0, 0, 20},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };

    int startVertex = 0; // 对应v1
    vector<int> prev;
    vector<int> dist = dijkstra(graph, startVertex, prev);

    // 输出结果
    for (int i = 0; i < graph.size(); ++i) {
        if (i != startVertex) {
            printPath(prev, startVertex, i);
            cout << "最短距离: ";
            if (dist[i] == INT_MAX)
                cout << "∞" << endl;
            else
                cout << dist[i] << endl;
            cout << endl;
        }
    }

    return 0;
}