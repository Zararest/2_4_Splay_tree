#include "headers/Splay_tree.h"

#include <cassert>

Node::Node(T_key new_key, Node* prev_node){

    prev = prev_node;
    node_key = new_key;
}

void Node::copy_node_data(Node* node_to_copy){

    if (node_to_copy == nullptr){ return; }

    node_key = node_to_copy->node_key;
    size_of_left_tree = node_to_copy->size_of_left_tree;
    size_of_right_tree = node_to_copy->size_of_right_tree;
}

Node* Node::copy_tree(Node* old_tree){

    if (old_tree == nullptr){ return nullptr; }

    Node* cur_node = old_tree;
    Node* new_tree_cur_node = new Node(old_tree->node_key, nullptr);
    new_tree_cur_node->copy_node_data(cur_node);

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

                new_tree_cur_node = new_tree_cur_node->left;
                cur_node = cur_node->left;
            } else{

                assert(new_tree_cur_node->prev != nullptr);
                new_tree_cur_node = new_tree_cur_node->prev;
                cur_node = cur_node->prev;
            }
        }
    }
}

Node::~Node(){

    Node* cur_node = this;

    if (cur_node != nullptr){

        while ((left != nullptr) || (right != nullptr) || (prev != nullptr)){

            if (left != nullptr){

                cur_node = left;
            } else{

                if (right != nullptr){

                    cur_node = right;
                } else{

                    if (cur_node->prev->right == cur_node){

                        cur_node = prev;
                        delete cur_node->right;
                    } else{
                        
                        cur_node = prev;
                        delete cur_node->left;
                    }
                }
            }
        }
    }
}

Node* Node::split_left(){

    Node* ret_val = left;

    if (left != nullptr){

        left->prev = nullptr;
    }

    size_of_left_tree = 0;
    left = nullptr;

    return ret_val;
}

Node* Node::split_right(){

    Node* ret_val = right;

    if (right != nullptr){

        right->prev = nullptr;
    }

    size_of_right_tree = 0;
    right = nullptr;

    return ret_val;
}

void Node::add_left(Node* new_left){

    if (new_left != nullptr){

        size_of_left_tree = left->size_of_left_tree + left->size_of_right_tree + 1;
        left = new_left;
        new_left->prev = this;
    } else{

        left = nullptr;
        size_of_left_tree = 0;
    }
}

void Node::add_right(Node* new_right){

    if (new_right != nullptr){

        size_of_right_tree = right->size_of_left_tree + right->size_of_right_tree + 1;
        right = new_right;
        new_right->prev = this;
    } else{

        right = nullptr;
        size_of_right_tree = 0;
    }
}


void Node::print_node(std::ostream& outp_stream) const{
    
    outp_stream << '"' << this << '"' << " [label = \"" << "key " << node_key << "\" fillcolor=green]" << std::endl;

    if (left != nullptr){

        outp_stream << '"' << this << '"' << " -> " << '"' << left << '"' << std::endl;
        left->print_node(outp_stream);
    }

    if (right != nullptr){

        outp_stream << '"' << this << '"' << " -> " << '"' << right << '"' << std::endl;
        right->print_node(outp_stream);
    }
}


Splay_tree::Splay_tree(const Splay_tree& old_tree){

    root = Node::copy_tree(old_tree.root);
}

Splay_tree::Splay_tree(Splay_tree&& rv_tree){

    std::swap(root, rv_tree.root);
}

Splay_tree::~Splay_tree(){

    delete root;
}

Splay_tree& Splay_tree::operator =(const Splay_tree& old_tree){

    if (&old_tree == this){ return *this; }

    delete root;
    root = Node::copy_tree(old_tree.root);

    return *this;
}

Splay_tree& Splay_tree::operator =(Splay_tree&& rv_tree){

    if (&rv_tree == this){ return *this; }

    std::swap(root, rv_tree.root);

    return *this;
}

bool Splay_tree::left_rotation(Node* cur_node){

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }

    Node* new_patrents_left = cur_node->split_right();
    Node* grandparent = parent->go_back();

    parent->split_left();
    parent->add_left(new_patrents_left);

    cur_node->add_right(parent);

    if (parent->is_left()){ grandparent->add_left(cur_node); }
    if (parent->is_right()){ grandparent->add_right(cur_node); }

    return true;
}

bool Splay_tree::right_rotation(Node* cur_node){

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }

    Node* new_patrents_right = cur_node->split_left();
    Node* grandparent = parent->go_back();

    parent->split_right();
    parent->add_right(new_patrents_right);

    cur_node->add_left(parent);

    if (parent->is_left()){ grandparent->add_left(cur_node); }
    if (parent->is_right()){ grandparent->add_right(cur_node); }

    return true;
}

bool Splay_tree::right_zig_zig(Node* cur_node){

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }
    Node* grandparent = parent->go_back();
    if (grandparent == nullptr){ return false; }

    right_rotation(parent);
    right_rotation(cur_node);
    
    return true;
}

bool Splay_tree::left_zig_zig(Node* cur_node){

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }
    Node* grandparent = parent->go_back();
    if (grandparent == nullptr){ return false; }

    left_rotation(parent);
    left_rotation(cur_node);
    
    return true;
}

bool Splay_tree::right_zig_zag(Node* cur_node){

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }
    Node* grandparent = parent->go_back();
    if (grandparent == nullptr){ return false; }

    left_rotation(cur_node);
    right_rotation(cur_node);

    return true;
}

bool Splay_tree::left_zig_zag(Node* cur_node){

    if (cur_node == nullptr){ return false; }
    Node* parent = cur_node->go_back();
    if (parent == nullptr){ return false; }
    Node* grandparent = parent->go_back();
    if (grandparent == nullptr){ return false; }

    right_rotation(cur_node);
    left_rotation(cur_node);

    return true;
}

int Splay_tree::choose_rootation(Node* cur_node){

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

Node* Splay_tree::find_nearest(T_key new_key){

    if (root == nullptr){ return nullptr; }

    Node tmp_node(new_key);
    Node* cur_node = root;
    bool not_found = true;

    while (not_found){

        not_found = false;

        if (cur_node->go_left() != nullptr && *cur_node->go_left() > tmp_node){

            cur_node = cur_node->go_left();
            not_found = true;
        }

        if (!not_found && cur_node->go_right() != nullptr && *cur_node->go_right() < tmp_node){

            cur_node = cur_node->go_right();
            not_found = true;
        }
    }

    return cur_node;
}

bool Splay_tree::check_sub_tree(Node* cur_node){

    if (cur_node == nullptr){ return true; }

    if (!cur_node->is_right() && !cur_node->is_left()){ return false; }

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

bool Splay_tree::check_tree(){

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

bool Splay_tree::find_elem(T_key elem){
    
    Node* nearest = find_nearest(elem);
    Node tmp_node(elem);

    if (nearest != nullptr && *nearest == tmp_node){ return true; }

    return false;
}