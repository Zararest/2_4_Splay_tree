#pragma once 

#include <cassert>
#include <fstream>
#include <exception>
#include <vector>

template <typename T_key>
void Node<T_key>::copy_node_data(Node<T_key>* node_to_copy) noexcept(std::is_nothrow_copy_constructible<T_key>::value){

    if (node_to_copy == nullptr){ return; }

    node_key = node_to_copy->node_key;
    size_of_left_tree = node_to_copy->size_of_left_tree;
    size_of_right_tree = node_to_copy->size_of_right_tree;
}

template <typename T_key>
void delete_tree_global(Node<T_key>* root) noexcept{

    if (root == nullptr){ return; }

    Node<T_key>* cur_node = root;
    Node<T_key>* tmp_right = nullptr;
    int tree_size = root->get_left_tree_size() + root->get_right_tree_size(); 
    std::vector<Node<T_key>*> path_stack;
    path_stack.reserve(tree_size);

    while (cur_node != nullptr || path_stack.size() != 0){
        
        if (path_stack.size() != 0){

            cur_node = path_stack.back();
            tmp_right = cur_node->go_right();
            path_stack.pop_back();
            delete cur_node;
            
            cur_node = tmp_right;
        }

        while (cur_node != nullptr){

            path_stack.push_back(cur_node);
            cur_node = cur_node->go_left();
        }
    }
}

template <typename T_key>
void Node<T_key>::delete_tree(Node<T_key>* root) noexcept{

    delete_tree_global(root);
}

template <typename T_key>
void Node<T_key>::tree_walk(Node<T_key>* cur_node, Node<T_key>* new_tree_cur_node){

    int num_of_nodes = cur_node->size_of_left_tree + cur_node->size_of_right_tree;
    int num_of_copy_nodes = 0;

    while (num_of_copy_nodes < num_of_nodes){

        if (cur_node->left != nullptr && new_tree_cur_node->left == nullptr){

            new_tree_cur_node->left = new Node<T_key>(cur_node->left->node_key, new_tree_cur_node);
            new_tree_cur_node->left->copy_node_data(cur_node->left);
            num_of_copy_nodes++;
            
            new_tree_cur_node = new_tree_cur_node->left;
            cur_node = cur_node->left;
        } else{

            if (cur_node->right != nullptr && new_tree_cur_node->right == nullptr){

                new_tree_cur_node->right = new Node<T_key>(cur_node->right->node_key, new_tree_cur_node);
                new_tree_cur_node->right->copy_node_data(cur_node->right);
                num_of_copy_nodes++;

                new_tree_cur_node = new_tree_cur_node->right;
                cur_node = cur_node->right;
            } else{

                if (new_tree_cur_node->prev != nullptr){

                    new_tree_cur_node = new_tree_cur_node->prev;
                    cur_node = cur_node->prev;
                }
            }
        }
    }
}

template <typename T_key>
Node<T_key>* Node<T_key>::copy_tree(Node<T_key>* old_tree, Node<T_key>*& mount_node){

    if (old_tree == nullptr){ return nullptr; }

    mount_node = new Node<T_key>(old_tree->node_key, nullptr);
    Node<T_key>* new_tree_root = mount_node;
    mount_node->copy_node_data(old_tree);

    tree_walk(old_tree, mount_node);   
    
    return new_tree_root;
}

template <typename T_key>
Node<T_key>* Node<T_key>::split_left() noexcept{

    Node<T_key>* ret_val = left;

    if (left != nullptr){

        left->prev = nullptr;
    }

    size_of_left_tree = 0;
    left = nullptr;

    return ret_val;
}

template <typename T_key>
Node<T_key>* Node<T_key>::split_right() noexcept{

    Node<T_key>* ret_val = right;

    if (right != nullptr){

        right->prev = nullptr;
    }

    size_of_right_tree = 0;
    right = nullptr;

    return ret_val;
}

