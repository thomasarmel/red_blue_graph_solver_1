#ifndef RED_BLUE_GRAPH_SOLVER_1_NODE_H
#define RED_BLUE_GRAPH_SOLVER_1_NODE_H

#include "Graph.h"

#include <map>
#include <utility>
#include <iosfwd>
#include <exception>

class Graph;

class Node
{
public:
    Node() = delete;
    Node(const Node&) = delete;
    ~Node() = default;

    class NodeModificationException : public std::exception
    {
    public:
        explicit NodeModificationException(const std::string &message) : _message(message)
        {
        }

        [[nodiscard]] const char *what() const noexcept override
        {
            return _message.c_str();
        }

    private:
        std::string _message;
    };

private:
    Node(Graph *parentGraph, GraphInterface::Color color, size_t id);
    Node(Graph *parentGraph, const Node &nodeToCopy);

    void addNeighbor(Node *node, GraphInterface::Color verticeColor);
    void addNeighbor(size_t nodeId, GraphInterface::Color verticeColor);
    void removeNeighbor(size_t nodeId);
    void setColor(GraphInterface::Color color);
    [[nodiscard]] GraphInterface::Color getColor() const;
    [[nodiscard]] size_t getId() const;
    void propagateColorToNeighbors();
    friend class Graph;
    [[nodiscard]] std::map<size_t, GraphInterface::Color> getNeighbors() const;
    friend std::ostream &operator<<(std::ostream &os, const Node &node);
    friend bool operator==(const Node &n1, const Node &n2);
    friend bool operator!=(const Node &n1, const Node &n2);

    Graph &_parentGraph;
    std::map<size_t, GraphInterface::Color> _neighbors;
    size_t _id;
    GraphInterface::Color _color;
};


#endif //RED_BLUE_GRAPH_SOLVER_1_NODE_H
