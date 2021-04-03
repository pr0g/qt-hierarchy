cmake_minimum_required(VERSION 3.15)
project(qt-hierarchy LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include(FetchContent)
FetchContent_Declare(
    hierarchy
    GIT_REPOSITORY https://github.com/pr0g/hierarchy.git
    GIT_TAG        51ed7524fa5e8c04eab7b16a8cc51d372578be7c)
FetchContent_MakeAvailable(hierarchy)

add_executable(${PROJECT_NAME})
target_sources(
  ${PROJECT_NAME} PRIVATE main.cpp tree-model.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets hierarchy)
