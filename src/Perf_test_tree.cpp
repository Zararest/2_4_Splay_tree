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

    for (int i = 0; i < 100 * NUM_OF_MEASUR; i++){ 
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

        // answers << "(Splay, AVL) = { " << Splay_time << ", " << AVL_time << "}" << std::endl;
    }

    answers << "average time: Splay tree: " << (Splay_total_time / NUM_OF_MEASUR) << ", AVL tree: " << (AVL_total_time / NUM_OF_MEASUR) << std::endl;
}

void Perf_test_tree::print_distribution(const char* distr_name, std::ofstream& result){

    std::ifstream input(distr_name);
    std::vector<int> distribution(1024, 0);
    int cur_num = 0, sum = 0, max_val = 0, max_num = 0;
    bool get_num = true;

    while (input.good()){

        input >> cur_num;

        while (distribution.size() < cur_num){

            distribution.resize(distribution.size() * 2);
            
            for (int i = distribution.size() / 2 - 1; i < distribution.size(); i++){

                distribution[i] = 0;
            }
        }

        distribution[cur_num]++;
        sum += cur_num;

        if (distribution[cur_num] > max_val){

            max_val = distribution[cur_num];
        }

        if (cur_num > max_num){

            max_num = cur_num;
        }
    }
    
    int size_of_symbol = max_val / MAX_ROW_SIZE + 1;
    int section_size = max_num / NUM_OF_CHUNKS;

    for (int i = 0; i < NUM_OF_CHUNKS; i++){

        int cur_sum = 0;

        for (int j = i * section_size; j < (i + 1) * section_size; j++){

            cur_sum += distribution[j];
        }

        int num_of_symbols = cur_sum / size_of_symbol;

        for (int j = 0; j < num_of_symbols; j++){
            
            std::cout << "=";
        }

        std::cout << std::endl;
    }
}