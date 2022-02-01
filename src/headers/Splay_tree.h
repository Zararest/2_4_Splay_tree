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

class Node final{//надо хранить размер леврогол и правого поддеревьев 
                 //когда происходит запрос вытягиваем середину отрезка и производим поиск концов проходя по самому правому и самому левому дереву 
private:

    Node* prev;
    Node* left = nullptr;
    Node* right = nullptr;

    T_key node_key;

    int size_of_left_tree = 0;
    int size_of_right_tree = 0;

    void copy_node_data(Node* node_to_copy);

public:

    Node(T_key new_key, Node* prev_node = nullptr);
    Node(const Node&) = delete;
    Node(Node&&) = delete;
    ~Node();

    static Node* copy_tree(Node* old_tree);

    Node& operator =(const Node&) = delete;
    Node& operator =(Node&&) = delete;

    bool operator <(const Node& right_node) const{

        return node_key < right_node.node_key;
    }
    bool operator >(const Node& right_node) const{

        return node_key > right_node.node_key;
    }
    bool operator ==(const Node& right_node) const{

        return node_key == right_node.node_key;
    }

    Node* split_left();
    Node* split_right();
    void add_left(Node* new_left);
    void add_right(Node* new_right);

    bool is_right(){

        if (prev == nullptr){ return false; }
        if (prev->right == this) { return true; }
        return false;
    }
    bool is_left(){

        if (prev == nullptr){ return false; }
        if (prev->left == this) { return true; }
        return false;
    }
    bool is_leaf(){

        if (left == nullptr && right == nullptr){ return true; }
        return false;
    }

    int get_left_tree_size() const{

        return size_of_left_tree;
    }
    int get_right_tree_size() const{

        return size_of_right_tree;
    }
    T_key get_key() const{

        return node_key;
    }
    Node* go_left() const{

        return left;
    }
    Node* go_right() const{

        return right;
    }
    Node* go_back() const{

        return prev;
    }
    void print_node(std::ostream& outp_stream) const;
};


class Splay_tree final{
    
    Node* root = nullptr;

    int choose_rootation(Node* cur_node);

    bool left_rotation(Node* cur_node);
    bool right_rotation(Node* cur_node);
    bool left_zig_zig(Node* cur_node);
    bool right_zig_zig(Node* cur_node);
    bool left_zig_zag(Node* cur_node);
    bool right_zig_zag(Node* cur_node);

    Node* find_first_less(T_key new_key);
    Node* find_first_greater(T_key new_key);
    Node* find_nearest(T_key new_key);

    bool check_sub_tree(Node* cur_node);

public:

    Splay_tree() = default;
    Splay_tree(const Splay_tree& old_tree);
    Splay_tree(Splay_tree&& rv_tree);
    ~Splay_tree();

    Splay_tree& operator =(const Splay_tree& old_tree);
    Splay_tree& operator =(Splay_tree&& rv_tree);

    bool check_tree();

    void add_new_elem(T_key new_elem);
    bool find_elem(T_key elem);
    int number_of_elems(int from, int to); 
};

