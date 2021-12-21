#ifndef RED_BLUE_GRAPH_SOLVER_1_FLATGRAPH_H
#define RED_BLUE_GRAPH_SOLVER_1_FLATGRAPH_H

#include <random>
#include "GraphInterface.h"

class FlatGraph
{
public:
    FlatGraph() = delete;
    explicit FlatGraph(size_t maxCapacity);
    FlatGraph(const FlatGraph &otherGraph) = default;
    FlatGraph &operator=(const FlatGraph &other) = default;
    ~FlatGraph() = default;

    void removeNode(size_t id);

    void generateRandom(double redNodeProbability = 0.5, double redEdgeProbability = 0.5, double leftDirectedEdgeProbability = 0.5);

    friend std::ostream &operator<<(std::ostream &os, const FlatGraph &graph);

private:
    struct FlatGraphNode
    {
        GraphInterface::Color color;
    };
    struct FlatGraphEdge
    {
        GraphInterface::Color color;
        bool isLeft;
    };

    size_t _maxCapacity;
    std::vector<std::optional<FlatGraphNode>> _nodes;
    std::vector<std::optional<FlatGraphEdge>> _edges;
    std::mt19937 _randomGenerator;
    std::default_random_engine _randomEngine;
};


#endif //RED_BLUE_GRAPH_SOLVER_1_FLATGRAPH_H
