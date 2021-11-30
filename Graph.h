#ifndef RED_BLUE_GRAPH_SOLVER_1_GRAPH_H
#define RED_BLUE_GRAPH_SOLVER_1_GRAPH_H

#include <iosfwd>
#include <vector>
#include <list>
#include <exception>
#include <optional>

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
    Graph& operator=(const Graph &other);
    Node *createNode(const Graph::Color &color, size_t id);
    bool nodeExists(size_t id) const;
    Node &getNode(size_t id) const;
    void removeNode(size_t id);
    std::optional<std::list<size_t>> getSequence(Color color, size_t k) const;
    bool isEmpty() const;
    size_t getMaxCapacity() const;
    size_t size() const;
    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
    //friend bool operator==(const Graph &g1, const Graph &g2); // TODO

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