template <typename T_key>
void Node<T_key>::add_left(Node<T_key>* new_left) noexcept{

    if (new_left != nullptr){

        size_of_left_tree = new_left->size_of_left_tree + new_left->size_of_right_tree + 1;
        left = new_left;
        new_left->prev = this;
    } else{

        left = nullptr;
        size_of_left_tree = 0;
    }
}

template <typename T_key>
void Node<T_key>::add_right(Node<T_key>* new_right) noexcept{

    if (new_right != nullptr){

        size_of_right_tree = new_right->size_of_left_tree + new_right->size_of_right_tree + 1;
        right = new_right;
        new_right->prev = this;
    } else{

        right = nullptr;
        size_of_right_tree = 0;
    }
}

template <typename T_key>
void Node<T_key>::print_node(std::ostream& outp_stream) const{
    
    outp_stream << '"' << this << '"' << " [label = \"" << "key " << node_key << "\" fillcolor=green]" << std::endl;

    if (left != nullptr && right != nullptr){

        outp_stream << "{ rank = same " << '"' << right << '"' << '"' << left << "\"}" << std::endl;
    }

    if (left != nullptr){

        outp_stream << '"' << this << '"' << " -> " << '"' << left << '"' << std::endl;
        left->print_node(outp_stream);
    }

    if (right != nullptr){

        outp_stream << '"' << this << '"' << " -> " << '"' << right << '"' << std::endl;
        right->print_node(outp_stream);
    }

    if (prev != nullptr){

        outp_stream << '"' << this << '"' << " -> " << '"' << prev << '"' << std::endl;
    }
}

template <typename T_key>
Splay_tree<T_key>::Splay_tree(const Splay_tree<T_key>& old_tree){

    Splay_tree<T_key> tmp_tree;
    Node<T_key>::copy_tree(old_tree.root, tmp_tree.root);

    std::swap(root, tmp_tree.root);
}

template <typename T_key>
Splay_tree<T_key>::Splay_tree(Splay_tree<T_key>&& rv_tree) noexcept{

    std::swap(root, rv_tree.root);
}

template <typename T_key>
void Splay_tree<T_key>::delete_tree() noexcept{

    delete_tree_global(root);
}

template <typename T_key>
Splay_tree<T_key>& Splay_tree<T_key>::operator =(const Splay_tree<T_key>& old_tree){

    Splay_tree<T_key> tmp_tree;
    Node<T_key>::copy_tree(old_tree.root, tmp_tree.root);

    std::swap(root, tmp_tree.root);

    return *this;
}

template <typename T_key>
Splay_tree<T_key>& Splay_tree<T_key>::operator =(Splay_tree<T_key>&& rv_tree) noexcept{

    if (&rv_tree == this){ return *this; }

    std::swap(root, rv_tree.root);

    return *this;
}

template <typename T_key>
void Splay_tree<T_key>::right_rotation(Node<T_key>* cur_node) noexcept{

    if (cur_node == nullptr){ return; }
    Node<T_key>* parent = cur_node->go_back();
    if (parent == nullptr){ return; }

    Node<T_key>* new_patrents_left = cur_node->split_right();
    Node<T_key>* grandparent = parent->go_back();
    bool parent_is_left = parent->is_left();
    bool parent_is_right = parent->is_right();

    assert(cur_node->is_left());
    cur_node->is_left();
    parent->split_left();
    parent->add_left(new_patrents_left);

    cur_node->add_right(parent);

    if (parent_is_left){ grandparent->add_left(cur_node); }
    if (parent_is_right){ grandparent->add_right(cur_node); }
}

template <typename T_key>
void Splay_tree<T_key>::left_rotation(Node<T_key>* cur_node) noexcept{

    if (cur_node == nullptr){ return; }
    Node<T_key>* parent = cur_node->go_back();
    if (parent == nullptr){ return; }

    Node<T_key>* new_patrents_right = cur_node->split_left();
    Node<T_key>* grandparent = parent->go_back();
    bool parent_is_left = parent->is_left();
    bool parent_is_right = parent->is_right();

    assert(cur_node->is_right());
    cur_node->is_right();
    parent->split_right();
    parent->add_right(new_patrents_right);

    cur_node->add_left(parent);

    if (parent_is_left){ grandparent->add_left(cur_node); }
    if (parent_is_right){ grandparent->add_right(cur_node); }
}

