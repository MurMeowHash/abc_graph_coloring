#include <iostream>

#include "Graph/Graph.h"
#include "ABCGraphColoring/ABCGraphColoring.h"
#include <windows.h>

#define DEFAULT_CONSOLE_COLOR 7

Graph *makeUSAGraph();
Graph *makeAustraliaGraph();
void outputColor(int color);
void printGraph(const Graph &graph);
void printResults(const Graph &graph, const ABCGraphColoring &solver);

int main() {
    auto graph = new Graph{200, 1, 20};
    ABCGraphColoring solver{*graph};
    solver(4);
    printResults(*graph, solver);
    delete graph;
    return 0;
}

Graph *makeAustraliaGraph() {
    auto graph = new Graph{7};
    graph->makeEdge(0, 1);
    graph->makeEdge(0, 2);
    graph->makeEdge(1, 2);
    graph->makeEdge(1, 3);
    graph->makeEdge(2, 3);
    graph->makeEdge(2, 4);
    graph->makeEdge(2, 5);
    graph->makeEdge(3, 4);
    graph->makeEdge(4, 5);
    return graph;
}

Graph *makeUSAGraph() {
    auto graph = new Graph;
    graph->addNode("Washington");
    graph->addNode("Oregon");
    graph->addNode("Idaho");
    graph->addNode("California");
    graph->addNode("Nevada");
    graph->addNode("Utah");
    graph->addNode("Arizona");
    graph->addNode("New Mexico");
    graph->addNode("Colorado");
    graph->addNode("Wyoming");
    graph->addNode("Montana");
    graph->addNode("North Dakota");
    graph->addNode("South Dakota");
    graph->addNode("Nebraska");
    graph->addNode("Kansas");
    graph->addNode("Oklahoma");
    graph->addNode("Texas");
    graph->addNode("Minnesota");
    graph->addNode("Iowa");
    graph->addNode("Missouri");
    graph->makeEdge("Washington", "Oregon");
    graph->makeEdge("Washington", "Idaho");
    graph->makeEdge("Oregon", "Idaho");
    graph->makeEdge("Oregon", "California");
    graph->makeEdge("Oregon", "Nevada");
    graph->makeEdge("California", "Nevada");
    graph->makeEdge("California", "Arizona");
    graph->makeEdge("Idaho", "Montana");
    graph->makeEdge("Idaho", "Wyoming");
    graph->makeEdge("Idaho", "Utah");
    graph->makeEdge("Idaho", "Nevada");
    graph->makeEdge("Nevada", "Arizona");
    graph->makeEdge("Nevada", "Utah");
    graph->makeEdge("Arizona", "Utah");
    graph->makeEdge("Arizona", "New Mexico");
    graph->makeEdge("Utah", "Colorado");
    graph->makeEdge("Utah", "Wyoming");
    graph->makeEdge("Montana", "Wyoming");
    graph->makeEdge("Montana", "North Dakota");
    graph->makeEdge("Montana", "South Dakota");
    graph->makeEdge("Wyoming", "Colorado");
    graph->makeEdge("Wyoming", "South Dakota");
    graph->makeEdge("Wyoming", "Nebraska");
    graph->makeEdge("Colorado", "New Mexico");
    graph->makeEdge("Colorado", "Nebraska");
    graph->makeEdge("Colorado", "Kansas");
    graph->makeEdge("Colorado", "Oklahoma");
    graph->makeEdge("New Mexico", "Oklahoma");
    graph->makeEdge("New Mexico", "Texas");
    graph->makeEdge("Texas", "Oklahoma");
    graph->makeEdge("Oklahoma", "Kansas");
    graph->makeEdge("Oklahoma", "Missouri");
    graph->makeEdge("Kansas", "Nebraska");
    graph->makeEdge("Kansas", "Missouri");
    graph->makeEdge("Nebraska", "South Dakota");
    graph->makeEdge("Nebraska", "Missouri");
    graph->makeEdge("Nebraska", "Iowa");
    graph->makeEdge("South Dakota", "Iowa");
    graph->makeEdge("South Dakota", "Minnesota");
    graph->makeEdge("South Dakota", "North Dakota");
    graph->makeEdge("North Dakota", "Minnesota");
    graph->makeEdge("Minnesota", "Iowa");
    graph->makeEdge("Iowa", "Missouri");
    return graph;
}

void outputColor(int color) {
    color++;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int backgroundColor = (color << 4) | color;
    SetConsoleTextAttribute(hConsole, backgroundColor);
    std::cout<<"   ";
    SetConsoleTextAttribute(hConsole, DEFAULT_CONSOLE_COLOR);
}

void printGraph(const Graph &graph) {
    const auto &nodes = graph.getNodes();
    for(uint i = 0; i < nodes.size(); i++) {
        std::cout << "Node: " << i << " | Color: ";
        outputColor(nodes[i].color);
        std::cout<<"\n\n";
    }
}

void printResults(const Graph &graph, const ABCGraphColoring &solver) {
    printGraph(graph);
    std::cout << "Chromatic number: " << solver.getUsedColors() << '\n';
    std::cout << "Conflicts count: " << graph.getConflictsCount() << '\n';
}