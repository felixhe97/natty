cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

project(natty VERSION 0.2)

add_executable(natty main.cpp)
target_sources(natty PRIVATE TrieMap.cpp)
