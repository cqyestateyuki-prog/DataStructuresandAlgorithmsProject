#define DEBUG
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>
#include "BSTROOT.h"

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
    //tests that const BSTROOT cannot be altered
    BSTROOT<int, char, compare_ints, is_equal> const const_BSTROOT;
    //const_BSTROOT.insert(1, 'A');

    BSTROOT<int, char, compare_ints, is_equal> BST;

    CHECK(BST.is_empty());

    BST.insert(3, 'C');
    CHECK(BST.get_root()->Key == 3);

    BST.insert(5, 'E');
    CHECK(BST.get_root()->Key == 5);
    CHECK(BST.get_root()->left->Value == 'C');

    BST.insert(2, 'B');
    CHECK(BST.get_root()->Key == 2);
    CHECK(BST.get_root()->right->Key == 5);

    BST.insert(8, 'H');
    CHECK(BST.get_root()->Key == 8);

    BST.insert(9, 'I');
    CHECK(BST.get_root()->Key == 9);

    BST.insert(1, 'A');
    CHECK(BST.get_root()->Key == 1);

    BST.insert(1, 'a');
    CHECK(BST.get_root()->Value == 'a');
    CHECK(BST.get_root()->right->Key == 9);
    CHECK(BST.get_root()->right->left->Key == 8);
    CHECK(BST.get_root()->right->left->left->Key == 2);
    CHECK(BST.get_root()->right->left->left->right->Key == 5);
    CHECK(BST.get_root()->right->left->left->right->left->Key == 3);

    CHECK(BST.size() == 6);
    CHECK(BST.height() == 6);
}

TEST_CASE("TEST REMOVE()")
{
    BSTROOT<int, char, compare_ints, is_equal> BST;

    CHECK_THROWS(BST.remove(1));

    BST.insert(2, 'B');
    BST.insert(5, 'E');
    BST.insert(8, 'H');
    BST.insert(9, 'I');
    BST.insert(1, 'A');

    BST.remove(2);
    CHECK(!BST.contains(2));
    CHECK(BST.size() == 4);

    BST.remove(1);
    CHECK(!BST.contains(1));
    CHECK(BST.size() == 3);

    BST.remove(8);
    CHECK(!BST.contains(8));
    CHECK(BST.size() == 2);

    BST.remove(5);
    CHECK(!BST.contains(5));
    CHECK(BST.size() == 1);

    BST.remove(9);
    CHECK(!BST.contains(9));
    CHECK(BST.size() == 0);
}

TEST_CASE("TEST LOOKUP()")
{
    BSTROOT<int, char, compare_ints, is_equal> BST;

    CHECK_THROWS(BST.lookup(1));

    BST.insert(2, 'B');
    CHECK(BST.lookup(2) == 'B');

    BST.insert(5, 'E');
    CHECK(BST.lookup(5) == 'E');

    BST.insert(8, 'H');
    CHECK(BST.lookup(8) == 'H');

    BST.insert(9, 'I');
    CHECK(BST.lookup(9) == 'I');

    BST.insert(1, 'A');
    CHECK(BST.lookup(1) == 'A');

    BST.insert(5, 'X');
    CHECK(BST.lookup(5) == 'X');
}

TEST_CASE("TEST CONTAINS()")
{
    BSTROOT<int, char, compare_ints, is_equal> BST;

    CHECK(!BST.contains(1));

    BST.insert(2, 'B');
    CHECK(BST.contains(2));

    BST.insert(5, 'E');
    CHECK(BST.contains(5));

    BST.insert(8, 'H');
    CHECK(BST.contains(8));

    BST.insert(9, 'I');
    CHECK(BST.contains(9));

    BST.insert(1, 'A');
    CHECK(BST.contains(1));

    CHECK(!BST.contains(7));
}

TEST_CASE("TEST SIZE()")
{
    BSTROOT<int, char, compare_ints, is_equal> BST;

    CHECK(BST.size() == 0);

    BST.insert(2, 'B');
    CHECK(BST.size() == 1);

    BST.insert(5, 'E');
    CHECK(BST.size() == 2);

    BST.insert(8, 'H');
    CHECK(BST.size() == 3);

    BST.insert(9, 'I');
    CHECK(BST.size() == 4);

    BST.insert(1, 'A');
    CHECK(BST.size() == 5);
}

TEST_CASE("TEST CLEAR()")
{
    BSTROOT<int, char, compare_ints, is_equal> BST;

    BST.clear();

    BST.insert(2, 'B');
    BST.insert(5, 'E');
    BST.insert(8, 'H');
    BST.insert(9, 'I');
    BST.insert(1, 'A');

    BST.clear();

    CHECK(BST.size() == 0);
    CHECK(BST.is_empty());
}

TEST_CASE("TEST HEIGHT()")
{
    BSTROOT<int, char, compare_ints, is_equal> BST;

    CHECK(BST.height() == 0);

    BST.insert(3, 'C');
    CHECK(BST.height() == 1);

    BST.insert(5, 'E');
    CHECK(BST.height() == 2);

    BST.insert(2, 'B');
    CHECK(BST.height() == 3);

    BST.insert(8, 'H');
    CHECK(BST.height() == 4);

    BST.insert(9, 'I');
    CHECK(BST.height() == 5);

    BST.insert(1, 'A');
    CHECK(BST.height() == 6);
}

TEST_CASE("TEST BALANCE()")
{
    BSTROOT<int, char, compare_ints, is_equal> BST;

    CHECK(BST.balance() == 0);

    BST.insert(3, 'C');
    CHECK(BST.balance() == 0);

    BST.insert(5, 'E');
    CHECK(BST.balance() == 1);

    BST.insert(2, 'B');
    CHECK(BST.balance() == -2);

    BST.insert(8, 'H');
    CHECK(BST.balance() == 3);

    BST.insert(9, 'I');
    CHECK(BST.balance() == 4);

    BST.insert(1, 'A');
    CHECK(BST.balance() == -5);
}

TEST_CASE("TEST COPY & MOVE")
{
    BSTROOT<int, char, compare_ints, is_equal> BST1;
    BST1.insert(2, 'B');
    BST1.insert(5, 'E');
    BST1.insert(8, 'H');
    BST1.insert(9, 'I');
    BST1.insert(1, 'A');

    //copy constructor
    BSTROOT<int, char, compare_ints, is_equal> BST2 = BST1;
    CHECK(BST1.size() == 5);
    CHECK(BST2.size() == 5);

    //copy assignment operator
    BSTROOT<int, char, compare_ints, is_equal> BST3;
    BST3 = BST1;
    CHECK(BST1.size() == 5);
    CHECK(BST3.size() == 5);

    //move constructor
    BSTROOT<int, char, compare_ints, is_equal> BST4;
    BST4 = std::move(BST1);
    CHECK(BST1.size() == 0);
    CHECK(BST4.size() == 5);

    //move assignment operator
    BSTROOT<int, char, compare_ints, is_equal> BST5 = std::move(BST2);
    CHECK(BST2.size() == 0);
    CHECK(BST5.size() == 5);
}
