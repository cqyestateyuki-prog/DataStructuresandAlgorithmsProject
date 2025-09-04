#ifndef BSTRAND_H_INCLUDED
#define BSTRAND_H_INCLUDED
#include <ctime>

namespace cop3530
{
    template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
    class BSTRAND;
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
class cop3530::BSTRAND
{
    struct node
    {
        key Key;
        value Value;
        struct node* left;
        struct node* right;
        node(key Key, value Value):
            Key(Key),
            Value(Value),
            left(nullptr),
            right(nullptr) {}

        ~node() {};
    };

public:
    BSTRAND();
    ~BSTRAND();

    //copy constructor
    BSTRAND(const BSTRAND& x)
    {
        _root = nullptr;
        copyTree(_root, x._root);
    }

    //copy assignment operator
    BSTRAND& operator= (const BSTRAND& x)
    {
        if (this != &x)
        {
            clear();
            copyTree(_root, x._root);
        }

        return *this;
    }

    //move constructor
    BSTRAND(BSTRAND&& x) noexcept
    {
        //have this root point to x's root
        _root = x._root;

        //free x's root
        x._root = nullptr;
    }

    //move assignment operator
    BSTRAND& operator= (BSTRAND&& x) noexcept
    {
        if (this != &x)
        {
            //free existing BSTRAND
            clear();

            //have this root point to x's root
            _root = x._root;

            //free x's root
            x._root = nullptr;
        }

        return *this;
    }

    void copyTree(node* &_root, const node* x_root)
    {
        if (!x_root)
            return;

        _root = new node(x_root->Key, x_root->Value);

        copyTree(_root->left, x_root->left);
        copyTree(_root->right, x_root->right);
    };

    void rotate_clockwise(node* &root);
    void rotate_counter_clockwise(node* &root);

    void insert(key Key, value Value);
    void remove(key Key);
    value& lookup(key Key) const;

