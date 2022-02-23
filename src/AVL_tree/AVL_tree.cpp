#include "headers/AVL_tree.hpp"

typedef struct Coordinates_struct{

    int x;
    int y;
} Coordinates;

Node_AVL::Node_AVL(T_key new_key, Node_AVL* prev_node): node_key(new_key), prev(prev_node){}

bool Node_AVL::check_balance() const{

    if ((depth_of_left - depth_of_right > 1) || (depth_of_left - depth_of_right < -1)){ 

        return false;
    } else{

        return true;
    }
}

int Node_AVL::choose_rotation() const{

    if (check_balance() == true){

        return none;
    }

    if (depth_of_left - depth_of_right > 1){

        if (left->depth_of_left - left->depth_of_right >= 0){

            return left_rot;
        } else{

            return big_left_rot;
        }
    } else{

        if (right->depth_of_right - right->depth_of_left >= 0){

            return right_rot;
        } else{

            return big_right_rot;
        }
    }
}

bool Node_AVL::check_data(){

    if (left != nullptr){

        if (depth_of_left - 1 != std::max(left->depth_of_left, left->depth_of_right)){

            node_error = left_depth;
            return false;
        }

        if (size_of_left_tree - 1 != left->size_of_left_tree + left->size_of_right_tree){

            node_error = left_size;
            return false;
        }
    } else{

        if (size_of_left_tree != 0){

            node_error = left_size;
            return false;
        }

        if (depth_of_left != 0){

            node_error = left_depth;
            return false;
        }
    }

    if (right != nullptr){

        if (depth_of_right - 1 != std::max(right->depth_of_right, right->depth_of_left)){

            node_error = right_depth;
            return false;
        }

        if (size_of_right_tree - 1 != right->size_of_left_tree + right->size_of_right_tree){
            
            node_error = right_size;
            return false;
        }
    } else{

        if (size_of_right_tree != 0){

            node_error = right_size;
            return false;
        }

        if (depth_of_right != 0){

            node_error = right_depth;
            return false;
        }
    }

    return true;
}

void Node_AVL::left_rotation(){ 
    
    Node_AVL* cur_prev = prev;
    Node_AVL* cur_left = left;

    left = cur_left->right;
    if (left != nullptr){

        left->prev = this;
    }
    
    if (cur_prev != nullptr){

        if (cur_prev->left == this){

            cur_prev->left = cur_left;
            cur_left->prev = cur_prev;
        } else{

            cur_prev->right = cur_left;
            cur_left->prev = cur_prev;
        }
    } else{

        cur_left->prev = nullptr;
    }

    cur_left->right = this;
    prev = cur_left;

    fix_node_data();
    prev->fix_node_data();
}

void Node_AVL::right_rotation(){

    Node_AVL* cur_prev = prev;
    Node_AVL* cur_right = right;

    right = cur_right->left;
    if (right != nullptr){

        right->prev = this;
    }

    if (cur_prev != nullptr){

        if (cur_prev->left == this){

            cur_prev->left = cur_right;
            cur_right->prev = cur_prev;
        } else{

            cur_prev->right = cur_right;
            cur_right->prev = cur_prev;
        }
    } else{

        cur_right->prev = nullptr;
    }

    cur_right->left = this;
    prev = cur_right;

    fix_node_data();
    prev->fix_node_data();
}

void Node_AVL::big_left_rotation(){

    left->right_rotation();
    left_rotation();
}

void Node_AVL::big_right_rotation(){

    right->left_rotation();
    right_rotation();
}

void Node_AVL::fix_node_data(){

    depth_of_left = 0;
    depth_of_right = 0;
    size_of_left_tree = 0;
    size_of_right_tree = 0;

    if (left != nullptr){

        depth_of_left = std::max(left->depth_of_left, left->depth_of_right) + 1;
        size_of_left_tree = left->size_of_left_tree + left->size_of_right_tree + 1;
    }

    if (right != nullptr){

        depth_of_right = std::max(right->depth_of_left, right->depth_of_right) + 1;
        size_of_right_tree = right->size_of_left_tree + right->size_of_right_tree + 1;
    }
}

void Node_AVL::add_left_node(T_key new_key){

    assert(left == nullptr);

    depth_of_left = 1;
    size_of_left_tree = 1;

    left = new Node_AVL(new_key, this);
}

