#include "src/headers/Test.h"

#define BOOST_TEST_MODULE First_TestSuite
#include <boost/test/included/unit_test.hpp>

#include <cstdlib>
#include <unistd.h>

BOOST_AUTO_TEST_SUITE(Splay_tree_tests)

BOOST_AUTO_TEST_CASE(find){

    int ret = chdir("../bin/find");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input"};
    char out_name[MAXLEN] = {"out"};

    Test_tree find_test(input_name, "requests", "ans");

    find_test.find(out_name);

    int diff_ret = std::system("diff ans out > ../out");

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(move_assign){

    int ret = chdir("../assign");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_move"};
    char out_name[MAXLEN] = {"out_move"};

    Test_tree move_test(input_name, "requests_move", "ans_move");

    move_test.move_assign(out_name);

    int diff_ret = std::system("diff ans_move out_move > ../out");

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(copy_assign){

    char input_name[MAXLEN] = {"input_copy"};
    char out_name[MAXLEN] = {"out_copy"};

    Test_tree copy_test(input_name, "requests_copy", "ans_copy");

    copy_test.copy_assign(out_name);

    int diff_ret = std::system("diff ans_copy out_copy > ../out");

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(range_find){
    
    int ret = chdir("../Range_find_tests/range_find");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_range"};
    char out_name[MAXLEN] = {"out_range"};

    Test_tree range_test(input_name, "requests_range", "ans_range");

    range_test.range_requests(out_name);

    int diff_ret = std::system("diff ans_range out_range > ../../out");

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(range_find_2){

    int ret = chdir("../range_find_2");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_range_2"};
    char out_name[MAXLEN] = {"out_range_2"};

    Test_tree range_test(input_name, "requests_range_2", "ans_range_2");

    range_test.range_requests(out_name);

    int diff_ret = std::system("diff ans_range_2 out_range_2 > ../../out");

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(range_find_3){
    
    int ret = chdir("../range_find_3");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_range_3"};
    char out_name[MAXLEN] = {"out_range_3"};

    Test_tree range_test(input_name, "requests_range_3", "ans_range_3");

    range_test.range_requests(out_name);

    int diff_ret = std::system("diff ans_range_3 out_range_3 > ../../out");

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(range_find_4){

    int ret = chdir("../range_find_4");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_range_4"};
    char out_name[MAXLEN] = {"out_range_4"};

    Test_tree range_test(input_name, "requests_range_4", "ans_range_4");

    range_test.range_requests(out_name);

    int diff_ret = std::system("diff ans_range_4 out_range_4 > ../../out");

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Perf_tests)

BOOST_AUTO_TEST_CASE(perf){

    int ret = chdir("../../Set_tests/perf");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_perf_test"};
    char out_name[MAXLEN] = {"out_perf_test"};

    Test_tree perf_test(input_name, "requests_perf_test", "ans_perf_test");

    long splay_time = perf_test.splay_tree_time(out_name);
    int diff_ret = std::system("diff ans_perf_test out_perf_test > ../../out");

    long set_time = perf_test.set_time(out_name);
    diff_ret += std::system("diff ans_perf_test out_perf_test > ../../out");

    std::cout << "splay time = " << splay_time << std::endl;
    std::cout << "set time = " << set_time << std::endl;
    std::cout << "-----------------" << std::endl;

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(perf_2){

    int ret = chdir("../perf_2");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_perf_test"};
    char out_name[MAXLEN] = {"out_perf_test"};

    Test_tree perf_test(input_name, "requests_perf_test", "ans_perf_test");

    long splay_time = perf_test.splay_tree_time(out_name);
    int diff_ret = std::system("diff ans_perf_test out_perf_test > ../../out");

    long set_time = perf_test.set_time(out_name);
    diff_ret += std::system("diff ans_perf_test out_perf_test > ../../out");

    std::cout << "splay time = " << splay_time << std::endl;
    std::cout << "set time = " << set_time << std::endl;
    std::cout << "-----------------" << std::endl;

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}

BOOST_AUTO_TEST_CASE(perf_3){

    int ret = chdir("../perf_3");
    assert(ret == 0);
    char input_name[MAXLEN] = {"input_perf_test"};
    char out_name[MAXLEN] = {"out_perf_test"};

    Test_tree perf_test(input_name, "requests_perf_test", "ans_perf_test");

    long splay_time = perf_test.splay_tree_time(out_name);
    int diff_ret = std::system("diff ans_perf_test out_perf_test > ../../out");

    long set_time = perf_test.set_time(out_name);
    diff_ret += std::system("diff ans_perf_test out_perf_test > ../../out");

    std::cout << "splay time = " << splay_time << std::endl;
    std::cout << "set time = " << set_time << std::endl;
    std::cout << "-----------------" << std::endl;

    BOOST_REQUIRE_EQUAL(diff_ret, 0);
}
    
BOOST_AUTO_TEST_SUITE_END()
