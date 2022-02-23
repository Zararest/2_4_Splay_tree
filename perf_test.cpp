#include "src/headers/Test.h"

#define BOOST_TEST_MODULE First_TestSuite
#include <boost/test/included/unit_test.hpp>
#include <fstream>

BOOST_AUTO_TEST_SUITE(Performance_tests)

BOOST_AUTO_TEST_CASE(random){
    
    int ret = chdir("../bin/AVL_tests/random");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input"};
    char out_name[MAXLEN] = {"out"};

    Perf_test_tree perf_tests(input_name, "requests", "ans");
;
    perf_tests.range_requests(out_name);
    int diff_ret = std::system("diff ans out > ../../out");

    perf_tests.check_AVL_tree(out_name);
    diff_ret += std::system("diff ans out > ../../out");

    std::ofstream results;
    results.open("../../results");

    results << "random requests(input: 90000; requests: 10000):" << std::endl;
    perf_tests.perf_test(results);
    results << "-------------------\n\n" << std::endl;

    results.close();

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(another_random){
    
    int ret = chdir("../another_random");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_rand"};
    char out_name[MAXLEN] = {"out_rand"};

    Perf_test_tree perf_tests(input_name, "requests_rand", "ans_rand");
;
    perf_tests.range_requests(out_name);
    int diff_ret = std::system("diff ans_rand out_rand > ../../out");

    perf_tests.check_AVL_tree(out_name);
    diff_ret += std::system("diff ans_rand out_rand > ../../out");

    std::ofstream results;
    results.open("../../results", std::ios::app);

    results << "random requests(input: 10000; requests: 10000):" << std::endl;
    perf_tests.perf_test(results);
    results << "-------------------\n\n" << std::endl;

    results.close();

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(huge_random){
   /* 
    int ret = chdir("../huge_random");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_rand"};
    char out_name[MAXLEN] = {"out_rand"};

    Perf_test_tree perf_tests(input_name, "requests_rand", "ans_rand");
;
    perf_tests.range_requests(out_name);
    int diff_ret = std::system("diff ans_rand out_rand > ../../out");

    perf_tests.check_AVL_tree(out_name);
    diff_ret += std::system("diff ans_rand out_rand > ../../out");

    std::ofstream results;
    results.open("../../results", std::ios::app);

    results << "random requests(input: 200000; requests: 10000):" << std::endl;
    perf_tests.perf_test(results);
    results << "-------------------\n\n" << std::endl;

    results.close();

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
    */
}

BOOST_AUTO_TEST_CASE(strange_random){
    
    int ret = chdir("../strange_random");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_not_rand"};
    char out_name[MAXLEN] = {"out_not_rand"};

    Perf_test_tree perf_tests(input_name, "requests_not_rand", "ans_not_rand");
;
    perf_tests.range_requests(out_name);
    int diff_ret = std::system("diff ans_not_rand out_not_rand > ../../out");

    perf_tests.check_AVL_tree(out_name);
    diff_ret += std::system("diff ans_not_rand out_not_rand > ../../out");

    std::ofstream results;
    results.open("../../results", std::ios::app);

    results << "not random requests(input: 10000; requests: 10000; sigma = 100):" << std::endl;
    perf_tests.perf_test(results);
    results << "-------------------\n\n" << std::endl;

    results.close();

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(small_range){
    
    int ret = chdir("../small_range");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_not_rand"};
    char out_name[MAXLEN] = {"out_not_rand"};

    Perf_test_tree perf_tests(input_name, "requests_not_rand", "ans_not_rand");
;
    perf_tests.range_requests(out_name);
    int diff_ret = std::system("diff ans_not_rand out_not_rand > ../../out");

    perf_tests.check_AVL_tree(out_name);
    diff_ret += std::system("diff ans_not_rand out_not_rand > ../../out");

    std::ofstream results;
    results.open("../../results", std::ios::app);

    results << "not random requests(input: 10000; requests: 10000; sigma = 1):" << std::endl;
    perf_tests.perf_test(results);
    results << "-------------------\n\n" << std::endl;

    results.close();

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}


BOOST_AUTO_TEST_SUITE_END()