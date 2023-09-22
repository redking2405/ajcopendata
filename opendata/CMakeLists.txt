cmake_minimum_required(VERSION 3.5)

project(opendata LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "/usr/include")
find_package(gd)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(opendata main.cpp)
target_link_libraries(opendata gd)
install(TARGETS opendata
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
