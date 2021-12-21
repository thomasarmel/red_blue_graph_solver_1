#ifndef RED_BLUE_GRAPH_SOLVER_1_GRAPHINTERFACE_H
#define RED_BLUE_GRAPH_SOLVER_1_GRAPHINTERFACE_H

#include <vector>
#include <optional>

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
};


#endif //RED_BLUE_GRAPH_SOLVER_1_GRAPHINTERFACE_H
