#ifndef RED_BLUE_GRAPH_SOLVER_1_GRAPH_H
#define RED_BLUE_GRAPH_SOLVER_1_GRAPH_H

#include <iosfwd>
#include <vector>
#include <list>
#include <exception>

class Node;

class Graph
{
public:
    enum class Color {
        RED,
        BLUE
    };
    Graph() = delete;
    Graph(size_t maxCapacity);
    Graph(const Graph &otherGraph);
    ~Graph();
    Graph& operator=(const Graph &other) = delete; // Useless here but could be implemented later
    Node *createNode(const Graph::Color &color, size_t id);
    bool nodeExists(size_t id) const;
    Node &getNode(size_t id) const;
    void removeNode(size_t id);
    bool isSequence(Color color, size_t k, size_t alreadyRemoved = 0, std::list<size_t> listToDisplay = std::list<size_t>(), size_t lastRemovedNode = 0) const;
    bool isEmpty() const;
    size_t getMaxCapacity() const;
    size_t size() const;
    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);

    class GraphModificationException : public std::exception
    {
    public:
        GraphModificationException(const std::string &message) : _message(message)
        {}
        const char *what() const noexcept override
        {
            return _message.c_str();
        }

    private:
        std::string _message;
    };

private:
    size_t _maxCapacity;
    size_t _size = 0;
    std::vector<Node*> _nodes;
};


#endif //RED_BLUE_GRAPH_SOLVER_1_GRAPH_H
