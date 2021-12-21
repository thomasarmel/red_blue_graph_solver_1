#ifndef RED_BLUE_GRAPH_SOLVER_1_GRAPH_H
#define RED_BLUE_GRAPH_SOLVER_1_GRAPH_H

#include <iosfwd>
#include <vector>
#include <deque>
#include <exception>
#include <optional>
#include <memory>

class Node;

class Graph
{
public:
    enum class Color
    {
        RED,
        BLUE
    };

    Graph() = delete;

    explicit Graph(size_t maxCapacity);

    Graph(const Graph &otherGraph);

    ~Graph() = default;

    Graph &operator=(const Graph &other);

    void createNode(const Graph::Color &color, size_t id);

    void addEdge(size_t from, size_t to, const Graph::Color &color);

    [[nodiscard]] bool nodeExists(size_t id) const;

    [[nodiscard]] Node &getNode(size_t id) const;

    void removeNode(size_t id);

    [[nodiscard]] std::optional<std::deque<size_t>> getSequence(Color color, size_t k) const;

    [[nodiscard]] std::pair<size_t, std::deque<size_t>> getSequenceMax(Color color) const;

    [[maybe_unused]] [[nodiscard]] bool isEmpty() const;

    [[maybe_unused]] [[nodiscard]] size_t getMaxCapacity() const;

    [[maybe_unused]] [[nodiscard]] size_t size() const;

    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);

    friend bool operator==(const Graph &g1, const Graph &g2);

    class GraphModificationException : public std::exception
    {
    public:
        explicit GraphModificationException(const std::string &message) : _message(message)
        {}

        [[nodiscard]] const char *what() const noexcept override
        {
            return _message.c_str();
        }

    private:
        std::string _message;
    };

private:
    size_t _maxCapacity;
    size_t _size = 0;
    std::vector<std::optional<std::unique_ptr<Node>>> _nodes;
};


#endif //RED_BLUE_GRAPH_SOLVER_1_GRAPH_H
