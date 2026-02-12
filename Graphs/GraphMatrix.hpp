#pragma once

#include "Graph.hpp"

class GraphMatrix: public Graph {
private:
    bool **adjMatrix;

protected:
    // print a representation of the graph
    virtual std::ostream& print(std::ostream&) const override;

public:
    // constructor
    GraphMatrix(int, GType);

    // destructor
    virtual ~GraphMatrix();

    // determine if an edge exists between the two given vertices
    virtual bool isEdge(int, int) const override;

    // toggle the existence of an edge between the two given vertices
    virtual void toggleEdge(int, int) override;
};
