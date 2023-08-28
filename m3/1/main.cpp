/*
Необходимо написать несколько реализаций интерфейса:
ListGraph, хранящий граф в виде массива списков смежности,
MatrixGraph, хранящий граф в виде матрицы смежности,
SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
ArcGraph, хранящий граф в виде одного массива пар {from, to}.
Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.
*/
#include "ArcGraph/ArcGraph.h"
#include "ListGraph/ListGraph.h"
#include "MatrixGraph/MatrixGraph.h"
#include "SetGraph/SetGraph.h"
#include <queue>

void dfs_aux(const IGraph &graph, std::vector<bool> &visited,  int v, void (*callback)(int v)) {
    visited[v] = true;
    callback(v);

    std::vector<int> children = graph.GetNextVertices(v);
    for (int i = 0; i < children.size(); ++i) {
        if (!visited[i]) {
            dfs_aux(graph, visited, children[i], callback);
        }
    }
}

void dfs(const IGraph &graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            dfs_aux(graph, visited, i, callback);
        }
    }
}

void bfs(const IGraph &graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> q;

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            visited[i] = true;
            q.push(i);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                callback(v);
                std::vector<int> children = graph.GetNextVertices(v);
                for (int child : children) {
                    if (!visited[child]) {
                        visited[child] = true;
                        q.push(child);
                    }
                }
            }
        }
    }
}

int main() {
    IGraph *list = new ListGraph(8);
    list->AddEdge(0, 1);
    list->AddEdge(1, 3);
    list->AddEdge(3, 6);
    list->AddEdge(6, 7);
    list->AddEdge(0, 2);
    list->AddEdge(2, 4);
    list->AddEdge(4, 5);
    list->AddEdge(5, 7);
    list->AddEdge(7, 0);
    IGraph *matrix = new MatrixGraph(*list);
    IGraph *set = new SetGraph(*matrix);
    IGraph *arc = new ArcGraph(*set);

    std::cout << "--ListGraph--" << std::endl;
    std::cout << "--DFS--" << std::endl;

    dfs(*list, [](int v) {
        std::cout << v << std::endl;
    });

    std::cout << "--BFS--" << std::endl;

    bfs(*list, [](int v) {
        std::cout << v << std::endl;
    });

    std::cout << "--MatrixGraph--" << std::endl;
    std::cout << "--DFS--" << std::endl;

    dfs(*matrix, [](int v) {
        std::cout << v << std::endl;
    });

    std::cout << "--BFS--" << std::endl;

    bfs(*matrix, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "--SetGraph--" << std::endl;
    std::cout << "--DFS--" << std::endl;

    dfs(*set, [](int v) {
        std::cout << v << std::endl;
    });

    std::cout << "--BFS--" << std::endl;

    bfs(*set, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "--ArcGraph--" << std::endl;
    std::cout << "--DFS--" << std::endl;

    dfs(*arc, [](int v) {
        std::cout << v << std::endl;
    });

    std::cout << "--BFS--" << std::endl;

    bfs(*arc, [](int v) {
        std::cout << v << std::endl;
    });

    delete list;
    delete matrix;
    delete set;
    delete arc;

    return 0;
}