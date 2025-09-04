#define DEBUG
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>
#include "AVL.h"

//the insert algorithm was done manually on paper to verify the program's correctness

using namespace cop3530;

bool compare_ints(const int& a, const int& b)
{
    return a < b;
}

bool is_equal(const int& a, const int& b)
{
    return a == b;
}

TEST_CASE("TEST INSERT()")
{
    //tests that const AVL cannot be altered
    AVL<int, char, compare_ints, is_equal> const const_AVL;
    //const_AVL.insert(1, 'A');

    AVL<int, char, compare_ints, is_equal> AVL;

    CHECK(AVL.is_empty());

    AVL.insert(2, 'B');
    CHECK(AVL.get_root()->Key == 2);
    CHECK(AVL.balance() == 0);

    AVL.insert(5, 'E');
    CHECK(AVL.get_root()->Key == 2);
    CHECK(AVL.get_root()->right->Key == 5);
    CHECK(AVL.balance() == -1);

    AVL.insert(8, 'H');
    CHECK(AVL.get_root()->Key == 5);
    CHECK(AVL.get_root()->left->Key == 2);
    CHECK(AVL.get_root()->right->Key == 8);
    CHECK(AVL.balance() == 0);

    AVL.insert(9, 'I');
    AVL.insert(1, 'A');
    AVL.insert(2, 'b');
    CHECK(AVL.get_root()->Key == 5);
    CHECK(AVL.get_root()->left->Key == 2);
    CHECK(AVL.get_root()->right->Key == 8);
    CHECK(AVL.get_root()->left->left->Key == 1);
    CHECK(AVL.get_root()->right->right->Key == 9);

    CHECK(AVL.size() == 5);
    CHECK(AVL.balance() == 0);
    CHECK(AVL.height() == 3);
    CHECK(!AVL.is_empty());
}

TEST_CASE("TEST REMOVE()")
{
    AVL<int, char, compare_ints, is_equal> AVL;

    AVL.insert(2, 'B');
    AVL.insert(5, 'E');
    AVL.insert(8, 'H');
    AVL.insert(9, 'I');
    AVL.insert(1, 'A');

    AVL.remove(2);
    CHECK(!AVL.contains(2));
    CHECK(AVL.size() == 4);

    AVL.remove(1);
    CHECK(!AVL.contains(1));
    CHECK(AVL.size() == 3);

    AVL.remove(8);
    CHECK(!AVL.contains(8));
    CHECK(AVL.size() == 2);

    AVL.remove(5);
    CHECK(!AVL.contains(5));
    CHECK(AVL.size() == 1);

    AVL.remove(9);
    CHECK(!AVL.contains(9));
    CHECK(AVL.size() == 0);
}

TEST_CASE("TEST LOOKUP()")
{
    AVL<int, char, compare_ints, is_equal> AVL;

    CHECK_THROWS(AVL.lookup(1));

    AVL.insert(2, 'B');
    CHECK(AVL.lookup(2) == 'B');

    AVL.insert(5, 'E');
    CHECK(AVL.lookup(5) == 'E');

    AVL.insert(8, 'H');
    CHECK(AVL.lookup(8) == 'H');

    AVL.insert(9, 'I');
    CHECK(AVL.lookup(9) == 'I');

    AVL.insert(1, 'A');
    CHECK(AVL.lookup(1) == 'A');
}

TEST_CASE("TEST CONTAINS()")
{
    AVL<int, char, compare_ints, is_equal> AVL;

    CHECK(!AVL.contains(1));

    AVL.insert(2, 'B');
    CHECK(AVL.contains(2));

    AVL.insert(5, 'E');
    CHECK(AVL.contains(5));

    AVL.insert(8, 'H');
    CHECK(AVL.contains(8));

    AVL.insert(9, 'I');
    CHECK(AVL.contains(9));

    AVL.insert(1, 'A');
    CHECK(AVL.contains(1));

    CHECK(!AVL.contains(7));
}

