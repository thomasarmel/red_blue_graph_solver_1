# Red Blue Graph problem solver

The problem is the following:

In a directed graph, each node is colored either red or blue. Furthermore, vertices are also colored red or blue.

When a node is deleted, its adjacent nodes are colored the same color than the vertice which made the link with the node.

Can we delete an uninterrupted sequence of k nodes with all the same color ?

### How to implement the algorithm ?

Create a new directed graph with a max capacity of 10 nodes (note that the node ids are 0 to 9).
```c++
Graph graph(10);
```
Add a node with id 0 and color blue and a node with id 1 and color red (the nodes will be deleted by the graph destructor).
```c++
graph.createNode(GraphInterface::Color::BLUE, 0);
graph.createNode(GraphInterface::Color::RED, 1);
```
Add a directed red edge from node 0 to node 1.
```c++
graph.addEdge(0, 1, GraphInterface::Color::RED);
```
Is it possible to remove an uninterrupted sequence of k nodes with all the same red color ? Is so, the function returns the ids of the nodes to remove.
```c++
std::optional<std::deque<size_t>> sequence = graph.getSequence(GraphInterface::Color::RED, 7);
```
Get the max sequence of red nodes it is possible to remove. The first element of the pair is the number of red nodes in the sequence and the second is the list of ids of the nodes to remove.
```c++
std::pair<size_t, std::deque<size_t>> sequenceMax = graph.getSequenceMax(GraphInterface::Color::RED);
```

### Example

Consider the following graph:

![Example of red-blue graph](images/example_graph.png "Example of red-blue graph")

If we want to check if there is a sequence of 7 red nodes, we can use the following code:

```c++
    Graph graph(9);
    // No node 0 for better visibility
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
    std::optional<std::deque<size_t>> sequence = graph.getSequence(GraphInterface::Color::RED, 7);
    std::cout << (sequence.has_value() ? "Sequence found" : "Sequence not found") << std::endl;
    if (sequence.has_value())
    {
        std::cout << "Sequence : ";
        for (const size_t &it: sequence.value())
        {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }
```
We get the following output: **3 2 5 6 8 1 7**

If we analyze the output:
- We remove the node 3 -> node 7 becomes red, node 6 stays blue
- We remove the node 2 -> node 7 becomes blue, node 1 becomes red
- We remove the node 5 -> node 7 stays blue, node 6 becomes red
- We remove the node 8 -> node 7 becomes red
- We remove the node 1
- We remove the node 7
