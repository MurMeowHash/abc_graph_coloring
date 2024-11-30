cmake_minimum_required(VERSION 3.29)
project(abc_graph_coloring)

set(CMAKE_CXX_STANDARD 20)

add_executable(abc_graph_coloring src/main.cpp
        src/Graph/Graph.cpp
        src/Graph/Graph.h
        src/utils/utils.cpp
        src/utils/utils.h
        src/Graph/Node/Node.h
        src/Random/Random.cpp
        src/Random/Random.h
        src/Graph/Node/Node.cpp
        src/ABCGraphColoring/ABCGraphColoring.cpp
        src/ABCGraphColoring/ABCGraphColoring.h
        src/ABCGraphColoring/ABCNodeData/ABCNodeData.h
        src/ABCGraphColoring/ABCNodeData/ABCNodeDataProb.h
)
