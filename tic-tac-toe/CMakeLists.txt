cmake_minimum_required(VERSION 3.10)

project(TicTacToe)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML HINTS C:/dev/SFML-2.5.1-64bit/lib/cmake/SFML COMPONENTS audio system graphics network window REQUIRED)


add_executable(TicTacToe game.cpp)

target_include_directories(TicTacToe PUBLIC C:/dev/SFML-2.5.1-64bit/include/)
target_link_libraries(TicTacToe sfml-graphics sfml-system sfml-window sfml-network sfml-audio )
