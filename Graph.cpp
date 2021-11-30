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
    if(nodeExists(id))
    {
        throw GraphModificationException("Node already exists");
    }
    if(id >= _maxCapacity)
    {
        throw GraphModificationException("Node id is out of bounds");
    }
    _size++;
    _nodes[id] = new Node(this, color, id);
    return _nodes[id];
}

std::ostream &operator<<(std::ostream &os, const Graph &graph)
{
    for (Node *node : graph._nodes)
    {
        if(node != nullptr)
        {
            os << *node << std::endl;
        }
    }
    return os;
}

Graph::~Graph()
{
    for (Node *node : _nodes)
    {
        delete node;
    }
}

Graph::Graph(const Graph &otherGraph) : _maxCapacity(otherGraph._maxCapacity)
{
    _nodes.resize(otherGraph._nodes.size());
    for (size_t i = 0; i < _nodes.size(); ++i)
    {
        if(otherGraph._nodes[i] == nullptr)
        {
            continue;
        }
        _nodes[i] = new Node(this, otherGraph.getNode(i).getColor(), otherGraph.getNode(i).getId());
        for(const std::pair<size_t, Graph::Color> &neighbor: otherGraph.getNode(i).getNeighbors())
        {
            _nodes[i]->addNeighbor(neighbor.first, neighbor.second);
        }
    }
}

Node &Graph::getNode(size_t id) const
{
    return *_nodes[id];
}

void Graph::removeNode(size_t id)
{
    if(!nodeExists(id))
    {
        throw GraphModificationException("Node does not exist");
    }
    Node *nodeToDelete = _nodes[id];
    nodeToDelete->propagateColorToNeighbors();
    for (size_t i = 0; i < _nodes.size(); ++i)
    {
        if(_nodes[i] == nullptr)
        {
            continue;
        }
        try
        {
            _nodes[i]->removeNeighbor(id);
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

bool Graph::isEmpty() const
{
    for (Node *node : _nodes)
    {
        if(node != nullptr)
        {
            return false;
        }
    }
    return true;
}

size_t Graph::getMaxCapacity() const
{
    return _maxCapacity;
}

size_t Graph::size() const
{
    return _size;
}

class QueueSequenceTupleComparator
{
public:
    bool operator()(const std::tuple<Graph, size_t, std::list<size_t>> &t1, const std::tuple<Graph, size_t, std::list<size_t>> &t2) const
    {
        return std::get<1>(t1) < std::get<1>(t2);
    }
};

std::optional<std::list<size_t>> Graph::getSequence(Graph::Color color, size_t k) const
{
    std::priority_queue<std::tuple<Graph, size_t, std::list<size_t>>, std::vector<std::tuple<Graph, size_t, std::list<size_t>>>, QueueSequenceTupleComparator> queue;
    queue.push(std::make_tuple(*this, 0, std::list<size_t>()));
    while(!queue.empty())
    {
        auto [graph, alreadyRemoved, listToDisplay] = queue.top();
        queue.pop();
        if(alreadyRemoved == k)
        {
            return listToDisplay;
        }
        for(size_t i = 0; i < graph._nodes.size(); ++i)
        {
            if(!graph._nodes[i])
            {
                continue;
            }
            bool goodColorHasBeenRemoved = graph._nodes[i]->getColor() == color;
            Graph graphCopy(graph);
            graphCopy.removeNode(i);
            listToDisplay.push_back(i);
            queue.push(std::make_tuple(graphCopy, (goodColorHasBeenRemoved ? alreadyRemoved + 1 : 0), listToDisplay));
            listToDisplay.pop_back();
        }
    }
    return std::nullopt;
}

Graph &Graph::operator=(const Graph &other)
{
    for (size_t i=0; i<_nodes.size(); ++i)
    {
        if(_nodes[i] != nullptr)
        {
            delete _nodes[i];
            _nodes[i] = nullptr;
        }
    }
    _nodes.resize(other._nodes.size());
    _size = other._size;
    _maxCapacity = other._maxCapacity;
    for (size_t i = 0; i < _nodes.size(); ++i)
    {
        if(other._nodes[i] == nullptr)
        {
            continue;
        }
        _nodes[i] = new Node(this, other.getNode(i).getColor(), other.getNode(i).getId());
        for(const std::pair<size_t, Graph::Color> &neighbor: other.getNode(i).getNeighbors())
        {
            _nodes[i]->addNeighbor(neighbor.first, neighbor.second);
        }
    }
    return *this;
}

/*bool operator==(const Graph &g1, const Graph &g2)
{
    return false;
}
*/