TEST_CASE("TEST SIZE()")
{
    AVL<int, char, compare_ints, is_equal> AVL;

    CHECK(AVL.size() == 0);

    AVL.insert(2, 'B');
    CHECK(AVL.size() == 1);

    AVL.insert(5, 'E');
    CHECK(AVL.size() == 2);

    AVL.insert(8, 'H');
    CHECK(AVL.size() == 3);

    AVL.insert(9, 'I');
    CHECK(AVL.size() == 4);

    AVL.insert(1, 'A');
    CHECK(AVL.size() == 5);
}

TEST_CASE("TEST CLEAR()")
{
    AVL<int, char, compare_ints, is_equal> AVL;

    AVL.clear();

    AVL.insert(2, 'B');
    AVL.insert(5, 'E');
    AVL.insert(8, 'H');
    AVL.insert(9, 'I');
    AVL.insert(1, 'A');

    AVL.clear();

    CHECK(AVL.size() == 0);
    CHECK(AVL.is_empty());
}

TEST_CASE("TEST HEIGHT()")
{
    AVL<int, char, compare_ints, is_equal> AVL;

    CHECK(AVL.height() == 0);

    AVL.insert(2, 'B');
    CHECK(AVL.height() == 1);

    AVL.insert(5, 'E');
    CHECK(AVL.height() == 2);

    AVL.insert(8, 'H');
    CHECK(AVL.height() == 2);

    AVL.insert(9, 'I');
    CHECK(AVL.height() == 3);

    AVL.insert(1, 'A');
    CHECK(AVL.height() == 3);
}

TEST_CASE("TEST BALANCE()")
{
    AVL<int, char, compare_ints, is_equal> AVL;

    CHECK(AVL.balance() == 0);

    AVL.insert(2, 'B');
    CHECK(AVL.balance() == 0);

    AVL.insert(5, 'E');
    CHECK(AVL.balance() == -1);

    AVL.insert(8, 'H');
    CHECK(AVL.balance() == 0);

    AVL.insert(9, 'I');
    CHECK(AVL.balance() == -1);

    AVL.insert(1, 'A');
    CHECK(AVL.balance() == 0);
}

TEST_CASE("TEST COPY & MOVE")
{
    AVL<int, char, compare_ints, is_equal> AVL1;
    AVL1.insert(2, 'B');
    AVL1.insert(5, 'E');
    AVL1.insert(8, 'H');
    AVL1.insert(9, 'I');
    AVL1.insert(1, 'A');

    //copy constructor
    AVL<int, char, compare_ints, is_equal> AVL2 = AVL1;
    CHECK(AVL1.get_root()->Key == 5);
    CHECK(AVL1.get_root()->left->Key == 2);
    CHECK(AVL1.get_root()->right->Key == 8);
    CHECK(AVL1.get_root()->left->left->Key == 1);
    CHECK(AVL1.get_root()->right->right->Key == 9);
    CHECK(AVL2.get_root()->Key == 5);
    CHECK(AVL2.get_root()->left->Key == 2);
    CHECK(AVL2.get_root()->right->Key == 8);
    CHECK(AVL2.get_root()->left->left->Key == 1);
    CHECK(AVL2.get_root()->right->right->Key == 9);
    CHECK(AVL1.size() == 5);
    CHECK(AVL2.size() == 5);

    //copy assignment operator
    AVL<int, char, compare_ints, is_equal> AVL3;
    AVL3.insert(2, 'B');
    AVL3.insert(5, 'E');
    AVL3 = AVL1;
    CHECK(AVL1.size() == 5);
    CHECK(AVL3.size() == 5);

    //move constructor
    AVL<int, char, compare_ints, is_equal> AVL4 = std::move(AVL1);
    CHECK(AVL1.size() == 0);
    CHECK(AVL4.size() == 5);

    //move assignment operator
    AVL<int, char, compare_ints, is_equal> AVL5;
    AVL5.insert(2, 'B');
    AVL5.insert(5, 'E');
    AVL5 = std::move(AVL2);
    CHECK(AVL2.size() == 0);
    CHECK(AVL5.size() == 5);
}
