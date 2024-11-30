#pragma once

#include <vector>
#include "Node/Node.h"

struct ABCGraphColoring;

class Graph {
    friend ABCGraphColoring;
private:
    static constexpr uint EDGE{1};
    static constexpr int INVALID_INDEX{-1};
    std::vector<std::vector<uint>> adjacencyMatrix;
    std::vector<Node> nodes;
    bool randomFill(uint minDegree, uint maxDegree);
    void DFSUtil(uint v, bool visited[]);
public:
    explicit Graph();
    explicit Graph(uint vertexCount);
    Graph(uint vertexCount, uint minDegree, uint maxDegree);
    void connectedComponents();
    void addNode(const char *name);
    void makeEdge(uint lhsVert, uint rhsVert);
    void makeEdge(const char *lhs, const char *rhs);
    NODISCARD uint getConflictsCount() const;
    NODISCARD const std::vector<Node> &getNodes() const;
};