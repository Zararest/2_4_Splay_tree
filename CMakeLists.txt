cmake_minimum_required(VERSION 3.16)
project(Splay_tree)

SET(CMAKE_CXX_COMPILER /usr/bin/g++-9)
find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

set(SPLAY_DIR ./src/)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2") 


add_executable(Splay_tree   main.cpp)

add_executable(Splay_tree_test  test.cpp
                                ${SPLAY_DIR}Test_tree.cpp)

add_executable(Splay_tree_perf  perf_test.cpp
                                ${SPLAY_DIR}Perf_test_tree.cpp
                                ${SPLAY_DIR}Test_tree.cpp
                                ./src/AVL_tree/AVL_tree.cpp)                                

target_link_libraries(Splay_tree_test Boost::program_options)
target_link_libraries(Splay_tree_perf Boost::program_options)

target_compile_features(Splay_tree_test PRIVATE cxx_std_20)
target_compile_features(Splay_tree_perf PRIVATE cxx_std_20)
target_compile_features(Splay_tree PRIVATE cxx_std_20)
