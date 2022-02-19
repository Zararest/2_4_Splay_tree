#include "headers/Splay_tree.h"

#include <cassert>
#include <fstream>
#include <exception>

void Node::copy_node_data(Node* node_to_copy) noexcept{

    if (node_to_copy == nullptr){ return; }

    node_key = node_to_copy->node_key;
    size_of_left_tree = node_to_copy->size_of_left_tree;
    size_of_right_tree = node_to_copy->size_of_right_tree;
}

void delete_tree_global(Node* root){

    Node* cur_node = root;

    if (root != nullptr){

        while ((cur_node->go_left() != nullptr) 
            || (cur_node->go_right() != nullptr) 
            || (cur_node->go_back() != nullptr)){

            if (cur_node->go_left() != nullptr){

                cur_node = cur_node->go_left();
            } else{

                if (cur_node->go_right() != nullptr){

                    cur_node = cur_node->go_right();
                } else{

                    if (cur_node->is_right()){

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

void Node::delete_tree(Node* root) noexcept{

    delete_tree_global(root);
}

void Node::_tree_walk(Node* cur_node, Node* new_tree_cur_node){

    int num_of_nodes = cur_node->size_of_left_tree + cur_node->size_of_right_tree;
    int num_of_copy_nodes = 0;

    while (num_of_copy_nodes < num_of_nodes){

        if (cur_node->left != nullptr && new_tree_cur_node->left == nullptr){

            new_tree_cur_node->left = new Node(cur_node->left->node_key, new_tree_cur_node);
            new_tree_cur_node->left->copy_node_data(cur_node->left);
            num_of_copy_nodes++;
            
            new_tree_cur_node = new_tree_cur_node->left;
            cur_node = cur_node->left;
        } else{

            if (cur_node->right != nullptr && new_tree_cur_node->right == nullptr){

                new_tree_cur_node->right = new Node(cur_node->right->node_key, new_tree_cur_node);
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

Node* Node::copy_tree(Node* old_tree){

    if (old_tree == nullptr){ return nullptr; }

    Node* cur_node = old_tree;
    Node* new_tree_cur_node = nullptr;

    new_tree_cur_node = new Node(old_tree->node_key, nullptr);
    Node* new_tree_root = new_tree_cur_node;
    new_tree_cur_node->copy_node_data(cur_node);

    try{

        _tree_walk(cur_node, new_tree_cur_node);
    } catch (std::bad_alloc except){

        delete_tree(new_tree_root);
        throw except;
    }
    
    return new_tree_root;
}

Node* Node::split_left() noexcept{

    Node* ret_val = left;

    if (left != nullptr){

        left->prev = nullptr;
    }

    size_of_left_tree = 0;
    left = nullptr;

    return ret_val;
}

Node* Node::split_right() noexcept{

    Node* ret_val = right;

    if (right != nullptr){

        right->prev = nullptr;
    }

    size_of_right_tree = 0;
    right = nullptr;

    return ret_val;
}

void Node::add_left(Node* new_left) noexcept{

    if (new_left != nullptr){

        size_of_left_tree = new_left->size_of_left_tree + new_left->size_of_right_tree + 1;
        left = new_left;
        new_left->prev = this;
    } else{

        left = nullptr;
        size_of_left_tree = 0;
    }
}

void Node::add_right(Node* new_right) noexcept{

    if (new_right != nullptr){

        size_of_right_tree = new_right->size_of_left_tree + new_right->size_of_right_tree + 1;
        right = new_right;
        new_right->prev = this;
    } else{

        right = nullptr;
        size_of_right_tree = 0;
    }
}


void Node::print_node(std::ostream& outp_stream) const{
    
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


Splay_tree::Splay_tree(Splay_tree&& rv_tree) noexcept{

    std::swap(root, rv_tree.root);
}

void Splay_tree::delete_tree() noexcept{

    delete_tree_global(root);
}

Splay_tree& Splay_tree::operator =(const Splay_tree& old_tree){

    if (&old_tree == this){ return *this; }

    Node* tmp = Node::copy_tree(old_tree.root);

    delete_tree();
    root = tmp; 

    return *this;
}

Splay_tree& Splay_tree::operator =(Splay_tree&& rv_tree) noexcept{

    if (&rv_tree == this){ return *this; }

    std::swap(root, rv_tree.root);

    return *this;
}

bool Splay_tree::right_rotation(Node* cur_node) noexcept{

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }

    Node* new_patrents_left = cur_node->split_right();
    Node* grandparent = parent->go_back();
    bool parent_is_left = parent->is_left();
    bool parent_is_right = parent->is_right();

    assert(cur_node->is_left());
    cur_node->is_left();
    parent->split_left();
    parent->add_left(new_patrents_left);

    cur_node->add_right(parent);

    if (parent_is_left){ grandparent->add_left(cur_node); }
    if (parent_is_right){ grandparent->add_right(cur_node); }

    return true;
}

bool Splay_tree::left_rotation(Node* cur_node) noexcept{

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }

    Node* new_patrents_right = cur_node->split_left();
    Node* grandparent = parent->go_back();
    bool parent_is_left = parent->is_left();
    bool parent_is_right = parent->is_right();

    assert(cur_node->is_right());
    cur_node->is_right();
    parent->split_right();
    parent->add_right(new_patrents_right);

    cur_node->add_left(parent);

    if (parent_is_left){ grandparent->add_left(cur_node); }
    if (parent_is_right){ grandparent->add_right(cur_node); }

    return true;
}

bool Splay_tree::right_zig_zig(Node* cur_node) noexcept{

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }
    Node* grandparent = parent->go_back();
    if (grandparent == nullptr){ return false; }

    right_rotation(parent);
    right_rotation(cur_node);
    
    return true;
}

bool Splay_tree::left_zig_zig(Node* cur_node) noexcept{

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }
    Node* grandparent = parent->go_back();
    if (grandparent == nullptr){ return false; }

    left_rotation(parent);
    left_rotation(cur_node);
    
    return true;
}

bool Splay_tree::right_zig_zag(Node* cur_node) noexcept{

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }
    Node* grandparent = parent->go_back();
    if (grandparent == nullptr){ return false; }

    left_rotation(cur_node);
    right_rotation(cur_node);

    return true;
}

bool Splay_tree::left_zig_zag(Node* cur_node) noexcept{

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }
    Node* grandparent = parent->go_back();
    if (grandparent == nullptr){ return false; }

    right_rotation(cur_node);
    left_rotation(cur_node);

    return true;
}

int Splay_tree::choose_rootation(Node* cur_node) const noexcept{

    if (cur_node == nullptr){ return Nothing; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return Nothing; }
    Node* grandparent = parent->go_back();

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

void Splay_tree::pull_node_up(Node* cur_node) noexcept{

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

    //dump_graphviz("../bin/graph.dot");
}

Node* Splay_tree::find_nearest(T_key new_key) noexcept{

    if (root == nullptr){ return nullptr; }

    Node tmp_node(new_key);
    Node* cur_node = root;
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

bool Splay_tree::check_sub_tree(Node* cur_node) const noexcept{

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

bool Splay_tree::check_tree() const noexcept{

    if (root != nullptr){

        return check_sub_tree(root->go_right()) && check_sub_tree(root->go_left());
    }

    return true; 
}

void Splay_tree::add_new_elem(T_key new_elem){

    if (root == nullptr){

        root = new Node(new_elem);
        return;
    }

    Node* new_node = new Node(new_elem);

    Node* nearest_elem = find_nearest(new_elem);
    Node* new_left = nullptr;
    Node* new_right = nullptr;
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

bool Splay_tree::find_elem(T_key elem) noexcept{
    
    Node* nearest = find_nearest(elem);
    Node tmp_node(elem);

    if (nearest != nullptr && *nearest == tmp_node){ 
        
        pull_node_up(nearest);
        return true; 
    }

    return false;
}

int Splay_tree::number_of_elems(int from, int to) noexcept{

    if (from > to){ return -1; }

    int medium_elem = (to + from) / 2;

    Node* nearest_to_medium = find_nearest(medium_elem);
    pull_node_up(nearest_to_medium);

    if (nearest_to_medium == nullptr){ return 0; }

    Node tmp_left(from);
    Node tmp_right(to);
    Node* left_limit = find_nearest(from);
    int num_of_greater_than_left = num_of_greater_elems;
    Node* right_limit = find_nearest(to);
    int num_of_greater_than_right = num_of_greater_elems;

    int ret_val = num_of_greater_than_left - num_of_greater_than_right + 1;

    if (*left_limit < tmp_left){ ret_val--; }
    if (*right_limit > tmp_right){ ret_val--; }

    return ret_val;
}   

void Splay_tree::dump_graphviz(const char* out_name) const{

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