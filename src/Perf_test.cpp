#include "./headers/Test.h"

Perf_test_tree::Perf_test_tree(const char* input_name, const char* request_name, const char* answers_name):
    Test_tree(input_name, request_name, answers_name){

    int tmp_elem = 0, scan_ret = 0;
    fseek(input_file, 0, SEEK_SET);

    while ((scan_ret = fscanf(input_file, "%d", &tmp_elem)) > 0){
        
        AVL.add_new_elem(tmp_elem);
    }
}

void Perf_test_tree::check_AVL_tree(const char* out_name){

    int left_elem = 0, right_elem = 0;
    FILE* out_file = fopen(out_name, "w");
    assert(out_file != nullptr);

    while (fscanf(request_file, "%d %d", &left_elem, &right_elem) > 0){

        if (!tree.check_tree()){ fprintf(out_file, "error\n"); }

        fprintf(out_file, "%i\n", AVL.number_of_elems(left_elem, right_elem));
    }

    fclose(out_file);
}