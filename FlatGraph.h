#ifndef RED_BLUE_GRAPH_SOLVER_1_FLATGRAPH_H
#define RED_BLUE_GRAPH_SOLVER_1_FLATGRAPH_H

#include <random>
#include "GraphInterface.h"
#include <stack>

class FlatGraph
        {
        public:
            FlatGraph() = delete;
            explicit FlatGraph(size_t maxCapacity);
            FlatGraph(const FlatGraph &otherGraph) = default;
            FlatGraph &operator=(const FlatGraph &other) = default;
            ~FlatGraph() = default;

            [[nodiscard]] bool nodeExists(size_t id) const;

            [[nodiscard]] size_t getMaxCapacity() const;

            void createNode(const GraphInterface::Color &color, size_t id);

            void addEdge(size_t from, size_t to, const GraphInterface::Color &color);

            [[nodiscard]] std::vector<std::pair<GraphInterface::Color, size_t>> getNodeNeighbors(size_t nodeId) const;

            void removeNode(size_t nodeId);

            void generateRandom(double redNodeProbability = 0.5, double redEdgeProbability = 0.5, double leftDirectedEdgeProbability = 0.5);

            [[nodiscard]] std::vector<size_t> getSequenceMax(const GraphInterface::Color &color, bool trace = false) const;

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

            [[nodiscard]] bool isColor(size_t nodeId, size_t edgeId, const GraphInterface::Color &color/*, bool leftOrRight*/) const;

            [[nodiscard]] bool edgeExists(size_t id) const;

            [[nodiscard]] bool mayBeInterestingToRemove(size_t nodeId, const GraphInterface::Color &color, bool leftOrRight) const;

            void setColor(size_t i, const GraphInterface::Color& color);

            void findNodesToRemoveBeforeUtil(FlatGraph &graphCopy, std::vector<size_t> &sequenceMax, size_t current,
                                     const GraphInterface::Color &color, bool leftOrRight, bool trace) const;
};

#endif //RED_BLUE_GRAPH_SOLVER_1_FLATGRAPH_H
