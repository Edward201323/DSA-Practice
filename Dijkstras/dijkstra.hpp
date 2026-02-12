#pragma once

#include "PriorityQueue.hpp"
#include "WeightedGraphList.hpp"
#include <iostream>
#include <unordered_map>
#include <unordered_set>

// V - the type of the vertex labels
// W - the type of the numerical distances / edge weights

template <typename V, typename W>
void dijkstra(const WeightedGraphList<V, W> &g, const V &start) {
    PriorityQueue<V, W> pq(PriorityMode::ASCENDING, g.getNumEdges());
    std::unordered_map<V, W> tentative_distances;
    std::unordered_set<V> found_shortest;

    pq.enqueue(start, 0);
    tentative_distances[start] = 0;

    while (!pq.isEmpty()) {
        V current = pq.frontElement();
        W current_distance = pq.frontPriority();
        pq.dequeue();

        if (found_shortest.count(current)) continue;

        found_shortest.insert(current);

        for (const auto &neighbor : g.getAdjacent(current)) {
            V neighbor_vertex = neighbor.first;
            W edge_weight = neighbor.second;
            W new_distance = current_distance + edge_weight;

            if (!tentative_distances.count(neighbor_vertex) || new_distance < tentative_distances[neighbor_vertex]) {
                tentative_distances[neighbor_vertex] = new_distance;
                pq.enqueue(neighbor_vertex, new_distance);
            }
        }
    }

    for (const auto &vertex : g.getVertices()) {
        if (tentative_distances.count(vertex))
            std::cout << vertex << ": " << tentative_distances[vertex] << std::endl;
        else
            std::cout << vertex << ": unreachable" << std::endl;
    }
}

