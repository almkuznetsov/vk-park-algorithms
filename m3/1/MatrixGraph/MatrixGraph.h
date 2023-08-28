#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "../IGraph.h"

class MatrixGraph : public IGraph {
public:
    MatrixGraph(int vertices_count);
    MatrixGraph(const IGraph &other_graph);
    ~MatrixGraph() override;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector< std::vector<bool> > graph;
    int vertices_count;
};

#endif