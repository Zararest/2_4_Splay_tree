#include "Splay_tree.h"

#define MAXLEN 100

class Test_tree{

    FILE* input_file = nullptr;
    FILE* request_file = nullptr;
    FILE* answers_file = nullptr;

    Splay_tree tree;

public:

    Test_tree(const char* input_name, const char* request_name, const char* answers_name);
    Test_tree(const Test_tree&) = delete;
    Test_tree(Test_tree&&) = delete;
    ~Test_tree();

    void find(const char* out_name);
    void range_requests(const char* out_name);
    void copy_assign(const char* out_name);
    void move_assign(const char* out_name);

    long splay_tree_time(const char* out_name);
    long set_time(const char* out_name);
};
