#include "headers/Test.h"

#include <cassert>
#include <ctime>
#include <iterator>
#include <fstream>

Test_tree::Test_tree(const char* input_name, const char* request_name, const char* answers_name){

    input_file = fopen(input_name, "r");
    assert(input_file != nullptr);
    request_file = fopen(request_name, "r");
    assert(request_file != nullptr);
    answers_file = fopen(answers_name, "r");
    assert(answers_file != nullptr);

    int tmp_elem = 0;
    int scan_ret = 0;

    while ((scan_ret = fscanf(input_file, "%d", &tmp_elem)) > 0){

        tree.add_new_elem(tmp_elem);
        set.insert(tmp_elem);
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
    assert(out_file != nullptr);

    while (fscanf(request_file, "%d", &tmp_elem) > 0){

        if (!tree.check_tree()){ fprintf(out_file, "error\n"); }
        
        fprintf(out_file, "%i\n", tree.find_elem(tmp_elem));
    }

    fclose(out_file);
}

void Test_tree::range_requests(const char* out_name){

    int left_elem = 0, right_elem = 0;
    FILE* out_file = fopen(out_name, "w");
    assert(out_file != nullptr);

    while (fscanf(request_file, "%d %d", &left_elem, &right_elem) > 0){

        if (!tree.check_tree()){ fprintf(out_file, "error\n"); }

        fprintf(out_file, "%i\n", tree.number_of_elems(left_elem, right_elem));
    }

    fclose(out_file);
}

void Test_tree::copy_assign(const char* out_name){

    Splay_tree new_tree;
    new_tree = tree;

    int tmp_elem = 0;
    FILE* out_file = fopen(out_name, "w");
    assert(out_file != nullptr);

    while (fscanf(request_file, "%d", &tmp_elem) > 0){

        if (!new_tree.check_tree()){ fprintf(out_file, "error\n"); }
        
        fprintf(out_file, "%i\n", new_tree.find_elem(tmp_elem));
    }

    fclose(out_file);
}

void Test_tree::move_assign(const char* out_name){

    Splay_tree new_tree;
    new_tree = tree;
    Splay_tree new_move_tree;
    new_move_tree = static_cast<Splay_tree&&>(new_tree);

    int tmp_elem = 0;
    FILE* out_file = fopen(out_name, "w");
    assert(out_file != nullptr);

    while (fscanf(request_file, "%d", &tmp_elem) > 0){

        if (!new_move_tree.check_tree()){ fprintf(out_file, "error\n"); }
        
        fprintf(out_file, "%i\n", new_move_tree.find_elem(tmp_elem));
    }

    fclose(out_file);
}

long Test_tree::splay_tree_time(const char* out_name){

    FILE* out_file = fopen(out_name, "w");
    assert(out_file != nullptr);

    int left_elem = 0, right_elem = 0;
    long start_time = clock(), end_time = 0;
    int count = 0;
    
    while (fscanf(request_file, "%d %d", &left_elem, &right_elem) > 0){

        fprintf(out_file, "%i\n", tree.number_of_elems(left_elem, right_elem));
        count++;
    }
    

    end_time = clock();

    fclose(out_file);

    return end_time - start_time;
}

long Test_tree::set_time(const char* out_name){

    std::ofstream out;
    out.open(out_name, std::ios::trunc);

    fseek(request_file, 0, SEEK_SET);

    int left_elem = 0, right_elem = 0, number_of_elems = 0;
    long start_time = clock(), end_time = 0;

    while (fscanf(request_file, "%d %d", &left_elem, &right_elem) > 0){
        
        out << std::distance(set.lower_bound(left_elem), set.upper_bound(right_elem)) << std::endl;
    }

    end_time = clock();

    out.close();

    return end_time - start_time;
}

