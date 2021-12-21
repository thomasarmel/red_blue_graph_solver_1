#include <iostream>
#include <chrono>
#include "Graph.h"
#include "Node.h"

int main()
{
    Graph graph(9);
    // No node 0
    graph.createNode(Graph::Color::BLUE, 1);
    graph.createNode(Graph::Color::RED, 2);
    graph.createNode(Graph::Color::RED, 3);
    graph.createNode(Graph::Color::BLUE, 4);
    graph.createNode(Graph::Color::RED, 5);
    graph.createNode(Graph::Color::BLUE, 6);
    graph.createNode(Graph::Color::BLUE, 7);
    graph.createNode(Graph::Color::RED, 8);

    graph.addEdge(1, 2, Graph::Color::BLUE);
    graph.addEdge(1, 8, Graph::Color::BLUE);
    graph.addEdge(2, 1, Graph::Color::RED);
    graph.addEdge(2, 3, Graph::Color::BLUE);
    graph.addEdge(2, 7, Graph::Color::BLUE);
    graph.addEdge(3, 6, Graph::Color::BLUE);
    graph.addEdge(3, 7, Graph::Color::RED);
    graph.addEdge(4, 3, Graph::Color::RED);
    graph.addEdge(4, 5, Graph::Color::RED);
    graph.addEdge(4, 6, Graph::Color::BLUE);
    graph.addEdge(5, 6, Graph::Color::RED);
    graph.addEdge(5, 7, Graph::Color::BLUE);
    graph.addEdge(6, 3, Graph::Color::BLUE);
    graph.addEdge(8, 7, Graph::Color::RED);

    std::cout << graph << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::optional<std::deque<size_t>> sequence = graph.getSequence(Graph::Color::RED, 7);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << (sequence.has_value() ? "Sequence trouvee" : "Sequence non trouvee") << std::endl;
    if (sequence.has_value())
    {
        std::cout << "Sequence : ";
        for (const size_t &it: sequence.value())
        {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Temps d'execution : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " micro-s" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    std::pair<size_t, std::deque<size_t>> sequenceMax = graph.getSequenceMax(Graph::Color::RED);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Sequence maximale (" << sequenceMax.first << " noeuds rouges retires): ";
    for (const size_t &it: sequenceMax.second)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    std::cout << "Temps d'execution : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " micro-s" << std::endl;
    return 0;
}
