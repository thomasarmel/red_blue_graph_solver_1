#include <iostream>
#include <chrono>
#include "Graph.h"
#include "FlatGraph.h"
#include <stack>

void graphTest();
void flatGraphTest();

int main()
{
    //graphTest();
    flatGraphTest();
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
    FlatGraph flatGraph(8);
    /*flatGraph.createNode(GraphInterface::Color::RED, 0);
    flatGraph.createNode(GraphInterface::Color::BLUE, 1);
    flatGraph.createNode(GraphInterface::Color::RED, 2);
    flatGraph.createNode(GraphInterface::Color::BLUE, 3);
    flatGraph.createNode(GraphInterface::Color::BLUE, 4);
    flatGraph.createNode(GraphInterface::Color::RED, 5);
    flatGraph.createNode(GraphInterface::Color::RED, 6);
    flatGraph.createNode(GraphInterface::Color::BLUE, 7);
    flatGraph.addEdge(0, 1, GraphInterface::Color::RED);
    flatGraph.addEdge(2, 1, GraphInterface::Color::BLUE);
    flatGraph.addEdge(2, 3, GraphInterface::Color::RED);
    flatGraph.addEdge(3, 4, GraphInterface::Color::BLUE);
    flatGraph.addEdge(5, 4, GraphInterface::Color::BLUE);
    flatGraph.addEdge(5, 6, GraphInterface::Color::BLUE);
    flatGraph.addEdge(7, 6, GraphInterface::Color::RED);*/
    flatGraph.createNode(GraphInterface::Color::RED, 0);
    flatGraph.createNode(GraphInterface::Color::BLUE, 1);
    flatGraph.createNode(GraphInterface::Color::RED, 2);
    flatGraph.createNode(GraphInterface::Color::RED, 3);
    flatGraph.createNode(GraphInterface::Color::BLUE, 4);
    flatGraph.createNode(GraphInterface::Color::BLUE, 5);
    flatGraph.createNode(GraphInterface::Color::RED, 6);
    flatGraph.createNode(GraphInterface::Color::RED, 7);
    flatGraph.addEdge(0, 1, GraphInterface::Color::RED);
    flatGraph.addEdge(1, 2, GraphInterface::Color::BLUE);
    flatGraph.addEdge(3, 2, GraphInterface::Color::BLUE);
    flatGraph.addEdge(3, 4, GraphInterface::Color::RED);
    flatGraph.addEdge(4, 5, GraphInterface::Color::RED);
    flatGraph.addEdge(6, 5, GraphInterface::Color::BLUE);
    flatGraph.addEdge(6, 7, GraphInterface::Color::RED);
    // [RED]-RED->[BLUE]-BLUE->[RED]<-BLUE-[RED]-RED->[BLUE]-RED->[BLUE]<-BLUE-[RED]-RED->[RED]
    std::cout << flatGraph << std::endl;

    std::deque<size_t> sequenceMaxRed;
    sequenceMaxRed = flatGraph.getSequenceMax(GraphInterface::Color::RED);
    std::cout << "Maximum sequence (red): ";
    for (const size_t &it: sequenceMaxRed)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}