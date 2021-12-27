#include <iostream>
#include <chrono>
#include <list>
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
    if (!nodeExists(nodeId))
    {
        throw GraphInterface::GraphModificationException("Node does not exist.");
    }
    std::vector<std::pair<GraphInterface::Color, size_t>> neighbours = getNodeNeighbors(nodeId);
    for (const std::pair<GraphInterface::Color, size_t> &neighbour: neighbours)
    {
        _nodes[neighbour.second]->color = neighbour.first;
    }
    if (nodeId > 0)
    {
        _edges[nodeId - 1] = std::nullopt;
    }
    if (nodeId < _maxCapacity - 1)
    {
        _edges[nodeId] = std::nullopt;
    }
    _nodes[nodeId] = std::nullopt;
    _size--;
}

void FlatGraph::generateRandom(double redNodeProbability, double redEdgeProbability, double leftDirectedEdgeProbability)
{
    std::uniform_real_distribution<float> distr(0, 1);
    std::transform(_nodes.begin(), _nodes.end(), _nodes.begin(),
                   [this, &redNodeProbability, &distr](std::optional<FlatGraphNode> node) {
                       FlatGraphNode flatGraphNode{};
                       double randomNumber = distr(_randomEngine);
                       if (randomNumber < redNodeProbability)
                       {
                           flatGraphNode.color = GraphInterface::Color::RED;
                       } else
                       {
                           flatGraphNode.color = GraphInterface::Color::BLUE;
                       }
                       return flatGraphNode;
                   });
    std::transform(_edges.begin(), _edges.end(), _edges.begin(),
                   [this, &redEdgeProbability, &leftDirectedEdgeProbability, &distr](
                           std::optional<FlatGraphEdge> edge) {
                       FlatGraphEdge flatGraphEdge{};
                       double randomNumber = distr(_randomEngine);
                       if (randomNumber < redEdgeProbability)
                       {
                           flatGraphEdge.color = GraphInterface::Color::RED;
                       } else
                       {
                           flatGraphEdge.color = GraphInterface::Color::BLUE;
                       }
                       randomNumber = distr(_randomEngine);
                       if (randomNumber < leftDirectedEdgeProbability)
                       {
                           flatGraphEdge.isLeft = true;
                       } else
                       {
                           flatGraphEdge.isLeft = false;
                       }
                       return flatGraphEdge;
                   });
    _size = _maxCapacity;
}

