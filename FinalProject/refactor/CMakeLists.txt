cmake_minimum_required(VERSION 3.16)
project(App)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(SOURCE_FILES ./src/PaintCanvas.cpp ./src/main.cpp ./src/Parser.cpp ./src/ServerConnection.cpp ./src/ClientConnection.cpp ./src/ClientController.cpp)

add_executable(App ${SOURCE_FILES})
include_directories(./include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(App sfml-system sfml-window sfml-graphics sfml-audio sfml-network pthread)

# Test PaintCanvas class
#add_executable(PaintCanvas_test ./src/PaintCanvas.cpp ./tests/PaintCanvas_test.cpp ./tests/catch_amalgamated.cpp ./src/Parser.cpp)
#target_link_libraries(PaintCanvas_test sfml-window sfml-graphics sfml-network)
