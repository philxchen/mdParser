cmake_minimum_required(VERSION 3.5)
project(mdParser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    github-markdown.css
    main.cpp
    mdtransform.hpp
    test.md)

add_executable(mdParser ${SOURCE_FILES})