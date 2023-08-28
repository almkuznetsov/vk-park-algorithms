/*
Требуется отыскать самый выгодный маршрут между городами. 
Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
Формат входных данных.
Первая строка содержит число N – количество городов.
Вторая строка содержит число M - количество дорог.
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
Последняя строка содержит маршрут (откуда и куда нужно доехать).
Формат выходных данных.
Вывести длину самого выгодного маршрута.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <set>

class ListGraph {
public:
    ListGraph(int vertices_count) {
        graph.resize(vertices_count);
    };

    ~ListGraph() {};

    void AddEdge(int from, int to, int time) {
        graph[from].push_back((std::make_pair(to, time)));
        graph[to].push_back((std::make_pair(from, time)));
    };

    int VerticesCount() const {
        return graph.size();
    };

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const {
        std::vector<std::pair<int, int>> result(graph[vertex].begin(), graph[vertex].end());
        return result;
    };

private:
    std::vector<std::vector<std::pair<int, int>>> graph;
};

int shortestWay(const ListGraph &graph, int start, int end) {
    std::vector<int> visited(graph.VerticesCount(), std::numeric_limits<int>::max());
    std::queue<int> q;
    visited[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        std::vector<std::pair<int, int>> children = graph.GetNextVertices(cur);
        for (auto &child : children) {
            if (visited[child.first] > visited[cur] + child.second) {
                visited[child.first] = visited[cur] + child.second;
                q.push(child.first);
            }
        }
    }
    return visited[end];
}


int main() {
    int N = 0;
    int M = 0;
    std::cin >> N >> M;
    ListGraph list = ListGraph(N);

    int from = 0;
    int to = 0; 
    int time = 0;

    for (int i = 0; i < M; i++) {
        std::cin >> from >> to >> time;
        list.AddEdge(from, to, time);
    }

    int start, end;
    std::cin >> start >> end;
    std::cout << shortestWay(list, start, end);
    return 0;
}