std::ostream &operator<<(std::ostream &os, const FlatGraph &graph)
{
    for (size_t i = 0; i < graph._maxCapacity; i++)
    {
        if (i > 0)
        {
            if (graph._edges[i - 1].has_value())
            {
                const FlatGraph::FlatGraphEdge &edge = graph._edges[i - 1].value();
                std::string edgeColor = (edge.color == GraphInterface::Color::RED ? "RED" : "BLUE");
                if (edge.isLeft)
                {
                    os << "<-" << edgeColor << "-";
                } else
                {
                    os << "-" << edgeColor << "->";
                }
            } else
            {
                os << "   ";
            }
        }
        if (graph._nodes[i].has_value())
        {
            os << "[" << (graph._nodes[i].value().color == GraphInterface::Color::RED ? "RED" : "BLUE") << "]";
        } else
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

bool FlatGraph::edgeExists(size_t id) const
{
    return id < _maxCapacity - 1 && _edges[id].has_value();
}

std::vector<std::pair<GraphInterface::Color, size_t>> FlatGraph::getNodeNeighbors(size_t nodeId) const
{
    if (!nodeExists(nodeId))
    {
        throw GraphInterface::GraphModificationException("Node does not exist.");
    }
    std::vector<std::pair<GraphInterface::Color, size_t>> neighbors;
    if (nodeExists(nodeId + 1) && _edges[nodeId].has_value() && !_edges[nodeId].value().isLeft)
    {
        neighbors.emplace_back(_edges[nodeId].value().color, nodeId + 1);
    }
    if (nodeId > 0 && nodeExists(nodeId - 1) && _edges[nodeId - 1].has_value() && _edges[nodeId - 1].value().isLeft)
    {
        neighbors.emplace_back(_edges[nodeId - 1].value().color, nodeId - 1);
    }
    return neighbors;
}

void FlatGraph::createNode(const GraphInterface::Color &color, size_t id)
{
    if (id > _maxCapacity)
    {
        throw GraphInterface::GraphModificationException("Node id is too big.");
    }
    if (nodeExists(id))
    {
        throw GraphInterface::GraphModificationException("Node already exists.");
    }
    _nodes[id] = FlatGraphNode{color};
    _size++;
}

void FlatGraph::addEdge(size_t from, size_t to, const GraphInterface::Color &color)
{
    if (!nodeExists(from) || !nodeExists(to))
    {
        throw GraphInterface::GraphModificationException("Node does not exist.");
    }
    if (from - to != 1 && to - from != 1)
    {
        throw GraphInterface::GraphModificationException("Nodes are not adjacent.");
    }
    size_t edgeId = std::min(from, to);
    if (_edges[edgeId].has_value())
    {
        throw GraphInterface::GraphModificationException("Edge already exists.");
    }
    bool isLeft = (from - to == 1);
    _edges[edgeId] = FlatGraphEdge{color, isLeft};
}

size_t FlatGraph::getMaxCapacity() const
{
    return _maxCapacity;
}

bool FlatGraph::isColor(size_t nodeId, size_t edgeId, const GraphInterface::Color &color/*, bool leftOrRight*/) const
{
    return this->nodeExists(nodeId)
           && this->_nodes[nodeId]->color == color
           && this->edgeExists(edgeId)
           && _edges[edgeId]->color == color;
}

bool FlatGraph::mayBeInterestingToRemove(size_t nodeId, const GraphInterface::Color &color, bool leftOrRight) const
{
    size_t edgeId = leftOrRight ? nodeId - 1 : nodeId;
    if (!this->edgeExists(edgeId))
    {
        return false;
    }
    if ((leftOrRight && !_edges[edgeId]->isLeft) || !leftOrRight && _edges[edgeId]->isLeft)
    {
        return false;
    }
    size_t nodeDestId = leftOrRight ? nodeId - 1 : nodeId + 1;
    return isColor(nodeId, edgeId, color)
           && nodeExists(nodeDestId) && _nodes[nodeDestId]->color != color;
}

void FlatGraph::setColor(size_t i, const GraphInterface::Color &color)
{
    if (!this->nodeExists(i))
    {
        throw GraphInterface::GraphModificationException("Node does not exist.");
    }
    this->_nodes[i]->color = color;
}

void
FlatGraph::sequenceMaxPushAndRemoveUtil(FlatGraph &graphCopy, std::deque<size_t> &sequenceMaxRed, size_t current) const
{
    sequenceMaxRed.push_back(current);
    graphCopy.removeNode(current); // May be useless with a stack
}

void FlatGraph::findNodesToRemoveBeforeUtil(FlatGraph &graphCopy, std::deque<size_t> &sequenceMax, size_t current,
                                            const GraphInterface::Color &color, bool leftOrRight) const
{
    const std::function<bool(size_t, size_t)> EDGES_LEFT_OR_RIGHT = [&graphCopy](size_t leftOrRight, size_t edgeId) {
        return (leftOrRight) != 0 == graphCopy._edges[edgeId]->isLeft;
    };
    const std::function<bool(size_t, size_t, size_t)> BACK_EDGES_COMPARE_CURRENT = [](size_t leftOrRight,
                                                                                      size_t currentTemp,
                                                                                      size_t current) {
        return ((leftOrRight) ? (currentTemp) < (current) : (currentTemp) > (current));
    };
    size_t currentTemp = leftOrRight ? current - 1 : current + 1;
    size_t edgeId = leftOrRight ? current - 1 : current;
    while (true)
    {
        if (graphCopy.nodeExists(currentTemp) && graphCopy._nodes[currentTemp]->color == color
            && graphCopy.edgeExists(edgeId) && EDGES_LEFT_OR_RIGHT(leftOrRight, edgeId))
        {
            leftOrRight ? currentTemp-- : currentTemp++;
            leftOrRight ? edgeId-- : edgeId++;
        } else
        {
            leftOrRight ? currentTemp += 1 : currentTemp -= 1;
            leftOrRight ? edgeId += 1 : edgeId -= 1;
            while (BACK_EDGES_COMPARE_CURRENT(leftOrRight, currentTemp, current))
            {
                sequenceMaxPushAndRemoveUtil(graphCopy, sequenceMax, currentTemp);
                leftOrRight ? currentTemp++ : currentTemp--;
                leftOrRight ? edgeId++ : edgeId--;
            }
            break;
        }
    }
}

std::deque<size_t> FlatGraph::getSequenceMax(const GraphInterface::Color &color) const
{
    FlatGraph graphCopy(*this);
    std::deque<size_t> sequenceMax;
    size_t current = 0;
    while (current < graphCopy.getMaxCapacity())
    {
        if (graphCopy.mayBeInterestingToRemove(current, color, false))
        {
            if (graphCopy.mayBeInterestingToRemove(current, color, true))
            {
                sequenceMaxPushAndRemoveUtil(graphCopy, sequenceMax, current);
                current--;
            } else
            {
                findNodesToRemoveBeforeUtil(graphCopy, sequenceMax, current, color, true);
                sequenceMaxPushAndRemoveUtil(graphCopy, sequenceMax, current);
                current++;
            }
        } else
        {
            if (graphCopy.mayBeInterestingToRemove(current, color, true))
            {
                findNodesToRemoveBeforeUtil(graphCopy, sequenceMax, current, color, false);
                sequenceMaxPushAndRemoveUtil(graphCopy, sequenceMax, current);
                current--;
            } else
            {
                if (graphCopy.nodeExists(current) && graphCopy._nodes[current]->color == color)
                {
                    findNodesToRemoveBeforeUtil(graphCopy, sequenceMax, current, color, false);
                    sequenceMaxPushAndRemoveUtil(graphCopy, sequenceMax, current);
                }
                current++;
            }
        }
    }
    current = 0;
    while (current < graphCopy.getMaxCapacity())
    {
        if (graphCopy.nodeExists(current) && graphCopy._nodes[current]->color == color)
        {
            sequenceMax.push_back(current);
            graphCopy.removeNode(current); // May be useless with a stack
        }
        current++;
    }
    return sequenceMax;
}

bool FlatGraph::isEmpty() const
{
    return _size == 0;
}

size_t FlatGraph::size() const
{
    return _size;
}

std::deque<size_t> FlatGraph::getSequenceMaxBis(const GraphInterface::Color &color) const
{
    std::list<size_t> sequenceMax;
    for (size_t i = 0; i < _size; i++)
    {
        if (_nodes[i].has_value())
        {
            sequenceMax.emplace_back(i);
        }
    }
    long long alreadyParsed = 0;
    for(size_t i = 0; i < _size; i++)
    {
        std::list<size_t>::iterator itToMove = std::prev(sequenceMax.end(), 1);
        std::list<size_t>::iterator itDestination = std::next(sequenceMax.begin(), alreadyParsed);
        while (itDestination != sequenceMax.begin() && !shouldBeRemovedBefore(*(std::prev(itDestination, 1)), *itToMove, color))
        {
            itDestination--;
        }
        sequenceMax.splice(itDestination, sequenceMax, itToMove);
        alreadyParsed++;
        /*for (auto node : sequenceMax)
        {
            std::cout << node << " ";
        }
        std::cout << std::endl;*/
    }
    std::deque<size_t> sequenceMaxDeque;
    FlatGraph graphCopy(*this);
    for(auto it = sequenceMax.begin(); it != sequenceMax.end(); it++)
    {
        if(graphCopy.nodeExists(*it) && graphCopy._nodes[*it]->color == color)
        {
            sequenceMaxDeque.push_back(*it);
            graphCopy.removeNode(*it);
        }
    }
    return sequenceMaxDeque;
}

bool FlatGraph::shouldBeRemovedBefore(size_t first, size_t second, const GraphInterface::Color &color) const
{
    int diff = first - second;
    if (!nodeExists(first) || !nodeExists(second))
    {
        return false;
    }
    switch (diff)
    {
        case -1: // first a gauche de second
            if (!edgeExists(first))
            {
                return false;
            }
            // first donne bonne couleur a second
            if (!_edges[first]->isLeft && _nodes[second]->color != color && _edges[first]->color == color)
            {
                return true;
            }
            // second donne mauvaise couleur a first
            if (_edges[first]->isLeft && _nodes[first]->color == color && _edges[first]->color != color)
            {
                return true;
            }
            break;
        case 1: // first a droite de second
            if (!edgeExists(second))
            {
                return false;
            }
            // first donne bonne couleur a second
            if (_edges[second]->isLeft && _nodes[second]->color != color && _edges[second]->color == color)
            {
                return true;
            }
            // second donne mauvaise couleur a first
            if (!_edges[second]->isLeft && _nodes[first]->color == color && _edges[second]->color != color)
            {
                return true;
            }
            break;
    }
    return false;
}
