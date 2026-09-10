cmake_minimum_required(VERSION 3.10)

project(Tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 CONFIG REQUIRED)

add_executable(Tetris main.cpp)

target_sources(Tetris PRIVATE
	game_logic.cpp
)

target_link_libraries(Tetris PRIVATE SDL2::SDL2)