cmake_minimum_required(VERSION 3.15)

project(testSqlite)

set(CXX_STANDARD 11)

add_compile_options(-g -Wfatal-errors)

add_executable(testSq main.cpp)
target_link_libraries(testSq sqlite3)
