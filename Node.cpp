#include <iostream>
#include <string>
#include "Node.h"

Node::Node(Graph *parentGraph, GraphInterface::Color color, size_t id) : _parentGraph(*parentGraph), _color(color), _id(id)
{
}

Node::Node(Graph *parentGraph, const Node &nodeToCopy) : _parentGraph(*parentGraph), _color(nodeToCopy._color),
                                                         _id(nodeToCopy._id), _neighbors(nodeToCopy._neighbors)
{
}


void Node::addNeighbor(Node *node, GraphInterface::Color verticeColor)
{
    if (_neighbors.find(node->getId()) != _neighbors.end())
    {
        throw std::runtime_error("Node already exists");
    }
    _neighbors.insert(std::pair<size_t, GraphInterface::Color>(node->getId(), verticeColor));
}

void Node::addNeighbor(size_t nodeId, GraphInterface::Color verticeColor)
{
    if (_neighbors.find(nodeId) != _neighbors.end())
    {
        throw std::runtime_error("Node already exists");
    }
    _neighbors.insert(std::pair<size_t, GraphInterface::Color>(nodeId, verticeColor));
}


std::ostream &operator<<(std::ostream &os, const Node &node)
{
    os << "Node " << node._id << " (" << (node._color == GraphInterface::Color::RED ? "RED" : "BLUE") << "): " << std::endl;
    for (const std::pair<size_t, GraphInterface::Color> &vertice: node._neighbors)
    {
        os << "\t--- " << (vertice.second == GraphInterface::Color::RED ? "RED" : "BLUE") << " ---> Node "
           << node._parentGraph.getNode(vertice.first)._id << std::endl;
    }
    return os;
}

GraphInterface::Color Node::getColor() const
{
    return _color;
}

size_t Node::getId() const
{
    return _id;
}

std::map<size_t, GraphInterface::Color> Node::getNeighbors() const
{
    return _neighbors;
}

void Node::removeNeighbor(size_t nodeId)
{
    auto neighborPos = _neighbors.find(nodeId);
    if (neighborPos == _neighbors.end())
    {
        throw NodeModificationException(
                "Node " + std::to_string(_id) + " does not have a neighbor with id " + std::to_string(nodeId));
    }
    _neighbors.erase(neighborPos);
}

void Node::setColor(GraphInterface::Color color)
{
    _color = color;
}

void Node::propagateColorToNeighbors()
{
    for (const std::pair<size_t, GraphInterface::Color> &neighbor: _neighbors)
    {
        if (!_parentGraph.nodeExists(neighbor.first))
        {
            continue;
        }
        Node &node = _parentGraph.getNode(neighbor.first);
        node.setColor(neighbor.second);
    }
}

bool operator==(const Node &n1, const Node &n2)
{
    return n1._id == n2._id && n1._color == n2._color && n1._neighbors == n2._neighbors;
}

bool operator!=(const Node &n1, const Node &n2)
{
    return n1._id != n2._id || n1._color != n2._color || n1._neighbors != n2._neighbors;
}
