#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertices_count) {
    graph.resize(vertices_count);
    for (std::vector<bool> v : graph) {
        v.resize(vertices_count, false);
    }
}

MatrixGraph::MatrixGraph(const IGraph &other_graph) {
    graph.resize(other_graph.VerticesCount());
    for (int i = 0; i < other_graph.VerticesCount(); i++) {
        graph[i].resize(other_graph.VerticesCount(), false);
        for(auto &v : other_graph.GetNextVertices(i)){
            graph[i][v] = true;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    graph[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return graph.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for(int i = 0; i < graph[vertex].size(); i++){
        if (graph[vertex][i]){
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;

    for(int i = 0; i < graph.size(); i++){
        if (graph[i][vertex]){
            result.push_back(i);
        }
    }
    return result;
}

MatrixGraph::~MatrixGraph() {}