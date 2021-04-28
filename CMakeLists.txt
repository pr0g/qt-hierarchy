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
    GIT_TAG        49703301f6e922733a14666562ef8f954b9974b7)
FetchContent_MakeAvailable(hierarchy)

add_executable(${PROJECT_NAME})
target_sources(
  ${PROJECT_NAME} PRIVATE main.cpp tree-model.cpp main-window.cpp canvas.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets hierarchy)
