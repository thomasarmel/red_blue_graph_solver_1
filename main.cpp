#include <iostream>
#include <chrono>
#include "Graph.h"
#include "FlatGraph.h"

void graphTest();
void flatGraphTest();

int main()
{
    graphTest();
    return 0;
}

void graphTest()
{
    Graph graph(9);
    // No node 0
    graph.createNode(GraphInterface::Color::BLUE, 1);
    graph.createNode(GraphInterface::Color::RED, 2);
    graph.createNode(GraphInterface::Color::RED, 3);
    graph.createNode(GraphInterface::Color::BLUE, 4);
    graph.createNode(GraphInterface::Color::RED, 5);
    graph.createNode(GraphInterface::Color::BLUE, 6);
    graph.createNode(GraphInterface::Color::BLUE, 7);
    graph.createNode(GraphInterface::Color::RED, 8);

    graph.addEdge(1, 2, GraphInterface::Color::BLUE);
    graph.addEdge(1, 8, GraphInterface::Color::BLUE);
    graph.addEdge(2, 1, GraphInterface::Color::RED);
    graph.addEdge(2, 3, GraphInterface::Color::BLUE);
    graph.addEdge(2, 7, GraphInterface::Color::BLUE);
    graph.addEdge(3, 6, GraphInterface::Color::BLUE);
    graph.addEdge(3, 7, GraphInterface::Color::RED);
    graph.addEdge(4, 3, GraphInterface::Color::RED);
    graph.addEdge(4, 5, GraphInterface::Color::RED);
    graph.addEdge(4, 6, GraphInterface::Color::BLUE);
    graph.addEdge(5, 6, GraphInterface::Color::RED);
    graph.addEdge(5, 7, GraphInterface::Color::BLUE);
    graph.addEdge(6, 3, GraphInterface::Color::BLUE);
    graph.addEdge(8, 7, GraphInterface::Color::RED);

    std::cout << graph << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::optional<std::deque<size_t>> sequence = graph.getSequence(GraphInterface::Color::RED, 7);
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
    std::pair<size_t, std::deque<size_t>> sequenceMax = graph.getSequenceMax(GraphInterface::Color::RED);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Sequence maximale (" << sequenceMax.first << " noeuds rouges retires): ";
    for (const size_t &it: sequenceMax.second)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    std::cout << "Temps d'execution : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " micro-s" << std::endl;
}

void flatGraphTest()
{
    FlatGraph flatGraph(10);
    flatGraph.generateRandom(0.5, 0.5, 0.5);
    std::cout << flatGraph << std::endl;
}