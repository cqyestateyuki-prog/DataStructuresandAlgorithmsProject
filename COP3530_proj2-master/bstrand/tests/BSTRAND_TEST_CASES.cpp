#define DEBUG
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>
#include "BSTRAND.h"

//since the insert method is based off of a randomly generated integer, the location of inserted nodes is unknown, so location is not checked

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
    //tests that const BSTRAND cannot be altered
    BSTRAND<int, char, compare_ints, is_equal> const const_BSTRAND;
    //const_BSTRAND.insert(1, 'A');

    BSTRAND<int, char, compare_ints, is_equal> BST;

    CHECK(BST.is_empty());

    BST.insert(2, 'B');
    CHECK(BST.contains(2));

    BST.insert(5, 'E');
    CHECK(BST.contains(2));

    BST.insert(8, 'H');
    CHECK(BST.contains(2));

    BST.insert(9, 'I');
    CHECK(BST.contains(2));

    BST.insert(1, 'A');
    CHECK(BST.contains(2));

    BST.insert(2, 'b');
    CHECK(BST.contains(2));

    CHECK(BST.size() == 5);
    CHECK(!BST.is_empty());
}

TEST_CASE("TEST REMOVE()")
{
    BSTRAND<int, char, compare_ints, is_equal> BST;

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
    BSTRAND<int, char, compare_ints, is_equal> BST;

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
}

TEST_CASE("TEST CONTAINS()")
{
    BSTRAND<int, char, compare_ints, is_equal> BST;

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
    BSTRAND<int, char, compare_ints, is_equal> BST;

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
    BSTRAND<int, char, compare_ints, is_equal> BST;

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

//due to the randomness of the insert method, height is checked to be less than the number of nodes added (which is the max possible height)
TEST_CASE("TEST HEIGHT()")
{
    BSTRAND<int, char, compare_ints, is_equal> BST;

    CHECK(BST.height() == 0);

    BST.insert(3, 'C');
    CHECK(BST.height() == 1);

    BST.insert(5, 'E');
    CHECK(BST.height() == 2);

    BST.insert(2, 'B');
    CHECK(BST.height() <= 3);

    BST.insert(8, 'H');
    CHECK(BST.height() <= 4);

    BST.insert(9, 'I');
    CHECK(BST.height() <= 5);

    BST.insert(1, 'A');
    CHECK(BST.height() <= 6);
}

TEST_CASE("TEST BALANCE()")
{
    BSTRAND<int, char, compare_ints, is_equal> BST;

    CHECK(BST.balance() == 0);

    BST.insert(3, 'C');
    CHECK(BST.balance() <= 1);

    BST.insert(5, 'E');
    CHECK(abs(BST.balance()) <= 2);

    BST.insert(2, 'B');
    CHECK(abs(BST.balance()) <= 3);

    BST.insert(8, 'H');
    CHECK(abs(BST.balance()) <= 4);

    BST.insert(9, 'I');
    CHECK(abs(BST.balance()) <= 5);

    BST.insert(1, 'A');
    CHECK(abs(BST.balance()) <= 6);
}

TEST_CASE("TEST COPY & MOVE")
{
    BSTRAND<int, char, compare_ints, is_equal> BST1;
    BST1.insert(2, 'B');
    BST1.insert(5, 'E');
    BST1.insert(8, 'H');
    BST1.insert(9, 'I');
    BST1.insert(1, 'A');

    //copy constructor
    BSTRAND<int, char, compare_ints, is_equal> BST2 = BST1;
    CHECK(BST1.size() == 5);
    CHECK(BST2.size() == 5);

    //copy assignment operator
    BSTRAND<int, char, compare_ints, is_equal> BST3;
    BST3 = BST1;
    CHECK(BST1.size() == 5);
    CHECK(BST3.size() == 5);

    //move constructor
    BSTRAND<int, char, compare_ints, is_equal> BST4;
    BST4 = std::move(BST1);
    CHECK(BST1.size() == 0);
    CHECK(BST4.size() == 5);

    //move assignment operator
    BSTRAND<int, char, compare_ints, is_equal> BST5 = std::move(BST2);
    CHECK(BST2.size() == 0);
    CHECK(BST5.size() == 5);
}
