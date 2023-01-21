cmake_minimum_required(VERSION 3.24)
project(AllSyncer)

set(CMAKE_CXX_STANDARD 20)

add_executable(AllSyncer main.cpp src/Entry.cpp nlohmann-json/json.hpp)
