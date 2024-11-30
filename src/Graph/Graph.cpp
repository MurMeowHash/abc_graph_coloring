#include "Graph.h"
#include "../Random/Random.h"
#include <iostream>
#include <algorithm>

Graph::Graph() : Graph(0) {

}

Graph::Graph(uint vertexCount) : adjacencyMatrix(vertexCount), nodes(vertexCount) {

}

Graph::Graph(uint vertexCount, uint minDegree, uint maxDegree)
: Graph(vertexCount) {
    randomFill(minDegree, maxDegree);
}

bool Graph::randomFill(uint minDegree, uint maxDegree) {
    if (minDegree > maxDegree) {
        std::cerr << "Error: minDegree cannot be greater than maxDegree.\n";
        return false;
    }

    for (uint i = 0; i < adjacencyMatrix.size(); i++) {
        auto &adjacentNodes = adjacencyMatrix[i];
        uint currentDegree = adjacentNodes.size();

        while (currentDegree < minDegree) {
            uint j = Random::range(0, adjacencyMatrix.size() - 1);
            if (i != j && adjacencyMatrix[j].size() < maxDegree &&
                std::find(adjacencyMatrix[i].begin(), adjacencyMatrix[i].end(), j) == adjacencyMatrix[i].end()) {
                makeEdge(i, j);
                currentDegree++;
            }
        }

        while (currentDegree < maxDegree) {
            uint j = Random::range(0, adjacencyMatrix.size() - 1);
            if (i != j && adjacencyMatrix[j].size() < maxDegree &&
                std::find(adjacencyMatrix[i].begin(), adjacencyMatrix[i].end(), j) == adjacencyMatrix[i].end()) {
                makeEdge(i, j);
                currentDegree++;
            } else {
                break;
            }
        }
    }

    for (uint i = 0; i < adjacencyMatrix.size(); i++) {
        if (adjacencyMatrix[i].size() < minDegree) {
            std::cerr << "Failed to meet minimum degree requirement for vertex " << i << ".\n";
            return false;
        }
    }

    return true;
}

void Graph::connectedComponents() {
    uint nodesCount = nodes.size();
    bool *visited = new bool[nodesCount];
    for(uint v = 0; v < nodesCount; v++) {
        visited[v] = false;
    }
    for(uint v = 0; v < nodesCount; v++) {
        if(!visited[v]) {
            DFSUtil(v, visited);
            std::cout<<"\n\n\n\n\n";
        }
    }
    delete [] visited;
}

void Graph::DFSUtil(uint v, bool visited[]) {
    visited[v] = true;
    std::cout<<v<<" ";
    for(uint i = 0; i < adjacencyMatrix[v].size(); i++) {
        if(!visited[adjacencyMatrix[v][i]]) {
            DFSUtil(adjacencyMatrix[v][i], visited);
        }
    }
}

void Graph::makeEdge(uint lhsVert, uint rhsVert) {
    adjacencyMatrix[lhsVert].push_back(rhsVert);
    adjacencyMatrix[rhsVert].push_back(lhsVert);
}

void Graph::makeEdge(const char *lhs, const char *rhs) {
    int lhsIndex{INVALID_INDEX}, rhsIndex{INVALID_INDEX};
    for(int i = 0; i < nodes.size(); i++) {
        const char *nodeName = nodes[i].name;
        if(nodeName == lhs) {
            lhsIndex = i;
        } else if(nodeName == rhs) {
            rhsIndex = i;
        }
    }
    if(lhsIndex == INVALID_INDEX
       || rhsIndex == INVALID_INDEX) {
        return;
    }
    makeEdge(lhsIndex, rhsIndex);
}

void Graph::addNode(const char *name) {
    nodes.emplace_back(name);
    adjacencyMatrix.emplace_back(0);
}

uint Graph::getConflictsCount() const {
    uint conflicts{0};
    for(uint i = 0; i < adjacencyMatrix.size(); i++) {
        for(auto adjacent : adjacencyMatrix[i]) {
            if(nodes[i].color == nodes[adjacent].color) {
                conflicts++;
            }
        }
    }
    return conflicts;
}

const std::vector<Node> &Graph::getNodes() const {
    return nodes;
}