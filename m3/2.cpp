/*
Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. 
Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).
*/
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

class ListGraph {
public:
    ListGraph(int vertices_count) {
        graph.resize(vertices_count);
    };

    ~ListGraph() {};

    void AddEdge(int from, int to) {
        graph[from].push_back(to);;
        graph[to].push_back(from);;
    };

    int VerticesCount() const {
        return graph.size();
    };

    std::vector<int> GetNextVertices(int vertex) const {
        std::vector<int> result(graph[vertex].begin(), graph[vertex].end());
        return result;
    };

private:
    std::vector<std::vector<int>> graph;
};

int shortest(const ListGraph &graph, int u, int w) {
    std::vector<int> waySize(graph.VerticesCount(), std::numeric_limits<int>::max() - 1);
    std::vector<int> shortestWaysCount(graph.VerticesCount(), 0);

    std::queue<int> q;
    q.push(u);
    waySize[u] = 0;
    shortestWaysCount[u] = 1;

    while (!q.empty()){
        int cur = q.front();
        q.pop();
        std::vector<int> children = graph.GetNextVertices(cur);
        for (int child : children) {
            if (waySize[child] == waySize[cur] + 1){
                shortestWaysCount[child] += shortestWaysCount[cur];
            } else if (waySize[child] > waySize[cur] + 1){
                waySize[child] = waySize[cur] + 1;
                shortestWaysCount[child] = shortestWaysCount[cur];
                q.push(child);
            }
        }
    }
    return shortestWaysCount[w];
}


int main() {
    int v = 0 ;
    int n = 0;
    std::cin >> v >> n;
    ListGraph list = ListGraph(v);

    int from = 0; 
    int to = 0;;

    for (int i = 0; i < n; i++) {
        std::cin >> from >> to;
        list.AddEdge(from, to);
    }

    int u = 0;
    int w = 0;
    std::cin >> u >> w;
    std::cout << shortest(list, u, w);
    return 0;
}