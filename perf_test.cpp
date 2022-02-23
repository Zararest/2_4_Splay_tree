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


BOOST_AUTO_TEST_SUITE_END()