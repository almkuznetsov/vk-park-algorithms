#include "ArcGraph.h"


ArcGraph::ArcGraph(const IGraph &other_graph) {
    for (int i = 0; i < other_graph.VerticesCount(); i++) {
        std::vector<int> tmp = other_graph.GetNextVertices(i);
        for (auto &vert: tmp) {
            std::pair<int, int> temp(i, vert);
            graph.push_back(temp);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    std::pair<int, int> temp(from, to);
    graph.push_back(temp);
}

int ArcGraph::VerticesCount() const {
    std::unordered_set<int> tmp;
    for(auto& point : graph){
        tmp.insert(point.first);
        tmp.insert(point.second);
    }
    return tmp.size();
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for(auto& tmp : graph){
        if (tmp.first == vertex)
            result.push_back(tmp.second);
    }
    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for(auto& tmp : graph){
        if (tmp.second == vertex)
            result.push_back(tmp.first);
    }
    return result;
}

ArcGraph::~ArcGraph() {}