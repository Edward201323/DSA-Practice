#include "GraphMatrix.hpp"

GraphMatrix::GraphMatrix(int numV, GType type) : Graph(numV, 0, type) {
    adjMatrix = new bool*[v];
    for (int i = 0; i < v; ++i) {
        adjMatrix[i] = new bool[v];
        for (int j = 0; j < v; ++j) {
            adjMatrix[i][j] = false;
        }
    }
}

GraphMatrix::~GraphMatrix() {
    for (int i = 0; i < v; ++i) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

bool GraphMatrix::isEdge(int i, int j) const {
    if (i < 0 || i >= v || j < 0 || j >= v) {
        return false;
    }
    return adjMatrix[i][j];
}

std::ostream& GraphMatrix::print(std::ostream &os) const {
    os << "    ";
    for (int i = 0; i < v; i++) {
        os << i << ' ';
    }
    os << std::endl;

    os << "---";
    for (int i = 0; i < v; i++) {
        os << "--";
    }
    os << std::endl;

    for (int i = 0; i < v; i++) {
        os << i << " | ";
        for (int j = 0; j < v; j++) {
            os << adjMatrix[i][j] << ' ';
        }
        os << std::endl;
    }

    return os;
}

void GraphMatrix::toggleEdge(int i, int j) {
    if (i < 0 || i >= v || j < 0 || j >= v) {
        std::cerr << "Invalid vertex number." << std::endl;
        return;
    }

    if (adjMatrix[i][j]) {
        adjMatrix[i][j] = false;
        e--;
        if (graphType == UNDIRECTED) {
            adjMatrix[j][i] = false;
        }
    } else {
        adjMatrix[i][j] = true;
        e++;
        if (graphType == UNDIRECTED) {
            adjMatrix[j][i] = true;
        }
    }
}