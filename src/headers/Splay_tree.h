#pragma onse

#include <iostream>

typedef int T_key;

enum Rotations{
    
    Nothing = 0,
    Left = 1,
    Right = 2,
    Left_zig_zig = 3,
    Right_zig_zig = 4,
    Left_zig_zag = 5,
    Right_zig_zag = 6
};

class Node final{

private:

    Node* prev;
    Node* left = nullptr;
    Node* right = nullptr;

    T_key node_key;

    int size_of_left_tree = 0;
    int size_of_right_tree = 0;

    static void _tree_walk(Node* cur_node, Node* new_tree_cur_node);

    void copy_node_data(Node* node_to_copy) noexcept;
    static void delete_tree(Node* root) noexcept; //если при освобождении исключение, то все

public:

    Node(T_key new_key, Node* prev_node = nullptr) : prev{prev_node}, node_key{new_key} {};
    Node(const Node&) = delete;
    Node(Node&&) = delete;
    ~Node() {};

    static Node* copy_tree(Node* old_tree);

    Node& operator =(const Node&) = delete;
    Node& operator =(Node&&) = delete;

    bool operator <(const Node& right_node) const noexcept{

        return node_key < right_node.node_key;
    }
    bool operator <=(const Node& right_node) const noexcept{

        return node_key <= right_node.node_key;
    }
    bool operator >(const Node& right_node) const noexcept{

        return node_key > right_node.node_key;
    }
    bool operator >=(const Node& right_node) const noexcept{

        return node_key >= right_node.node_key;
    }
    bool operator ==(const Node& right_node) const noexcept{

        return node_key == right_node.node_key;
    }

    Node* split_left() noexcept;
    Node* split_right() noexcept;
    void add_left(Node* new_left) noexcept;
    void add_right(Node* new_right) noexcept;

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
    Node* go_left() const noexcept{

        return left;
    }
    Node* go_right() const noexcept{

        return right;
    }
    Node* go_back() const noexcept{

        return prev;
    }

    void delete_right() noexcept{

        delete right;
        right = nullptr;
    }

    void delete_left() noexcept{

        delete left;
        left = nullptr;
    }

    void print_node(std::ostream& outp_stream) const;
};


class Splay_tree final{
    
    Node* root = nullptr;
    int num_of_smaller_elems = 0;
    int num_of_greater_elems = 0;

    int choose_rootation(Node* cur_node) const noexcept;

    bool left_rotation(Node* cur_node) noexcept;
    bool right_rotation(Node* cur_node) noexcept;
    bool left_zig_zig(Node* cur_node) noexcept;
    bool right_zig_zig(Node* cur_node) noexcept;
    bool left_zig_zag(Node* cur_node) noexcept;
    bool right_zig_zag(Node* cur_node) noexcept;

    void pull_node_up(Node* cur_node) noexcept;
    Node* find_nearest(T_key new_key) noexcept;

    bool check_sub_tree(Node* cur_node) const noexcept;

    void delete_tree() noexcept;

public:

    Splay_tree(){}
    Splay_tree(const Splay_tree& old_tree) : root{root = Node::copy_tree(old_tree.root)} {}
    Splay_tree(Splay_tree&& rv_tree) noexcept;
    ~Splay_tree(){ delete_tree(); }

    Splay_tree& operator =(const Splay_tree& old_tree);
    Splay_tree& operator =(Splay_tree&& rv_tree) noexcept;

    bool check_tree() const noexcept;

    void add_new_elem(T_key new_elem);
    bool find_elem(T_key elem) noexcept;
    int number_of_elems(int from, int to) noexcept; 
    void dump_graphviz(const char* out_name) const;
};

