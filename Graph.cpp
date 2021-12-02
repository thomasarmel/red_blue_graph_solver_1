#include <iostream>
#include <algorithm>
#include <queue>
#include <tuple>
#include "Graph.h"
#include "Node.h"

Graph::Graph(size_t maxCapacity) : _maxCapacity(maxCapacity)
{
    _nodes.resize(maxCapacity, nullptr);
}


Node *Graph::createNode(const Graph::Color &color, size_t id)
{
    if (nodeExists(id))
    {
        throw GraphModificationException("Node already exists");
    }
    if (id >= _maxCapacity)
    {
        throw GraphModificationException("Node id is out of bounds");
    }
    _size++;
    _nodes[id] = new Node(this, color, id);
    return _nodes[id];
}

std::ostream &operator<<(std::ostream &os, const Graph &graph)
{
    for (Node *node: graph._nodes)
    {
        if (node != nullptr)
        {
            os << *node << std::endl;
        }
    }
    return os;
}

Graph::~Graph()
{
    for (Node *node: _nodes)
    {
        delete node;
    }
}

Graph::Graph(const Graph &otherGraph) : _maxCapacity(otherGraph._maxCapacity), _size(otherGraph._size)
{
    _nodes.resize(otherGraph._nodes.size());
    for (size_t i = 0; i < _nodes.size(); ++i)
    {
        if (otherGraph._nodes[i] == nullptr)
        {
            continue;
        }
        _nodes[i] = new Node(this, otherGraph.getNode(i));
    }
}

Node &Graph::getNode(size_t id) const
{
    return *_nodes[id];
}

void Graph::removeNode(size_t id)
{
    if (!nodeExists(id))
    {
        throw GraphModificationException("Node does not exist");
    }
    Node *nodeToDelete = _nodes[id];
    nodeToDelete->propagateColorToNeighbors();
    for (auto &_node: _nodes)
    {
        if (_node == nullptr)
        {
            continue;
        }
        try
        {
            _node->removeNeighbor(id);
        }
        catch (std::exception &e)
        {
            // Ignore exception here
        }
    }
    _nodes[id] = nullptr;
    delete nodeToDelete;
    _size--;
}

bool Graph::nodeExists(size_t id) const
{
    return _nodes[id] != nullptr;
}

[[maybe_unused]] bool Graph::isEmpty() const
{
    return _size == 0;
}

[[maybe_unused]] size_t Graph::getMaxCapacity() const
{
    return _maxCapacity;
}

[[maybe_unused]] size_t Graph::size() const
{
    return _size;
}

class QueueSequenceTupleComparator
{
public:
    bool operator()(const std::tuple<Graph, size_t, std::deque<size_t>> &t1,
                    const std::tuple<Graph, size_t, std::deque<size_t>> &t2) const
    {
        return std::get<1>(t1) < std::get<1>(t2);
    }
};

std::optional<std::deque<size_t>> Graph::getSequence(Graph::Color color, size_t k) const
{
    std::priority_queue<std::tuple<Graph, size_t, std::deque<size_t>>, std::vector<std::tuple<Graph, size_t, std::deque<size_t>>>, QueueSequenceTupleComparator> graphStatesQueue;
    graphStatesQueue.push(std::make_tuple(*this, 0, std::deque<size_t>()));
    while (!graphStatesQueue.empty())
    {
        auto[graph, alreadyRemoved, sequenceToDisplay] = graphStatesQueue.top();
        graphStatesQueue.pop();
        if (alreadyRemoved == k)
        {
            return sequenceToDisplay;
        }
        if (k > alreadyRemoved + graph.size())
        {
            continue;
        }
        for (size_t i = 0; i < graph._nodes.size(); ++i)
        {
            if (!graph._nodes[i])
            {
                continue;
            }
            bool goodColorHasBeenRemoved = graph._nodes[i]->getColor() == color;
            Graph graphCopy(graph);
            graphCopy.removeNode(i);
            sequenceToDisplay.push_back(i);
            graphStatesQueue.push(
                    std::make_tuple(graphCopy, (goodColorHasBeenRemoved ? alreadyRemoved + 1 : 0), sequenceToDisplay));
            sequenceToDisplay.pop_back();
        }
    }
    return std::nullopt;
}

std::pair<size_t, std::deque<size_t>> Graph::getSequenceMax(Graph::Color color) const
{
    std::priority_queue<std::tuple<Graph, size_t, std::deque<size_t>>, std::vector<std::tuple<Graph, size_t, std::deque<size_t>>>, QueueSequenceTupleComparator> graphStatesQueue;
    std::pair<size_t, std::deque<size_t>> sequenceMax;
    graphStatesQueue.push(std::make_tuple(*this, 0, std::deque<size_t>()));
    while (!graphStatesQueue.empty())
    {
        auto[graph, alreadyRemoved, sequenceToDisplay] = graphStatesQueue.top();
        graphStatesQueue.pop();
        for (size_t i = 0; i < graph._nodes.size(); ++i)
        {
            if (!graph._nodes[i])
            {
                continue;
            }
            bool goodColorHasBeenRemoved = graph._nodes[i]->getColor() == color;
            if(!goodColorHasBeenRemoved && ((graphStatesQueue.empty() || graph.size() <= std::get<1>(graphStatesQueue.top())) || graph.size() <= sequenceMax.first) )
            {
                if(sequenceToDisplay.size() > sequenceMax.second.size())
                {
                    sequenceMax = std::make_pair(alreadyRemoved, sequenceToDisplay);
                }
                continue;
            }
            Graph graphCopy(graph);
            graphCopy.removeNode(i);
            sequenceToDisplay.push_back(i);
            graphStatesQueue.push(
                    std::make_tuple(graphCopy, (goodColorHasBeenRemoved ? alreadyRemoved + 1 : 0), sequenceToDisplay));
            sequenceToDisplay.pop_back();
        }
    }
    return sequenceMax;
}

Graph &Graph::operator=(const Graph &other)
{
    for (auto &_node: _nodes)
    {
        if (_node != nullptr)
        {
            delete _node;
            _node = nullptr;
        }
    }
    _nodes.resize(other._nodes.size());
    _size = other._size;
    _maxCapacity = other._maxCapacity;
    for (size_t i = 0; i < _nodes.size(); ++i)
    {
        if (other._nodes[i] == nullptr)
        {
            continue;
        }
        _nodes[i] = new Node(this, other.getNode(i));
    }
    return *this;
}

/*bool operator==(const Graph &g1, const Graph &g2)
{
    return false;
}
*/