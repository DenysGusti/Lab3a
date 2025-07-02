cmake_minimum_required(VERSION 3.22)
project(Lab3a)

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_STANDARD 23)

add_executable(Lab3a main.cpp libs/pugixml/src/pugixml.cpp)
