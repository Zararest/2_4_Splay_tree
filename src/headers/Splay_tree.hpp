#pragma onse

//#include <compare>
#include <iostream>

enum Rotations{
    
    Nothing = 0,
    Left = 1,
    Right = 2,
    Left_zig_zig = 3,
    Right_zig_zig = 4,
    Left_zig_zag = 5,
    Right_zig_zag = 6
};

template <typename T_key>
class Node final{

private:

    Node<T_key>* prev;
    Node<T_key>* left = nullptr;
    Node<T_key>* right = nullptr;

    T_key node_key;

    int size_of_left_tree = 0;
    int size_of_right_tree = 0;

    static void tree_walk(Node<T_key>* cur_node, Node<T_key>* new_tree_cur_node);

    void copy_node_data(Node<T_key>* node_to_copy) noexcept(std::is_nothrow_copy_constructible<T_key>::value);
    static void delete_tree(Node<T_key>* root) noexcept;

public:

    Node<T_key>(T_key new_key, Node<T_key>* prev_node = nullptr) : prev{prev_node}, node_key{new_key} {};
    Node<T_key>(const Node<T_key>&) = delete;
    Node<T_key>(Node<T_key>&&) = delete;
    ~Node<T_key>() {};

    static Node<T_key>* copy_tree(Node<T_key>* old_tree, Node<T_key>*& mount_node);

    Node<T_key>& operator =(const Node<T_key>&) = delete;
    Node<T_key>& operator =(Node<T_key>&&) = delete;

    /*auto operator <=>(const Node<T_key>& right_node){

        return node_key <=> right_node.node_key;
    }*/

    bool operator <(const Node<T_key>& right_node) const{

        return node_key < right_node.node_key;
    }
    bool operator <=(const Node<T_key>& right_node) const{

        return node_key <= right_node.node_key;
    }
    bool operator >(const Node<T_key>& right_node) const{

        return node_key > right_node.node_key;
    }
    bool operator >=(const Node<T_key>& right_node) const{

        return node_key >= right_node.node_key;
    }
    bool operator ==(const Node<T_key>& right_node) const{

        return node_key == right_node.node_key;
    }

    Node<T_key>* split_left() noexcept;
    Node<T_key>* split_right() noexcept;
    void add_left(Node<T_key>* new_left) noexcept;
    void add_right(Node<T_key>* new_right) noexcept;

    bool is_right() const noexcept{

        if (prev == nullptr){ return false; }
        if (prev->right == this) { return true; }
        return false;
    }
    bool is_left() const noexcept{

        if (prev == nullptr){ return false; }
        if (prev->left == this) { return true; }
        return false;
    }
    bool is_leaf() const noexcept{

        if (left == nullptr && right == nullptr){ return true; }
        return false;
    }

    int get_left_tree_size() const noexcept{

        return size_of_left_tree;
    }
    int get_right_tree_size() const noexcept{

        return size_of_right_tree;
    }
    T_key get_key() const noexcept{

        return node_key;
    }
    Node<T_key>* go_left() const noexcept{

        return left;
    }
    Node<T_key>* go_right() const noexcept{

        return right;
    }
    Node<T_key>* go_back() const noexcept{

        return prev;
    }

    void print_node(std::ostream& outp_stream) const;
};

template <typename T_key>
class Splay_tree final{
    
    Node<T_key>* root = nullptr;
    int num_of_smaller_elems = 0;
    int num_of_greater_elems = 0;

    int choose_rootation(Node<T_key>* cur_node) const noexcept;

    void left_rotation(Node<T_key>* cur_node) noexcept;
    void right_rotation(Node<T_key>* cur_node) noexcept;
    void left_zig_zig(Node<T_key>* cur_node) noexcept;
    void right_zig_zig(Node<T_key>* cur_node) noexcept;
    void left_zig_zag(Node<T_key>* cur_node) noexcept;
    void right_zig_zag(Node<T_key>* cur_node) noexcept;

    void pull_node_up(Node<T_key>* cur_node) noexcept;
    Node<T_key>* find_nearest(T_key new_key);
    Node<T_key>* get_median(Node<T_key>& cur_left, T_key median);

    bool check_sub_tree(Node<T_key>* cur_node) const;

    void delete_tree() noexcept;

public:

    Splay_tree() = default;
    Splay_tree(const Splay_tree<T_key>& old_tree);
    Splay_tree(Splay_tree<T_key>&& rv_tree) noexcept;
    ~Splay_tree(){ delete_tree(); }

    Splay_tree<T_key>& operator =(const Splay_tree<T_key>& old_tree);
    Splay_tree<T_key>& operator =(Splay_tree<T_key>&& rv_tree) noexcept;

    bool check_tree() const;

    void add_new_elem(T_key new_elem);
    bool find_elem(T_key elem);
    int number_of_elems(T_key from, T_key to); 
    void dump_graphviz(const char* out_name) const;
};

#include "./Splay_tree-impl.hpp"
