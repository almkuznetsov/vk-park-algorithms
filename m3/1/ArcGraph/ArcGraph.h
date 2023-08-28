#ifndef ARCGRAPH_H
#define ARCGRAPH_H

#include "../IGraph.h"
#include <unordered_set>

class ArcGraph : public IGraph {
public:
    ArcGraph(int vertices_count);
    ArcGraph(const IGraph &other_graph);
    ~ArcGraph() override;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector< std::pair<int, int> > graph;
    int vertices_count;
};

#endif