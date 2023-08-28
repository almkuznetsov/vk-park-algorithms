#include "SetGraph.h"

SetGraph::SetGraph(int vertices_count) {
    graph.resize(vertices_count);
}

SetGraph::SetGraph(const IGraph &other_graph) {
    graph.resize(other_graph.VerticesCount());
    for (int i = 0; i < other_graph.VerticesCount(); i++) {
        std::vector<int> tmp = other_graph.GetNextVertices(i);
        for (auto &vert: tmp) {
            graph[i].insert(vert);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    graph[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return graph.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (auto vert: graph[vertex]) {
        result.push_back(vert);
    }
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph.size(); i++)
        for (auto vert : graph[i]) {
            if (vert == vertex)
                result.push_back(i);
        }
    return result;
}

SetGraph::~SetGraph() {}