void Node_AVL::add_right_node(T_key new_key){

    assert(right == nullptr);

    depth_of_right = 1;
    size_of_right_tree = 1;

    right = new Node_AVL(new_key, this);
}


bool go_to_the_left(const int x, Node_AVL*& cur_node, Coordinates& cur_node_coord, const int vertical_size){

    if (cur_node_coord.x - x >= pow(2, vertical_size - cur_node_coord.y - 1)){

        if (cur_node->go_back() == nullptr) return false;
        
        if (cur_node->go_back()->go_left() == cur_node){

            cur_node_coord.x -= pow(2, vertical_size - cur_node_coord.y - 1);
        } else{

            cur_node_coord.x += pow(2, vertical_size - cur_node_coord.y - 1);
        }

        cur_node = cur_node->go_back();
        cur_node_coord.y--;
    } else{

        if (cur_node->go_right() == nullptr) return false;
        
        cur_node = cur_node->go_right();
        cur_node_coord.x -= pow(2, vertical_size - cur_node_coord.y - 2);
        cur_node_coord.y++;
    }

    return true;
}

bool go_to_the_right(const int x, Node_AVL*& cur_node, Coordinates& cur_node_coord, const int vertical_size){

    if (x - cur_node_coord.x >= pow(2, vertical_size - cur_node_coord.y - 1)){

        if (cur_node->go_back() == nullptr) return false;
        
        if (cur_node->go_back()->go_left() == cur_node){

            cur_node_coord.x -= pow(2, vertical_size - cur_node_coord.y - 1);
        } else{

            cur_node_coord.x += pow(2, vertical_size - cur_node_coord.y - 1);
        }
        cur_node = cur_node->go_back();
        cur_node_coord.y--;
    } else{

        if (cur_node->go_left() == nullptr) return false;
        
        cur_node = cur_node->go_left();
        cur_node_coord.x += pow(2, vertical_size - cur_node_coord.y - 2);
        cur_node_coord.y++;
    }

    return true;
}

bool go_to_node(const int x, Node_AVL*& cur_node, Coordinates& cur_node_coord, const int vertical_size){

    bool node_has_found = false;

    if (cur_node_coord.x == x){

        node_has_found = true;
        return true;
    }

    while (!node_has_found){

        if (x < cur_node_coord.x){

            if (!go_to_the_left(x, cur_node, cur_node_coord, vertical_size)) return false;
        } else{

            if (!go_to_the_right(x, cur_node, cur_node_coord, vertical_size)) return false;
        }

        if (cur_node_coord.x == x){

            node_has_found = true;
        }
    }

    return true;
}

void AVL_tree::copy_tree(const AVL_tree& old_tree, AVL_tree* cur_tree){

    Node_AVL* cur_node = old_tree.root;
    Coordinates cur_node_coord{0, 0};
    int  vertical_tree_size = std::max(old_tree.root->get_left_depth(), old_tree.root->get_right_depth()) + 1;
    int horizontal_tree_size = pow(2, vertical_tree_size), depth = 0;

    while(cur_node->go_right() != nullptr){

        cur_node = cur_node->go_right();
        depth++;
    }
    cur_node_coord.y = depth;

    for (int x = 0; x < horizontal_tree_size; x++){

        if (go_to_node(x, cur_node, cur_node_coord, vertical_tree_size)){

            cur_tree->add_new_elem(cur_node->get_key());
        }
    }
}

AVL_tree::AVL_tree(const AVL_tree& old_tree){

    copy_tree(old_tree, this);
}

AVL_tree::AVL_tree(AVL_tree&& tmp_obj){

    std::swap(root, tmp_obj.root);
    error_occurred = tmp_obj.error_occurred;
    number_of_rotations = tmp_obj.number_of_rotations;
}

AVL_tree& AVL_tree::operator =(AVL_tree&& tmp_obj){

    if (this == &tmp_obj){

        return *this;
    }

    std::swap(root, tmp_obj.root);
    
    error_occurred = tmp_obj.error_occurred;
    number_of_rotations = tmp_obj.number_of_rotations;

    return *this;
}

AVL_tree& AVL_tree::operator =(const AVL_tree& old_tree){

    if (this == &old_tree){

        return *this;
    }

    AVL_tree tmp_object_with_prev_data(static_cast<AVL_tree&&>(*this));

    if (old_tree.root != nullptr){

        copy_tree(old_tree, this);
    }

    return *this;
}

