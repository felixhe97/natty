cmake_minimum_required(VERSION 3.10)

project(natty VERSION 0.1)

add_executable(natty main.cpp)
target_sources(natty PRIVATE TrieMap.cpp TrieMap.cpp)
