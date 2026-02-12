#include "dijkstra.hpp"
#include "heaptest.hpp"
#include "WeightedGraphList.hpp"
#include <iostream>

using namespace std;

template <typename V, typename W>
void testDijkstra(const WeightedGraphList<V, W> &g);
void testDijkstraMap();
void testDijkstraToy();

int main() {
    int choice;
    cout << "Menu:" << endl;
    cout << "1 - ArrayHeap tests" << endl;
    cout << "2 - Dijkstra test (directed graph from lecture)" << endl;
    cout << "3 - Dijkstra test (undirected map data)" << endl;
    cout << "Choose one (1-3): ";
    cin >> choice;

    switch (choice) {
    case 1:
        testHeap();
        break;
    case 2:
        testDijkstraToy();
        break;
    case 3:
        testDijkstraMap();
        break;
    default:
        cout << "Invalid option" << endl;
    }

    return 0;
}

template <typename V, typename W>
void testDijkstra(const WeightedGraphList<V, W> &g) {
    V start;

    cout << "Vertices: ";
    for (const auto& v : g.getVertices())
        cout << v << "; ";
    cout << endl;

    cout << "Enter a starting vertex: ";
    cin >> start;

    if (g.getVertices().count(start)) {
        dijkstra<V,W>(g, start);
    } else {
        cout << "Error: vertex not found in graph" << endl;
    }
}

void testDijkstraMap() {
    WeightedGraphList<string, float> g(GType::UNDIRECTED);
    g.addEdge("Hayward", "Castro Valley", 3.2);
    g.addEdge("Castro Valley", "Dublin", 9.3);
    g.addEdge("Dublin", "San Ramon", 6.0);
    g.addEdge("Dublin", "Livermore", 10.6);
    g.addEdge("Dublin", "Pleasanton", 6.4);
    g.addEdge("San Ramon", "Danville", 5.8);
    g.addEdge("Livermore", "Pleasanton", 8.0);
    g.addEdge("Livermore", "Mountain House", 15.9);
    g.addEdge("Livermore", "Tracy", 23.0);
    g.addEdge("Mountain House", "Tracy", 9.3);

    //g.print();
    testDijkstra<string, float>(g);
}

void testDijkstraToy() {
    WeightedGraphList<char, unsigned> g(GType::DIRECTED);
    g.addEdge('0', '1', 10);
    g.addEdge('0', '2', 3);
    g.addEdge('0', '3', 20);
    g.addEdge('1', '3', 5);
    g.addEdge('2', '1', 2);
    g.addEdge('2', '4', 15);
    g.addEdge('3', '4', 11);

    //g.print();
    testDijkstra<char, unsigned>(g);
}

