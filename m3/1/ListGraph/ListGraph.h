#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "../IGraph.h"

class ListGraph : public IGraph {
public:
    ListGraph(int vertices_count);
    ListGraph(const IGraph &other_graph);
    ~ListGraph() override;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector< std::vector<int> > graph;
    int vertices_count;
};

#endif