#include <iostream>
#include <string>
#include "Node.h"

Node::Node(Graph *parentGraph, Graph::Color color, size_t id) : _parentGraph(*parentGraph), _color(color), _id(id)
{
}

void Node::addNeighbor(Node *node, Graph::Color verticeColor)
{
    for (auto it = _neighbors.begin(); it != _neighbors.end(); ++it)
    {
        if (it->first == node->getId())
        {
            throw std::runtime_error("Node already exists");
        }
    }
    _neighbors.push_back(std::make_pair(node->_id, verticeColor));
}

void Node::addNeighbor(size_t nodeId, Graph::Color verticeColor)
{
    for (auto it = _neighbors.begin(); it != _neighbors.end(); ++it)
    {
        if (it->first == nodeId)
        {
            throw std::runtime_error("Node already exists");
        }
    }
    _neighbors.push_back(std::make_pair(nodeId, verticeColor));
}


std::ostream &operator<<(std::ostream &os, const Node &node)
{
    os << "Node " << node._id << " (" << (node._color == Graph::Color::RED ? "RED" : "BLUE") <<"): " << std::endl;
    for (const std::pair<size_t, Graph::Color> &vertice : node._neighbors)
    {
        os << "\t--- " << (vertice.second == Graph::Color::RED ? "RED" : "BLUE") << " ---> Node " << node._parentGraph.getNode(vertice.first)._id << std::endl;
    }
    return os;
}

Graph::Color Node::getColor() const
{
    return _color;
}

size_t Node::getId() const
{
    return _id;
}

std::vector<std::pair<size_t, Graph::Color>> Node::getNeighbors() const
{
    return _neighbors;
}

void Node::removeNeighbor(size_t nodeId)
{
    for (auto it = _neighbors.begin(); it != _neighbors.end(); ++it)
    {
        if (it->first == nodeId)
        {
            _neighbors.erase(it);
            return;
        }
    }
    throw NodeModificationException("Node " + std::to_string(_id) + " does not have a neighbor with id " + std::to_string(nodeId));
}

void Node::setColor(Graph::Color color)
{
    _color = color;
}

void Node::propagateColorToNeighbors()
{
    for (const std::pair<size_t, Graph::Color> &neighbor : _neighbors)
    {
        if(!_parentGraph.nodeExists(neighbor.first))
        {
            continue;
        }
        Node &node = _parentGraph.getNode(neighbor.first);
        node.setColor(neighbor.second);
    }
}
