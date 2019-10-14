cmake_minimum_required(VERSION 3.5.1)

#add_definitions(-std=c++11 -pthread)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

project(Pacman)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(Pacman src/controller.cpp src/game.cpp src/pacman.cpp src/enemy.cpp src/renderer.cpp src/main.cpp src/map.cpp src/character.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Pacman ${SDL2_LIBRARIES})
