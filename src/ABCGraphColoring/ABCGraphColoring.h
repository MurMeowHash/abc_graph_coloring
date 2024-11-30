#pragma once

#include "../Graph/Graph.h"
#include "../utils/utils.h"
#include <queue>
#include <list>
#include "ABCNodeData/ABCNodeData.h"
#include "ABCNodeData/ABCNodeDataProb.h"

struct ABCGraphColoring {
    explicit ABCGraphColoring(Graph &graph);
    void operator()(uint targetColors);
    NODISCARD uint getUsedColors() const;
private:
    static constexpr uint EMPLOYED_BEES_COUNT{14};
    static constexpr uint ONLOOKER_BEES_COUNT{14};
    static constexpr uint SCOUT_BEES_COUNT{2};
    std::vector<ABCNodeData*> availableNodes;
    std::list<ABCNodeDataProb> openNodes;
    std::vector<uint> colorsInUse;
    uint coloredNodes;
    uint usedColors;
    uint chromaticNum;
    int currentPos;
    Graph &graph;
    void formNodeData();
    void approximateChromaticNum();
    void recalculateProbabilities();
    void findHeuristicSource(std::list<ABCNodeDataProb> &targetList);
    void sendEmployedBees();
    void sendScoutBees();
    void colorNeighbors(uint vertex);
    void assignAvailableColor(uint vertex);
    uint findOnlookerNode();
    void assignColor(uint vertex, int color);
    void removeColor(uint vertex);
    void findNodePlace(uint vertex);
};