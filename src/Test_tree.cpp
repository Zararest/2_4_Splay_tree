#include "headers/Test.h"

#include <cassert>

Test_tree::Test_tree(const char* input_name, const char* request_name, const char* answers_name){

    input_file = fopen(input_name, "r");
    assert(input_file != nullptr);
    request_file = fopen(request_name, "r");
    assert(request_file != nullptr);
    answers_file = fopen(answers_name, "r");
    assert(answers_file != nullptr);

    int tmp_elem = 0;

    while (fscanf(input_file, "%d", &tmp_elem) != 0){

        tree.add_new_elem(tmp_elem);
    }
}

Test_tree::~Test_tree(){

    fclose(input_file);
    fclose(request_file);
    fclose(answers_file);
}

void Test_tree::find(const char* out_name){
    
    int tmp_elem = 0;
    FILE* out_file = fopen(out_name, "w");

    while (fscanf(request_file, "%d", &tmp_elem) != 0){

        if (!tree.check_tree()){ fprintf(out_file, "error\n"); }
        
        fprintf(out_file, "%i\n", tree.find_elem(tmp_elem));
    }
}

