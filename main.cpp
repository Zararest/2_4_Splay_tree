#include "src/headers/Splay_tree.h"

#include <fstream>

#define NUM_OF_ELEMS 6

int main(){

    Splay_tree new_tree;
    std::ifstream input("../bin/find/input");
    std::ofstream output("../bin/out");
    std::ifstream req("../bin/find/requests");

    int tmp_elem = 0;

    for (int i = 0; i < 100; i++){

        input >> tmp_elem;
        new_tree.add_new_elem(tmp_elem);
    }

    new_tree.dump_graphviz("../bin/graph.dot");

    for (int i = 0; i < 10; i++){

        req >> tmp_elem;
        output << new_tree.find_elem(tmp_elem) << std::endl;
        std::cout << new_tree.check_tree() << std::endl;
    }
}