AVL_tree::~AVL_tree(){

    Node_AVL* cur_node = root;

    if (root != nullptr){

        while ((cur_node->go_left() != nullptr) || (cur_node->go_right() != nullptr) || (cur_node->go_back() != nullptr)){

            if (cur_node->go_left() != nullptr){

                cur_node = cur_node->go_left();
            } else{

                if (cur_node->go_right() != nullptr){

                    cur_node = cur_node->go_right();
                } else{

                    if (cur_node->go_back()->go_right() == cur_node){

                        cur_node = cur_node->go_back();
                        cur_node->delete_right();
                    } else{
                        
                        cur_node = cur_node->go_back();
                        cur_node->delete_left();
                    }
                }
            }
        }
        delete root;
    }
}

bool AVL_tree::check_add_new_elem_condition(T_key new_key){

    if (find_elem(new_key)){

        std::cerr << "Error: This element already exists in the tree. Can't add new element[m " << new_key << "]\n";
        error_occurred = true;
        return false;
    }

    return true;
}

long AVL_tree::add_new_elem(T_key new_key){

    if (root == nullptr){

        root = new Node_AVL(new_key);
        return 0;
    }

    if (find_elem(new_key) == true) return 0;

    Node_AVL* cur_node = root;
    bool elem_has_been_added = false;
    long number_of_rot_before = number_of_rotations;

    while (!elem_has_been_added){
        
        if (new_key < cur_node->get_key()){
            
            cur_node->increase_size_of_left();

            if (cur_node->go_left() == nullptr){

                cur_node->add_left_node(new_key);
                balance_tree(cur_node->go_left());
                elem_has_been_added = true;
            } else{

                cur_node = cur_node->go_left();
            }
        } else{
            
            cur_node->increase_size_of_right();

            if (cur_node->go_right() == nullptr){

                cur_node->add_right_node(new_key);
                balance_tree(cur_node->go_right());
                elem_has_been_added = true;
            } else{

                cur_node = cur_node->go_right();
            }
        }
        assert(cur_node != nullptr);
    }

    if (root->go_back() != nullptr){

        root = root->go_back();
        assert(root->go_back() == nullptr);
    }
    assert(root->check_balance() == true);   

    return number_of_rotations - number_of_rot_before;
}

void AVL_tree::balance_tree(Node_AVL* cur_tree_root){

    switch (cur_tree_root->choose_rotation()){

    case left_rot:
        cur_tree_root->left_rotation();
        cur_tree_root = cur_tree_root->go_back();
        number_of_rotations++;
        break;

    case right_rot:
        cur_tree_root->right_rotation();
        cur_tree_root = cur_tree_root->go_back();
        number_of_rotations++;
        break;

    case big_left_rot:
        cur_tree_root->big_left_rotation();
        cur_tree_root = cur_tree_root->go_back();
        number_of_rotations += 2;
        break;

    case big_right_rot:
        cur_tree_root->big_right_rotation();
        cur_tree_root = cur_tree_root->go_back();
        number_of_rotations += 2;
        break;

    case none:
        cur_tree_root->fix_node_data();
    }

    if (cur_tree_root->go_back() != nullptr){

        cur_tree_root->go_back()->fix_node_data();
        balance_tree(cur_tree_root->go_back());
    }
}

void print_tree(std::ostream& outp_stream, Node_AVL* cur_node){

    if (cur_node != nullptr){

        print_tree(outp_stream, cur_node->go_left());
        cur_node->print_node(outp_stream);
        print_tree(outp_stream, cur_node->go_right());
    }
}

void AVL_tree::dump(std::ostream& outp_stream) const{

    outp_stream << "root: ";
    if (root != nullptr){

        root->print_node(outp_stream);
    } else{

        outp_stream << "null\n";
    }
    
    outp_stream << "number of rotations: " << number_of_rotations << '\n';
    print_tree(outp_stream, root);
}

Node_AVL* AVL_tree::find_elems_node(T_key elem) const{

    Node_AVL* cur_node = root;

    while (cur_node != nullptr){

        if (cur_node->get_key() == elem){

            return cur_node;
        }

        if (elem < cur_node->get_key()){

            cur_node = cur_node->go_left();
        } else{

            cur_node = cur_node->go_right();
        }
    }

    return nullptr;
}