template <typename T_key>
void Splay_tree<T_key>::right_zig_zig(Node<T_key>* cur_node) noexcept{

    if (cur_node == nullptr){ return; }
    Node<T_key>* parent = cur_node->go_back();
    if (parent == nullptr){ return; }
    Node<T_key>* grandparent = parent->go_back();
    if (grandparent == nullptr){ return; }

    right_rotation(parent);
    right_rotation(cur_node);
}

template <typename T_key>
void Splay_tree<T_key>::left_zig_zig(Node<T_key>* cur_node) noexcept{

    if (cur_node == nullptr){ return; }
    Node<T_key>* parent = cur_node->go_back();
    if (parent == nullptr){ return; }
    Node<T_key>* grandparent = parent->go_back();
    if (grandparent == nullptr){ return; }

    left_rotation(parent);
    left_rotation(cur_node);
}

template <typename T_key>
void Splay_tree<T_key>::right_zig_zag(Node<T_key>* cur_node) noexcept{

    if (cur_node == nullptr){ return; }
    Node<T_key>* parent = cur_node->go_back();
    if (parent == nullptr){ return; }
    Node<T_key>* grandparent = parent->go_back();
    if (grandparent == nullptr){ return; }

    left_rotation(cur_node);
    right_rotation(cur_node);
}

template <typename T_key>
void Splay_tree<T_key>::left_zig_zag(Node<T_key>* cur_node) noexcept{

    if (cur_node == nullptr){ return; }
    Node<T_key>* parent = cur_node->go_back();
    if (parent == nullptr){ return; }
    Node<T_key>* grandparent = parent->go_back();
    if (grandparent == nullptr){ return; }

    right_rotation(cur_node);
    left_rotation(cur_node);
}

template <typename T_key>
int Splay_tree<T_key>::choose_rootation(Node<T_key>* cur_node) const noexcept{

    if (cur_node == nullptr){ return Nothing; }
    Node<T_key>* parent = cur_node->go_back();
    if (parent == nullptr){ return Nothing; }
    Node<T_key>* grandparent = parent->go_back();

    if (grandparent == nullptr){

        if (cur_node->is_left()){

            return Right;
        } else{
            
            return Left;
        }
    }

    if (parent->is_left()){

        if (cur_node->is_left()){

            return Right_zig_zig;
        } else{

            return Right_zig_zag;
        }
    } else{

        if (cur_node->is_right()){

            return Left_zig_zig;
        } else{
            
            return Left_zig_zag;
        }
    }
}

template <typename T_key>
void Splay_tree<T_key>::pull_node_up(Node<T_key>* cur_node) noexcept{

    int cur_rotation = 0;

    while ((cur_rotation = choose_rootation(cur_node)) != Nothing){
    
        switch (cur_rotation){

            case Left:
                left_rotation(cur_node);
                break;
            
            case Right:
                right_rotation(cur_node);
                break;

            case Left_zig_zig:;
                left_zig_zig(cur_node);
                break;

            case Right_zig_zig:
                right_zig_zig(cur_node);
                break;

            case Left_zig_zag:
                left_zig_zag(cur_node);
                break;

            case Right_zig_zag:
                right_zig_zag(cur_node);
                break;
        }
    }

    root = cur_node;
}

