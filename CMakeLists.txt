cmake_minimum_required (VERSION 2.8.8)
project (PudgeWars)

set(GAME_FILE_DIRECTORY "pudge-wars")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g") 
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Allegro5 REQUIRED)
include_directories(${ALLEGRO_INCLUDE_DIRS})

add_subdirectory (src)
#add_subdirectory (test)
