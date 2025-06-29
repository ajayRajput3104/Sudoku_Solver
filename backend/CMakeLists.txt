cmake_minimum_required(VERSION 3.10)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(sudoku main.cpp)

# This tells the compiler to look in backend/crow and backend/
target_include_directories(sudoku PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/crow
)

target_include_directories(sudoku PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/crow
    ${CMAKE_CURRENT_SOURCE_DIR}/asio
)

