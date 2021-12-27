cmake_minimum_required(VERSION 3.16)
project(red_blue_graph_solver_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(red_blue_graph_solver_1 main.cpp Graph.cpp Graph.h Node.cpp Node.h FlatGraph.cpp FlatGraph.h GraphInterface.h compilation_infos.h)
