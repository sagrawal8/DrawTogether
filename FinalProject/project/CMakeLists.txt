# Your CMakeLists.txt for the main App project

cmake_minimum_required(VERSION 3.14)
project(App)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES ./src/main.cpp ./src/App.cpp ./src/Command.cpp ./src/Draw.cpp ./src/Square.cpp ./src/BaseShape.cpp src/Triangle.cpp src/Circle.cpp src/PaintCanvas.cpp ./src/servernetwork.cpp ./src/clientnetwork.cpp)
add_executable(App ${SOURCE_FILES})
include_directories(./include)
#set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(App sfml-system sfml-window sfml-graphics sfml-audio sfml-network)


#added additionals to run test project as well
add_executable(App_Test ./src/App.cpp ./src/Command.cpp ./src/Draw.cpp ./tests/main_test.cpp ./tests/catch_amalgamated.cpp)
target_link_libraries(App_Test sfml-graphics sfml-window sfml-system)
