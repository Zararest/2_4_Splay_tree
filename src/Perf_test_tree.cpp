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

    fseek(request_file, 0, SEEK_SET);

    while (fscanf(request_file, "%d %d", &left_elem, &right_elem) > 0){

        if (!tree.check_tree()){ fprintf(out_file, "error\n"); }

        fprintf(out_file, "%i\n", AVL.number_of_elems(left_elem, right_elem));
    }

    fclose(out_file);
}

void Perf_test_tree::perf_test(std::ostream& answers){

    long AVL_time = 0, Splay_time = 0, start_time = 0, end_time = 0;
    long AVL_total_time = 0, Splay_total_time = 0;
    int left_elem = 0, right_elem = 0;

    for (int i = 0; i < NUM_OF_MEASUR; i++){

        fseek(request_file, 0, SEEK_SET);

        start_time = clock();
        while (fscanf(request_file, "%d %d", &left_elem, &right_elem) > 0){

            tree.number_of_elems(left_elem, right_elem);
        }
        end_time = clock();
        Splay_time = end_time - start_time;

        fseek(request_file, 0, SEEK_SET);

        start_time = clock();
        while (fscanf(request_file, "%d %d", &left_elem, &right_elem) > 0){

            AVL.number_of_elems(left_elem, right_elem);
        }
        end_time = clock();
        AVL_time = end_time - start_time;
        
        Splay_total_time += Splay_time;
        AVL_total_time += AVL_time;

        answers << "(Splay, AVL) = { " << Splay_time << ", " << AVL_time << "}" << std::endl;
    }

    answers << "average time: Splay tree: " << (Splay_total_time / NUM_OF_MEASUR) << ", AVL tree: " << (AVL_total_time / NUM_OF_MEASUR) << std::endl;
}