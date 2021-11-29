#include <iostream>
#include <algorithm>
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

bool Graph::isSequence(Graph::Color color, size_t k, size_t alreadyRemoved, std::list<size_t> listToDisplay, size_t lastRemovedNode) const
{
    //std::cout << *this << std::endl;
    if(lastRemovedNode)
    {
        listToDisplay.push_back(lastRemovedNode);
    }
    if(alreadyRemoved == k)
    {
        std::cout << "list: ";
        std::for_each(listToDisplay.begin(), listToDisplay.end(), [](size_t &id) {
            std::cout << id << " ";
        });
        std::cout << std::endl;
        return true;
    }
    if(isEmpty())
    {
        return false;
    }
    for(size_t i = 0; i < _nodes.size(); ++i)
    {
        if(_nodes[i] == nullptr)
        {
            continue;
        }
        Graph graphCopy(*this);
        //std::cout << graphCopy.size() << " " << alreadyRemoved << std::endl;
        bool goodColorHasBeenRemoved = _nodes[i]->getColor() == color;
        graphCopy.removeNode(i);
        if(graphCopy.isSequence(color, k, (goodColorHasBeenRemoved ? alreadyRemoved + 1 : 0), listToDisplay, i))
        {
            return true;
        }
    }
    return false;
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
