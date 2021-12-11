#include <iostream>
#include <chrono>
#include "Graph.h"
#include "Node.h"

int main()
{
    Graph graph(9);
    // No node 0
    Node *n1 = graph.createNode(Graph::Color::BLUE, 1);
    Node *n2 = graph.createNode(Graph::Color::RED, 2);
    Node *n3 = graph.createNode(Graph::Color::RED, 3);
    Node *n4 = graph.createNode(Graph::Color::BLUE, 4);
    Node *n5 = graph.createNode(Graph::Color::RED, 5);
    Node *n6 = graph.createNode(Graph::Color::BLUE, 6);
    Node *n7 = graph.createNode(Graph::Color::BLUE, 7);
    Node *n8 = graph.createNode(Graph::Color::RED, 8);
    n1->addNeighbor(n2, Graph::Color::BLUE);
    n1->addNeighbor(n8, Graph::Color::BLUE);
    n2->addNeighbor(n1, Graph::Color::RED);
    n2->addNeighbor(n3, Graph::Color::BLUE);
    n2->addNeighbor(n7, Graph::Color::BLUE);
    n3->addNeighbor(n6, Graph::Color::BLUE);
    n3->addNeighbor(n7, Graph::Color::RED);
    n4->addNeighbor(n3, Graph::Color::RED);
    n4->addNeighbor(n5, Graph::Color::RED);
    n4->addNeighbor(n6, Graph::Color::BLUE);
    n5->addNeighbor(n6, Graph::Color::RED);
    n5->addNeighbor(n7, Graph::Color::BLUE);
    n6->addNeighbor(n3, Graph::Color::BLUE);
    n8->addNeighbor(n7, Graph::Color::RED);
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
