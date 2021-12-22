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

void FlatGraph::removeNode(size_t nodeId)
{
    if(!nodeExists(nodeId))
    {
        throw GraphInterface::GraphModificationException("Node does not exist.");
    }
    std::vector<std::pair<GraphInterface::Color, size_t>> neighbours = getNodeNeighbors(nodeId);
    for(const std::pair<GraphInterface::Color, size_t> &neighbour : neighbours)
    {
        _nodes[neighbour.second]->color = neighbour.first;
    }
    if(nodeId > 0)
    {
        _edges[nodeId - 1] = std::nullopt;
    }
    if(nodeId < _maxCapacity - 1)
    {
        _edges[nodeId] = std::nullopt;
    }
    _nodes[nodeId] = std::nullopt;
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

bool FlatGraph::nodeExists(size_t id) const
{
    return id < _maxCapacity && _nodes[id].has_value();
}

std::vector<std::pair<GraphInterface::Color, size_t>> FlatGraph::getNodeNeighbors(size_t nodeId) const
{
    if(!nodeExists(nodeId))
    {
        throw GraphInterface::GraphModificationException("Node does not exist.");
    }
    std::vector<std::pair<GraphInterface::Color, size_t>> neighbors;
    if(nodeExists(nodeId + 1) && _edges[nodeId].has_value() && !_edges[nodeId].value().isLeft)
    {
        neighbors.emplace_back(_edges[nodeId].value().color, nodeId + 1);
    }
    if(nodeId > 0 && nodeExists(nodeId - 1) && _edges[nodeId - 1].has_value() && _edges[nodeId - 1].value().isLeft)
    {
        neighbors.emplace_back(_edges[nodeId - 1].value().color, nodeId - 1);
    }
    return neighbors;
}

void FlatGraph::createNode(const GraphInterface::Color &color, size_t id)
{
    if(id > _maxCapacity)
    {
        throw GraphInterface::GraphModificationException("Node id is too big.");
    }
    if(nodeExists(id))
    {
        throw GraphInterface::GraphModificationException("Node already exists.");
    }
    _nodes[id] = FlatGraphNode{color};
}

void FlatGraph::addEdge(size_t from, size_t to, const GraphInterface::Color &color)
{
    if(!nodeExists(from) || !nodeExists(to))
    {
        throw GraphInterface::GraphModificationException("Node does not exist.");
    }
    if(from - to != 1 && to - from != 1)
    {
        throw GraphInterface::GraphModificationException("Nodes are not adjacent.");
    }
    size_t edgeId = std::min(from, to);
    if(_edges[edgeId].has_value())
    {
        throw GraphInterface::GraphModificationException("Edge already exists.");
    }
    bool isLeft = (from - to == 1);
    _edges[edgeId] = FlatGraphEdge{color, isLeft};
}
