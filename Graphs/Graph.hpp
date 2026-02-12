#pragma once

#include <iostream>

class Graph {
public:
    enum GType {
        UNDIRECTED, DIRECTED
    };

protected:
    // the number of vertices
    int v;

    // the number of edges
    int e;

    // the type of graph
    GType graphType;

    // print a representation of the graph
    virtual std::ostream& print(std::ostream&) const = 0;

public:
    // default constructor
    Graph(int vv = 0, int ee = 0, GType gt = UNDIRECTED) :
            v(vv), e(ee), graphType(gt) {
    }

    // destructor
    virtual ~Graph() {
    }

    // return what type of graph this is
    virtual GType getGraphType() const {
        return graphType;
    }

    // determine if an edge exists between the two given vertices
    virtual bool isEdge(int, int) const = 0;

    // return the number of vertices
    virtual int numVertices() const {
        return v;
    }

    // return the number of edges
    virtual int numEdges() const {
        return e;
    }

    // toggle the existence of an edge between the two given vertices
    virtual void toggleEdge(int, int) = 0;

    // print a representation of the graph
    friend std::ostream& operator<<(std::ostream &os, const Graph &obj) {
        return obj.print(os);
    }
};
