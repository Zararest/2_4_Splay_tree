#include "src/headers/Test.h"

#define BOOST_TEST_MODULE First_TestSuite
#include <boost/test/included/unit_test.hpp>
#include <fstream>

BOOST_AUTO_TEST_SUITE(Performance_tests)

BOOST_AUTO_TEST_CASE(Gaus_distr_1){
    
    int ret = chdir("../bin/AVL_tests/Gaus_distr_1"); 
    
    Perf_test_tree perf_tests("input", "req", "ans");
    std::ofstream results;
    results.open("../../results", std::ios::app);

    results << "Distibution of the test:" << std::endl;

    results << "Gaus requests with constant size(100):\n" << 
    "input size = 1000000;\n" << 
    "requests number = 500000;\n" << 
    "sigma = 10\n" << 
    "rarity 1 in 10" << std::endl;

    perf_tests.perf_test(results);
    results << "-------------------\n\n" << std::endl;

    results.close();

    BOOST_REQUIRE_EQUAL(0, 0);
}

BOOST_AUTO_TEST_CASE(Gaus_distr_2){
    
    int ret = chdir("../Gaus_distr_2");

    Perf_test_tree perf_tests("input", "req", "ans");
    std::ofstream results;
    results.open("../../results", std::ios::app);

    results << "Distibution of the test:" << std::endl;

    results << "Gaus requests with constant size(100):\n" << 
    "input size = 1000000;\n" << 
    "requests number = 500000;\n" << 
    "sigma = 100\n" << 
    "rarity 1 in 10" << std::endl;

    perf_tests.perf_test(results);
    results << "-------------------\n\n" << std::endl;

    results.close();

    BOOST_REQUIRE_EQUAL(0, 0);
}

BOOST_AUTO_TEST_CASE(Gaus_distr_3){
    
    int ret = chdir("../Gaus_distr_3");

    Perf_test_tree perf_tests("input", "req", "ans");
    std::ofstream results;
    results.open("../../results", std::ios::app);

    results << "Distibution of the test:" << std::endl;

    results << "Gaus requests with constant size(100):\n" << 
    "input size = 1000000;\n" << 
    "requests number = 500000;\n" << 
    "sigma = 50\n" << 
    "rarity 1 in 10" << std::endl;

    perf_tests.perf_test(results);
    results << "-------------------\n\n" << std::endl;

    results.close();

    BOOST_REQUIRE_EQUAL(0, 0);
}

BOOST_AUTO_TEST_CASE(Gaus_distr_4){
    
    int ret = chdir("../Gaus_distr_4");

    Perf_test_tree perf_tests("input", "req", "ans");
    std::ofstream results;
    results.open("../../results", std::ios::app);

    results << "Distibution of the test:" << std::endl;

    results << "Gaus requests with constant size(100):\n" << 
    "input size = 1000000;\n" << 
    "requests number = 500000;\n" << 
    "sigma = 50\n" << 
    "rarity 1 in 1" << std::endl;

    perf_tests.perf_test(results);
    results << "-------------------\n\n" << std::endl;

    results.close();

    BOOST_REQUIRE_EQUAL(0, 0);
}

BOOST_AUTO_TEST_SUITE_END()