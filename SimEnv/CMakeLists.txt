cmake_minimum_required(VERSION 3.10)
project(SimEnv)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_library(SimEnv ${SOURCES}  "src/PhysicsFuncs.cpp")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_link_libraries(SimEnv PRIVATE sfml-system sfml-graphics sfml-window)