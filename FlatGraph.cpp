#include <iostream>
#include <chrono>
#include "FlatGraph.h"

FlatGraph::FlatGraph(size_t maxCapacity) : _maxCapacity(maxCapacity)
{
    _nodes.resize(maxCapacity);
    _edges.resize(maxCapacity - 1);
    size_t randomNumberGeneratorSeed = static_cast<size_t>(std::chrono::system_clock::now().time_since_epoch().count());
    _randomGenerator.seed(randomNumberGeneratorSeed);
    _randomEngine.seed(_randomGenerator());
}

void FlatGraph::removeNode(size_t id)
{
// TODO
}

void FlatGraph::generateRandom(double redNodeProbability, double redEdgeProbability, double leftDirectedEdgeProbability)
{
    std::uniform_real_distribution<float> distr(0, 1);
    std::transform(_nodes.begin(), _nodes.end(), _nodes.begin(), [this, &redNodeProbability, &distr](std::optional<FlatGraphNode> node) {
        FlatGraphNode flatGraphNode{};
        double randomNumber = distr(_randomEngine);
        if(randomNumber < redNodeProbability)
        {
            flatGraphNode.color = GraphInterface::Color::RED;
        }
        else
        {
            flatGraphNode.color = GraphInterface::Color::BLUE;
        }
        return flatGraphNode;
    });
    std::transform(_edges.begin(), _edges.end(), _edges.begin(), [this, &redEdgeProbability, &leftDirectedEdgeProbability, &distr](std::optional<FlatGraphEdge> edge) {
        FlatGraphEdge flatGraphEdge{};
        double randomNumber = distr(_randomEngine);
        if(randomNumber < redEdgeProbability)
        {
            flatGraphEdge.color = GraphInterface::Color::RED;
        }
        else
        {
            flatGraphEdge.color = GraphInterface::Color::BLUE;
        }
        randomNumber = distr(_randomEngine);
        if(randomNumber < leftDirectedEdgeProbability)
        {
            flatGraphEdge.isLeft = true;
        }
        else
        {
            flatGraphEdge.isLeft = false;
        }
        return flatGraphEdge;
    });
}

std::ostream &operator<<(std::ostream &os, const FlatGraph &graph)
{
    for (size_t i = 0; i < graph._maxCapacity; i++)
    {
        if(i > 0)
        {
            if(graph._edges[i - 1].has_value())
            {
                const FlatGraph::FlatGraphEdge &edge = graph._edges[i - 1].value();
                std::string edgeColor = (edge.color == GraphInterface::Color::RED ? "RED" : "BLUE");
                if(edge.isLeft)
                {
                    os << "<-" << edgeColor << "-";
                }
                else
                {
                    os << "-" << edgeColor << "->";
                }
            }
            else
            {
                os << "   ";
            }
        }
        if(graph._nodes[i].has_value())
        {
            os << "[" << (graph._nodes[i].value().color == GraphInterface::Color::RED ? "RED" : "BLUE") << "]";
        }
        else
        {
            os << "   ";
        }
    }
    return os;
}
