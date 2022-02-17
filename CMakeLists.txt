cmake_minimum_required(VERSION 2.8)
project(Splay_tree)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(SPLAY_DIR ./src/)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2") 

add_executable(Splay_tree   main.cpp 
                            ${SPLAY_DIR}Splay_tree.cpp)

add_executable(Splay_tree_test  test.cpp 
                                ${SPLAY_DIR}Splay_tree.cpp
                                ${SPLAY_DIR}Test_tree.cpp)

target_link_libraries(Splay_tree_test Boost::program_options)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)