bool AVL_tree::find_elem(T_key elem) const{
    
    if (find_elems_node(elem) != nullptr){

        return true;
    } else{

        return false;
    }
}

int AVL_tree::number_of_elems_less_than(int cur_elem) const{

    Node_AVL* cur_node = root;
    int elems_less_then = 0;

    while (cur_node != nullptr){

        if (cur_node->get_key() == cur_elem){

            return elems_less_then + cur_node->get_left_tree_size();
        }

        if (cur_elem < cur_node->get_key()){

            cur_node = cur_node->go_left();
        } else{

            elems_less_then += 1 + cur_node->get_left_tree_size();
            cur_node = cur_node->go_right();
        }
    }

    return elems_less_then;
}

bool AVL_tree::check_get_last_elem_condition(int degree_of_last_elem){

    if (root == nullptr){

        std::cerr << "Error: Tree is empty. Can't find last element[m " << degree_of_last_elem << "]\n";
        error_occurred = true;
        return false;
    }

    if (degree_of_last_elem < 1){

        std::cerr << "Error: Degree of the last element less is than 1. Can't find last element[m " << degree_of_last_elem << "]\n";
        error_occurred = true;
        return false;
    }

    if (degree_of_last_elem > root->get_left_tree_size() + root->get_right_tree_size() + 1){

        std::cerr << "Error: Degree of the last element is more than tree size. Can't find last element[m " << degree_of_last_elem << "]\n";
        error_occurred = true;
        return false;
    }

    return true;
}

T_key AVL_tree::get_last_elem(int degree_of_last_elem){

    bool elem_has_found = false;
    int elems_less_than_cur_node = 0;
    Node_AVL* cur_node = root;

    if (check_get_last_elem_condition(degree_of_last_elem) == false){

        return -1;
    }
    
    while (!elem_has_found){

        if (cur_node == nullptr){

            return -1;
        }

        if (degree_of_last_elem - 1 == elems_less_than_cur_node + cur_node->get_left_tree_size()){

            elem_has_found = true;
        } else{

            if (degree_of_last_elem - 1 < elems_less_than_cur_node + cur_node->get_left_tree_size()){

                cur_node = cur_node->go_left();
                assert(cur_node != nullptr);
            } else{

                elems_less_than_cur_node += 1 + cur_node->get_left_tree_size();
                cur_node = cur_node->go_right();
                assert(cur_node != nullptr);
            }
        }
    }
    
    return cur_node->get_key();
}

bool AVL_tree::check_error(){

    if (error_occurred){

        error_occurred = false;
        return false;
    } else{

        return true;
    }
}

Node_AVL* AVL_tree::find_nearest(T_key new_key){

    if (root == nullptr){ return nullptr; }

    Node_AVL tmp_node(new_key);
    Node_AVL* cur_node = root;
    bool not_found = true;

    num_of_smaller_elems = 0;
    num_of_greater_elems = 0;

    while (not_found){

        not_found = false;

        if (*cur_node == tmp_node){ 

            num_of_greater_elems += cur_node->get_right_tree_size();
            num_of_smaller_elems += cur_node->get_left_tree_size();    
            return cur_node; 
        }

        if (cur_node->go_left() != nullptr && *cur_node > tmp_node){

            num_of_greater_elems += cur_node->get_right_tree_size() + 1;
            cur_node = cur_node->go_left();
            not_found = true;
        }

        if (!not_found && cur_node->go_right() != nullptr && *cur_node < tmp_node){

            num_of_smaller_elems += cur_node->get_left_tree_size() + 1;
            cur_node = cur_node->go_right();
            not_found = true;
        }
    }

    num_of_greater_elems += cur_node->get_right_tree_size();
    num_of_smaller_elems += cur_node->get_left_tree_size();   
    
    return cur_node;
}

int AVL_tree::number_of_elems(int from, int to){

    Node_AVL tmp_left(from);
    Node_AVL tmp_right(to);
    Node_AVL* left_limit = find_nearest(from);
    int num_of_greater_than_left = num_of_greater_elems;
    Node_AVL* right_limit = find_nearest(to);
    int num_of_greater_than_right = num_of_greater_elems;

    int ret_val = num_of_greater_than_left - num_of_greater_than_right + 1;

    if (*left_limit < tmp_left){ ret_val--; }
    if (*right_limit > tmp_right){ ret_val--; }

    return ret_val;
}
