#pragma once

#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <utility>


// An enum to specify whether the graph is directed/undirected
enum class GType {
    DIRECTED,
    UNDIRECTED,
};

// Stores a weighted graph using the ideas of the adjacency-list representation.
// Not fully functional: allows for the creation and access of edges/vertices, but not their removal.
// Edges are stored as std::pair objects, where `first` is the destination vertex and `second` is the weight of that edge.
//
// V - the type of the vertex labels
// W - the type of the weights (probably float, int, etc)
template <typename V, typename W>
class WeightedGraphList {
private:
    // Stores whether this is a directed graph versus an undirected graph
    GType type;

    // a map (dictionary) where:
    // keys are the vertex labels in the graph
    // values are a list of (vertex, weight) pairs, specifying all the outgoing edges from the key vertex
    std::unordered_map<V, std::list<std::pair<V, W>>> adj;

    // a (redundant) collection of the vertices in the graph, for convenience
    std::unordered_set<V> vertices;

    // keep track of how many (directed) edges are in the graph
    unsigned numEdges;

    // If a vertex of the given label is not present in the graph,
    // add an entry to the adjacency list for it.
    // (Does nothing if the vertex is already present)
    void ensureVertex(const V& vertex);

public:
    WeightedGraphList(GType t = GType::UNDIRECTED);

    // Add an edge from the source vertex to the target vertex, with the given weight.
    // If the given vertices are not already in the graph, it adds them.
    void addEdge(const V &source, const V &target, const W &weight);

    // Return a std::list of the vertex-weight pairs representing the outgoing edges
    // from the given source vertex.
    // In each pair, `first` specifies the destination vertex,
    // and `second` specifies the weight of that edge.
    const std::list<std::pair<V, W>>& getAdjacent(const V &source) const;

    // Returns how many (directed) edges are in the graph
    unsigned getNumEdges() const;

    // Return a read-only view of the set of all vertices in this graph
    const std::unordered_set<V>& getVertices() const;

    // cout the outgoing edges of each vertex
    void print() const;
};

template <typename V, typename W>
WeightedGraphList<V, W>::WeightedGraphList(GType t) : type(t), numEdges(0) {}

template <typename V, typename W>
void WeightedGraphList<V, W>::ensureVertex(const V &name) {
    // if we haven't seen this vertex before
    if (vertices.count(name) == 0) {
        // add it to our set
        vertices.insert(name);

        // get started with an empty list for its outgoing edges
        adj.insert({name, std::list<std::pair<V, W>>()});
    }
}

template <typename V, typename W>
void WeightedGraphList<V, W>::addEdge(const V &source, const V &target, const W &weight) {
    // Add the source and target vertices to the graph, if they're not already there
    ensureVertex(source);
    ensureVertex(target);

    // Add the entry to source's list of outgoing edges
    adj[source].push_back(std::make_pair(target, weight));
    numEdges++;

    // if the graph is undirected, we also must add an edge for the same weight,
    // but in the other direction
    if (type == GType::UNDIRECTED) {
        adj[target].push_back(std::make_pair(source, weight));
        numEdges++;
    }
}

template <typename V, typename W>
const std::list<std::pair<V, W>>& WeightedGraphList<V, W>::getAdjacent(const V &source) const {
    return adj.at(source); // throws an exception if the key isn't found
}

template <typename V, typename W>
unsigned WeightedGraphList<V,W>::getNumEdges() const {
    return numEdges;
}

template <typename V, typename W>
const std::unordered_set<V>& WeightedGraphList<V, W>::getVertices() const {
    return vertices;
}

template <typename V, typename W>
void WeightedGraphList<V, W>::print() const {
    // for each vertex in the graph...
    // (range-based for-loop over the entire adjacency list, which is represented as a map/dictionary)
    for (const auto& keyvalue : adj) {
        // keyvalue is a std::pair where `first` is the source vertex, and `second` is the outgoing-edge-list

        // print the source vertex
        std::cout << keyvalue.first << ":" << std::endl;

        // for each outgoing edge, print the destination vertex label and weight
        // (range-based for-loop over a linked list representing the outgoing edges)
        for (const auto& pair : keyvalue.second) {
            // pair is a std::pair where `first` is the destination vertex, and `second` is the weight
            std::cout << "  " << pair.first << " (" << pair.second << ")" << std::endl;
        }
    }
}
