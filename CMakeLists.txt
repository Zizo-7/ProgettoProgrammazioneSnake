cmake_minimum_required(VERSION 3.16)
project(ncurses_example)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)

add_executable(untitled main.cpp
        snake.cpp
        snake.hpp
        food.cpp
        food.hpp
        game.cpp
        game.hpp
)
target_link_libraries(untitled ${CURSES_LIBRARIES})
