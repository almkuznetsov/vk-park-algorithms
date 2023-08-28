#include "ListGraph.h"

ListGraph::ListGraph(int vertices_count) {
    graph.resize(vertices_count);
}

ListGraph::ListGraph(const IGraph &other_graph) {
    graph.resize(other_graph.VerticesCount());
    for (int i = 0; i < other_graph.VerticesCount(); i++) {
        graph[i] = other_graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    graph[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return graph.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    result.reserve(graph[vertex].size());

    for (int i = 0; i < graph[vertex].size(); ++i) {
        result.push_back(graph[vertex][i]);
    }
    return result;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            if (j == vertex) {
                result.push_back(i); 
            }
        }
    }
}

ListGraph::~ListGraph() {}