    bool contains(key Key) const;
    bool is_empty() const;
    bool is_full() const;
    size_t size() const;
    void clear();
    size_t height() const;
    size_t balance() const;

#ifdef DEBUG
    node* get_root() const
    {
        return _root;
    }
#endif

private:
    void do_insert(node* &root, key Key, value Value); //recursive helper function for insert()
    void insert_at_root(node* &root, key Key, value Value); //recursive helper function for do_insert()
    void insert_at_leaf(node* &root, key Key, value Value); //recursive helper function for do_insert()
    void do_remove(node* &root, key Key); //recursive helper function for remove()
    size_t get_size(node* root) const; // recursive helper function for size()
    void do_clear(node* &root); //recursive helper function for clear()
    node* join(node* &a, node* &b); //used in remove() to join children trees of the node removed
    size_t get_height(node* root) const; //recursive helper function for height()
    bool (*compare)(const key&, const key&);
    bool (*is_equal)(const key&, const key&);
    node* _root = nullptr;
};

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
cop3530::BSTRAND<key, value, compare_function, equals_function>::BSTRAND():
    compare(compare_function),
    is_equal(equals_function)
{};

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
cop3530::BSTRAND<key, value, compare_function, equals_function>::~BSTRAND()
{
    clear();
};

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
void cop3530::BSTRAND<key, value, compare_function, equals_function>::rotate_clockwise(node* &root)
{
    node* root_left = root->left;
    root->left = root->left->right;
    root_left->right = root;
    root = root_left;
};

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
void cop3530::BSTRAND<key, value, compare_function, equals_function>::rotate_counter_clockwise(node* &root)
{
    node* root_right = root->right;
    root->right = root->right->left;
    root_right->left = root;
    root = root_right;
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
void cop3530::BSTRAND<key, value, compare_function, equals_function>::insert(key Key, value Value)
{
    do_insert(_root, Key, Value);
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
void cop3530::BSTRAND<key, value, compare_function, equals_function>::do_insert(node* &root, key Key, value Value)
{
    srand(time(nullptr));
    int M = size();
    int r = rand() % (M+1);

    if (r == 0)
        insert_at_root(root, Key, Value);
    else
        insert_at_leaf(root, Key, Value);
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
void cop3530::BSTRAND<key, value, compare_function, equals_function>::insert_at_root(node* &root, key Key, value Value)
{
    if (!root)
        root = new node(Key, Value);

    if (is_equal(Key, root->Key))
        root->Value = Value;

    else if (compare(Key, root->Key)) //if key < root->key
    {
        insert_at_root(root->left, Key, Value);
        rotate_clockwise(root);
    }

    else //if key > root->key
    {
        insert_at_root(root->right, Key, Value);
        rotate_counter_clockwise(root);
    }
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
void cop3530::BSTRAND<key, value, compare_function, equals_function>::insert_at_leaf(node* &root, key Key, value Value)
{
    if (!root)
        root = new node(Key, Value);

    if (is_equal(Key, root->Key))
        root->Value = Value;
    else if (compare(Key, root->Key)) //if Key < root->Key
        insert_at_leaf(root->left, Key, Value);

    else //if Key > root->Key
        insert_at_leaf(root->right, Key, Value);
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
void cop3530::BSTRAND<key, value, compare_function, equals_function>::remove(key Key)
{
    if (is_empty())
        throw std::runtime_error("void remove(key Key) const: Tree is empty");

    do_remove(_root, Key);
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
void cop3530::BSTRAND<key, value, compare_function, equals_function>::do_remove(node* &root, key Key)
{
    if (!root)
        return;

    if (compare(Key, root->Key))
        do_remove(root->left, Key);
    if (!compare(Key, root->Key))
        do_remove(root->right, Key);
    if (is_equal(Key, root->Key))
    {
        node* temp = root;
        root = join(root->left, root->right);
        delete temp;
    }
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
typename cop3530::BSTRAND<key, value, compare_function, equals_function>::node* cop3530::BSTRAND<key, value, compare_function, equals_function>::join(node* &a, node* &b)
{
    if (!a)
        return b;
    if (!b)
        return a;

    do_insert(b, a->Key, a->Value);
    b->left = join(a->left, b->left);
    b->right = join(a->right, b->right);

    delete a;
    return b;
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
value& cop3530::BSTRAND<key, value, compare_function, equals_function>::lookup(key Key) const
{
    if (is_empty())
        throw std::runtime_error("value& lookup(key Key) const: Tree is empty");

    node* curr = _root;
    while (true)
    {
        if (is_equal(curr->Key, Key))
            return curr->Value;
        else if (compare_function(Key, curr->Key)) //if the Key searched for is < the current node's Key, move left
        {
            if (!curr->left)
                throw std::runtime_error("value& lookup(key Key) const: No value corresponding to the given key");
            curr = curr->left;
        }
        else //if the Key searched for is > the current node's Key, move right
        {
            if (!curr->right)
                throw std::runtime_error("value& lookup(key Key) const: No value corresponding to the given key");
            curr = curr->right;
        }
    }
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
bool cop3530::BSTRAND<key, value, compare_function, equals_function>::contains(key Key) const
{
    if (is_empty())
        return false;

    node* curr = _root;
    while (true)
    {
        if (equals_function(curr->Key, Key))
            return true;
        else if (compare_function(curr->Key, Key))
        {
            if (!curr->right)
                return false;
            curr = curr->right;
        }
        else if (!compare_function(curr->Key, Key))
        {
            if (!curr->left)
                return false;

            curr = curr->left;
        }
    }

    return false;
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
size_t cop3530::BSTRAND<key, value, compare_function, equals_function>::size() const
{
    return get_size(_root);
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
size_t cop3530::BSTRAND<key, value, compare_function, equals_function>::get_size(node* root) const
{
    if (!root)
        return 0;
    size_t s = 1;
    s += get_size(root->left);
    s += get_size(root->right);

    return s;
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
bool cop3530::BSTRAND<key, value, compare_function, equals_function>::is_empty() const
{
    return (!_root);
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
bool cop3530::BSTRAND<key, value, compare_function, equals_function>::is_full() const
{
    return false;
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
void cop3530::BSTRAND<key, value, compare_function, equals_function>::clear()
{
    if (!is_empty())
        do_clear(_root);
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
void cop3530::BSTRAND<key, value, compare_function, equals_function>::do_clear(node* &root)
{
    if (root->left)
        do_clear(root->left);
    if (root->right)
        do_clear(root->right);

    delete root;
    root = nullptr;
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
size_t cop3530::BSTRAND<key, value, compare_function, equals_function>::height() const
{
    return get_height(_root);
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
size_t cop3530::BSTRAND<key, value, compare_function, equals_function>::get_height(node* root) const
{
    if (!root)
        return 0;

    size_t height_left = 1 + get_height(root->left);
    size_t height_right = 1 + get_height(root->right);

    return std::max(height_left, height_right);
}

template <typename key, typename value, bool(*compare_function)(const key&, const key&), bool(*equals_function)(const key&, const key&)>
size_t cop3530::BSTRAND<key, value, compare_function, equals_function>::balance() const
{
    if (is_empty())
        return 0;

    return get_height(_root->left) - get_height(_root->right);
}

#endif // BSTRAND_H_INCLUDED
