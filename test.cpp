#include "src/headers/Test.h"

#define BOOST_TEST_MODULE First_TestSuite
#include <boost/test/included/unit_test.hpp>

#include <cstdlib>

BOOST_AUTO_TEST_SUITE(Splay_tree_tests)

BOOST_AUTO_TEST_CASE(find){

    char input_name[MAXLEN] = {"../bin/find/input"};
    char out_name[MAXLEN] = {"../bin/find/out"};

    Test_tree find_test(input_name, "../bin/find/requests", "../bin/find/ans");

    find_test.find(out_name);

    int diff_ret = std::system("diff ../bin/find/ans ../bin/find/out > ../bin/out");

    BOOST_REQUIRE_EQUAL( diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(move_assign){

    char input_name[MAXLEN] = {"../bin/assign/input_move"};
    char out_name[MAXLEN] = {"../bin/assign/out_move"};

    Test_tree find_test(input_name, "../bin/assign/requests_move", "../bin/assign/ans_move");

    find_test.move_assign(out_name);

    int diff_ret = std::system("diff ../bin/assign/ans_move ../bin/assign/out_move > ../bin/out");

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(copy_assign){

    char input_name[MAXLEN] = {"../bin/assign/input_copy"};
    char out_name[MAXLEN] = {"../bin/assign/out_copy"};

    Test_tree find_test(input_name, "../bin/assign/requests_copy", "../bin/assign/ans_copy");

    find_test.move_assign(out_name);

    int diff_ret = std::system("diff ../bin/assign/ans_copy ../bin/assign/out_copy > ../bin/out");

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Perf_tests)


    
BOOST_AUTO_TEST_SUITE_END()
