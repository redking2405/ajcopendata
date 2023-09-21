cmake_minimum_required(VERSION 3.5)

project(opendata LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(opendata main.cpp)

install(TARGETS opendata
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
