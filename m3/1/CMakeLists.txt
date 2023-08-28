cmake_minimum_required(VERSION 3.20)
project(graph)

set(CMAKE_CXX_STANDARD 17)

add_executable(graph main.cpp ListGraph/ListGraph.cpp MatrixGraph/MatrixGraph.cpp SetGraph/SetGraph.cpp ArcGraph/ArcGraph.cpp)