template <typename T_key>
Node<T_key>* Splay_tree<T_key>::find_nearest(T_key new_key){

    if (root == nullptr){ return nullptr; }

    Node<T_key> tmp_node{new_key};
    Node<T_key>* cur_node = root;
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

template <typename T_key>
bool Splay_tree<T_key>::check_sub_tree(Node<T_key>* cur_node) const{

    if (cur_node == nullptr){ return true; }

    if (!cur_node->is_right() && !cur_node->is_left()){ return false; }

    if (cur_node->go_left() != nullptr && *cur_node <= *cur_node->go_left()){ return false; }
    if (cur_node->go_right() != nullptr && *cur_node >= *cur_node->go_right()){ return false; }

    if (cur_node->is_right()){

        int prev_right_tree_size = cur_node->go_back()->get_right_tree_size();
        int cur_tree_size = cur_node->get_right_tree_size() + cur_node->get_left_tree_size() + 1;

        if (prev_right_tree_size != cur_tree_size){ return false; }
    } else{

        int prev_left_tree_size = cur_node->go_back()->get_left_tree_size();
        int cur_tree_size = cur_node->get_right_tree_size() + cur_node->get_left_tree_size() + 1;

        if (prev_left_tree_size != cur_tree_size){ return false; }
    }

    return check_sub_tree(cur_node->go_left()) && check_sub_tree(cur_node->go_right());
}

template <typename T_key>
bool Splay_tree<T_key>::check_tree() const{

    if (root != nullptr){

        return check_sub_tree(root->go_right()) && check_sub_tree(root->go_left());
    }

    return true; 
}

template <typename T_key>
void Splay_tree<T_key>::add_new_elem(T_key new_elem){

    if (root == nullptr){

        root = new Node<T_key>(new_elem);
        return;
    }

    Node<T_key>* new_node = new Node<T_key>(new_elem);

    Node<T_key>* nearest_elem = find_nearest(new_elem);
    Node<T_key>* new_left = nullptr;
    Node<T_key>* new_right = nullptr;
    assert(nearest_elem != nullptr);

    pull_node_up(nearest_elem);

    if (*new_node > *nearest_elem){
        
        new_right = nearest_elem->go_right();
        nearest_elem->split_right();
        new_left = nearest_elem;
    } else{

        new_left = nearest_elem->go_left();
        nearest_elem->split_left();
        new_right = nearest_elem;
    }

    new_node->add_left(new_left);
    new_node->add_right(new_right);
    root = new_node;
}

template <typename T_key>
bool Splay_tree<T_key>::find_elem(T_key elem){
    
    Node<T_key>* nearest = find_nearest(elem);
    Node<T_key> tmp_node(elem);

    if (nearest != nullptr && *nearest == tmp_node){ 
        
        pull_node_up(nearest);

        return true; 
    }

    return false;
}

template <typename T_key>
Node<T_key>* Splay_tree<T_key>::get_median(Node<T_key>& cur_left, T_key median){

    Node<T_key> tmp_node{median};
    Node<T_key>* ret_node = &cur_left;
    Node<T_key>* prev_node = nullptr;

    while ((prev_node = ret_node->go_back()) != nullptr 
            && *ret_node < tmp_node){
        
        ret_node = prev_node;
    }

    return ret_node;
}

template <typename T_key>
int Splay_tree<T_key>::number_of_elems(T_key from, T_key to){

    if (from > to){ return -1; }

    Node<T_key>* left_limit = find_nearest(from);
    int num_of_greater_than_left = num_of_greater_elems;
    Node<T_key>* right_limit = find_nearest(to);
    int num_of_greater_than_right = num_of_greater_elems;

    int ret_val = num_of_greater_than_left - num_of_greater_than_right + 1;

    if (root->get_key() < from || root->get_key() > to){

        pull_node_up(get_median(*left_limit, (from + to) / 2));
    }
    
    ret_val -= (left_limit->get_key() < from) + (right_limit->get_key() > to);

    return ret_val;
}   

template <typename T_key>
void Splay_tree<T_key>::dump_graphviz(const char* out_name) const{

    assert(check_tree());
    std::ofstream out_file(out_name);
    if (!out_file.is_open()){

        std::cerr << "Can't open file" << std::endl;
    }

    out_file << "digraph Dump{ node[color=red,fontsize=14, style=filled]" << std::endl;
    root->print_node(out_file);
    out_file << "}" << std::endl;

    out_file.close();
}