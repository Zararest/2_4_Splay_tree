#include "Splay_tree.hpp"
#include "../AVL_tree/headers/AVL_tree.hpp"

#include <set>

#define MAXLEN 100
#define NUM_OF_MEASUR 10
#define MAX_ROW_SIZE 30
#define NUM_OF_CHUNKS 30

class Test_tree{

protected:

    FILE* input_file = nullptr;
    FILE* request_file = nullptr;
    FILE* answers_file = nullptr;

    Splay_tree<int> tree;
    std::set<int> set;

public:

    Test_tree(const char* input_name, const char* request_name, const char* answers_name);
    Test_tree(const Test_tree&) = delete;
    Test_tree(Test_tree&&) = delete;
    virtual ~Test_tree();

    void find(const char* out_name);
    void range_requests(const char* out_name);
    void copy_assign(const char* out_name);
    void move_assign(const char* out_name);

    long splay_tree_time(const char* out_name);
    long set_time(const char* out_name);
};

class Perf_test_tree final: public Test_tree{

    AVL_tree AVL;

public:

    Perf_test_tree(const char* input_name, const char* request_name, const char* answers_name);
    Perf_test_tree(const Perf_test_tree&) = delete;
    Perf_test_tree(Perf_test_tree&&) = delete;
    ~Perf_test_tree(){};

    void check_AVL_tree(const char* out_name);
    void perf_test(std::ostream& answers);

    void print_distribution(const char* distr_name, std::ofstream& result);
};