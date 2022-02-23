#include "src/headers/Splay_tree.hpp"

#include <fstream>

#define NUM_OF_ELEMS 6

int main(){

    Splay_tree<int> new_tree;

    int num_of_elems = 0, num_of_req = 0;
    int tmp_elem = 0, left_elem = 0, right_elem = 0;

    std::cin >> num_of_elems;

    for (int i = 0; i < num_of_elems; i++){

        std::cin >> tmp_elem;
        new_tree.add_new_elem(tmp_elem);
    }

    std::cin >> num_of_req;

    for (int i = 0; i < num_of_req; i++){

        std::cin >> left_elem >> right_elem;
        std::cout << new_tree.number_of_elems(left_elem, right_elem) << " ";
    }
}