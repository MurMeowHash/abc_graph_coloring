#include "ABCGraphColoring.h"
#include "../Random/Random.h"
#include <algorithm>
#include <iostream>

ABCGraphColoring::ABCGraphColoring(Graph &graph)
: graph{graph}, currentPos{0}, usedColors{0}, coloredNodes{0} {

}

void ABCGraphColoring::operator()(uint targetColors) {
    formNodeData();
    approximateChromaticNum();
    colorsInUse.resize(chromaticNum, 0);
    sendEmployedBees();
    sendScoutBees();
    bool reachedTarget{false};
    while(!openNodes.empty() && !reachedTarget) {
        decltype(openNodes) onlookersNodes;
        uint i{0};
        while(i < ONLOOKER_BEES_COUNT
        && !reachedTarget
        && !openNodes.empty()) {
            recalculateProbabilities();
            uint targetVertex = findOnlookerNode();
            colorNeighbors(targetVertex);
            assignAvailableColor(targetVertex);
            findHeuristicSource(onlookersNodes);
            if(coloredNodes == graph.nodes.size()
               && usedColors <= targetColors) {
                reachedTarget = true;
            }
            i++;
        }
        openNodes.insert(openNodes.end(), onlookersNodes.begin(), onlookersNodes.end());
        sendScoutBees();
    }
    for(auto node : availableNodes) {
        delete node;
    }
}

void ABCGraphColoring::formNodeData() {
    availableNodes.resize(graph.nodes.size());
    for(uint i = 0; i < availableNodes.size(); i++) {
        availableNodes[i] = new ABCNodeData{i, static_cast<uint>(graph.adjacencyMatrix[i].size())};
    }
    std::sort(availableNodes.begin(), availableNodes.end(),
              [](const ABCNodeData *lhs, const ABCNodeData *rhs) {
        return lhs->nectar > rhs->nectar;
    });
}

void ABCGraphColoring::approximateChromaticNum() {
    chromaticNum = availableNodes.front()->nectar + 1;
}

void ABCGraphColoring::recalculateProbabilities() {
    uint nectarAmount{0};
    std::for_each(openNodes.begin(), openNodes.end(), [&nectarAmount](ABCNodeDataProb nodeDataProb){
        nectarAmount += nodeDataProb.nodeData->nectar;
    });
    uint targetNectarSum = nectarAmount == 0 ? openNodes.size() : nectarAmount;
    double probabilitySum{0};
    for(auto &nodeDataProb : openNodes) {
        uint targetNectar = nectarAmount == 0 ? 1 : nodeDataProb.nodeData->nectar;
        probabilitySum += static_cast<double>(targetNectar) / static_cast<double>(targetNectarSum);
        nodeDataProb.probability = probabilitySum;
    }
}

void ABCGraphColoring::findHeuristicSource(std::list<ABCNodeDataProb> &targetList) {
    if(currentPos >= availableNodes.size()) {
        return;
    }
    auto nodeData = availableNodes[currentPos++];
    targetList.emplace_back(nodeData, 0.0);
}

void ABCGraphColoring::sendEmployedBees() {
    for(uint i = 0; i < EMPLOYED_BEES_COUNT; i++) {
        findHeuristicSource(openNodes);
    }
}

void ABCGraphColoring::sendScoutBees() {
    uint i{0};
    while(i < SCOUT_BEES_COUNT
    && currentPos < availableNodes.size()) {
        int randIndex = Random::range(currentPos, static_cast<int>(availableNodes.size() - 1));
        auto randNodeData = availableNodes[randIndex];
        openNodes.emplace_back(randNodeData, 0.0);
        std::swap(availableNodes[currentPos], availableNodes[randIndex]);
        currentPos++;
        findNodePlace(randIndex);
        i++;
    }
}

void ABCGraphColoring::colorNeighbors(uint vertex) {
    auto adjacentNodes = graph.adjacencyMatrix.at(vertex);
    removeColor(vertex);
    for(auto node : adjacentNodes) {
        assignAvailableColor(node);
    }
}

void ABCGraphColoring::assignAvailableColor(uint vertex) {
    std::vector<bool> availableColors(chromaticNum, true);
    auto adjacentNodes = graph.adjacencyMatrix[vertex];
    for(auto node : adjacentNodes) {
        int neighborColor = graph.nodes[node].color;
        if(neighborColor != Node::ABSENT_COLOR) {
            availableColors[neighborColor] = false;
        }
    }
    int i{0};
    bool foundAvailableColor{false};
    while(i != availableColors.size()
    && !foundAvailableColor) {
        if(availableColors[i]) {
            assignColor(vertex, i);
            foundAvailableColor = true;
        }
        i++;
    }
}

uint ABCGraphColoring::findOnlookerNode() {
    double randProb = Random::genProbability();
    uint targetVertex;
    bool foundNode{false};
    auto nodeIterator = openNodes.begin();
    while(nodeIterator != openNodes.end()
          && !foundNode) {
        if(randProb < nodeIterator->probability) {
            targetVertex = nodeIterator->nodeData->number;
            openNodes.erase(nodeIterator);
            foundNode = true;
        }
        nodeIterator++;
    }
    return targetVertex;
}

void ABCGraphColoring::assignColor(uint vertex, int color) {
    removeColor(vertex);
    if(color == Node::ABSENT_COLOR) {
        return;
    }
    Node &node = graph.nodes[vertex];
    node.color = color;
    if(++colorsInUse[node.color] == 1) {
        usedColors++;
    }
    coloredNodes++;
}

void ABCGraphColoring::removeColor(uint vertex) {
    Node &node = graph.nodes[vertex];
    if(node.color == Node::ABSENT_COLOR) {
        return;
    }
    if(--colorsInUse[node.color] == 0) {
        usedColors--;
    }
    node.color = Node::ABSENT_COLOR;
    coloredNodes--;
}

void ABCGraphColoring::findNodePlace(uint vertex) {
    uint i{vertex - 1};
    bool foundPlace{false};
    while(i >= currentPos
    && !foundPlace) {
        if(availableNodes[i + 1]->nectar > availableNodes[i]->nectar) {
            std::swap(availableNodes[i + 1], availableNodes[i]);
        } else {
            foundPlace = true;
        }
        i--;
    }
}

uint ABCGraphColoring::getUsedColors() const {
    return usedColors;
}