#ifndef RED_BLUE_GRAPH_SOLVER_1_GRAPHINTERFACE_H
#define RED_BLUE_GRAPH_SOLVER_1_GRAPHINTERFACE_H

#include <iostream>
#include <vector>
#include <optional>
#include <functional>
#include <deque>

class GraphInterface
{
public:
    enum class Color
    {
        RED,
        BLUE
    };

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

    virtual void createNode(const GraphInterface::Color &color, size_t id) = 0;
    virtual void addEdge(size_t from, size_t to, const GraphInterface::Color &color) = 0;
    virtual bool nodeExists(size_t id) const = 0;
    virtual void removeNode(size_t id) = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t getMaxCapacity() const = 0;
    virtual size_t size() const = 0;
};


#endif //RED_BLUE_GRAPH_SOLVER_1_GRAPHINTERFACE_H
