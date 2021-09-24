// hdtcount_test.cpp
// Glenn G. Chappell
// 2021-09-23
//
// For CS 311 Fall 2021
// Test program for function hdtCount
// For Project 4, Exercise A
// Uses the "doctest" unit-testing framework, version 2
// Requires doctest.h, hdtcount.h, hdtcount.cpp

// Includes for code to be tested
#include "hdtcount.h"        // For hdtCount
#include "hdtcount.h"        // Double-inclusion check, for testing only

// Includes for the "doctest" unit-testing framework
#define DOCTEST_CONFIG_IMPLEMENT
                             // We write our own main
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
                             // Reduce compile time
#include "doctest.h"         // For doctest

// Includes for all test programs
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;

// Additional includes for this test program
// (None)

// Printable name for this test suite
const std::string test_suite_name =
    "function hdtCount"
    " - CS 311 Proj 4, Ex A";

// *********************************************************************
// Helper Functions/Classes for This Test Program
// *********************************************************************


// class TypeCheck
// This class exists in order to have static member function "check",
// which takes a parameter of a given type, by reference. Objects of
// type TypeCheck<T> cannot be created.
// Usage:
//     TypeCheck<MyType>::check(x)
//      returns true if the type of x is (MyType) or (const MyType),
//      otherwise false.
// Invariants: None.
// Requirements on Types: None.
template<typename T>
class TypeCheck {

private:

    // No default ctor
    TypeCheck() = delete;

    // Uncopyable. Do not define copy/move ctor/assn.
    TypeCheck(const TypeCheck &) = delete;
    TypeCheck(TypeCheck &&) = delete;
    TypeCheck<T> & operator=(const TypeCheck &) = delete;
    TypeCheck<T> & operator=(TypeCheck &&) = delete;

    // Compiler-generated dctor is used (but irrelevant).
    ~TypeCheck() = default;

public:

    // check
    // The function and function template below simulate a single
    // function that takes a single parameter, and returns true iff the
    // parameter has type T or (const T).

    // check (reference-to-const T)
    // Pre: None.
    // Post:
    //     Return is true.
    // Does not throw (No-Throw Guarantee)
    static bool check([[maybe_unused]] const T & param)
    {
        return true;
    }

    // check (reference-to-const non-T)
    // Pre: None.
    // Post:
    //     Return is false.
    // Requirements on types: None.
    // Does not throw (No-Throw Guarantee)
    template <typename OtherType>
    static bool check([[maybe_unused]] const OtherType & param)
    {
        return false;
    }

};  // End class TypeCheck


// *********************************************************************
// Test Cases
// *********************************************************************


/*
TEST_CASE( "n x 1 and 1 x n boards" )
{
    SUBCASE( "All 3 x 1 boards" )
    {
        REQUIRE( countHSW(3,1, 0,0, 1,0, 2,0) == 1 );
        REQUIRE( countHSW(3,1, 0,0, 2,0, 1,0) == 1 );
        REQUIRE( countHSW(3,1, 1,0, 0,0, 2,0) == 0 );
        REQUIRE( countHSW(3,1, 1,0, 2,0, 0,0) == 0 );
        REQUIRE( countHSW(3,1, 2,0, 0,0, 1,0) == 1 );
        REQUIRE( countHSW(3,1, 2,0, 1,0, 0,0) == 1 );
    }

    SUBCASE( "All 1 x 3 boards" )
    {
        REQUIRE( countHSW(1,3, 0,0, 0,1, 0,2) == 1 );
        REQUIRE( countHSW(1,3, 0,0, 0,2, 0,1) == 1 );
        REQUIRE( countHSW(1,3, 0,1, 0,0, 0,2) == 0 );
        REQUIRE( countHSW(1,3, 0,1, 0,2, 0,0) == 0 );
        REQUIRE( countHSW(1,3, 0,2, 0,0, 0,1) == 1 );
        REQUIRE( countHSW(1,3, 0,2, 0,1, 0,0) == 1 );
    }

    SUBCASE( "All 4 x 1 boards" )
    {
        REQUIRE( countHSW(4,1, 0,0, 1,0, 2,0) == 0 );
        REQUIRE( countHSW(4,1, 0,0, 1,0, 3,0) == 1 );
        REQUIRE( countHSW(4,1, 0,0, 2,0, 1,0) == 0 );
        REQUIRE( countHSW(4,1, 0,0, 2,0, 3,0) == 0 );
        REQUIRE( countHSW(4,1, 0,0, 3,0, 1,0) == 1 );
        REQUIRE( countHSW(4,1, 0,0, 3,0, 2,0) == 0 );
        REQUIRE( countHSW(4,1, 1,0, 0,0, 2,0) == 0 );
        REQUIRE( countHSW(4,1, 1,0, 0,0, 3,0) == 0 );
        REQUIRE( countHSW(4,1, 1,0, 2,0, 0,0) == 0 );
        REQUIRE( countHSW(4,1, 1,0, 2,0, 3,0) == 0 );
        REQUIRE( countHSW(4,1, 1,0, 3,0, 0,0) == 0 );
        REQUIRE( countHSW(4,1, 1,0, 3,0, 2,0) == 0 );
        REQUIRE( countHSW(4,1, 2,0, 0,0, 1,0) == 0 );
        REQUIRE( countHSW(4,1, 2,0, 0,0, 3,0) == 0 );
        REQUIRE( countHSW(4,1, 2,0, 1,0, 0,0) == 0 );
        REQUIRE( countHSW(4,1, 2,0, 1,0, 3,0) == 0 );
        REQUIRE( countHSW(4,1, 2,0, 3,0, 0,0) == 0 );
        REQUIRE( countHSW(4,1, 2,0, 3,0, 1,0) == 0 );
        REQUIRE( countHSW(4,1, 3,0, 0,0, 1,0) == 0 );
        REQUIRE( countHSW(4,1, 3,0, 0,0, 2,0) == 1 );
        REQUIRE( countHSW(4,1, 3,0, 1,0, 0,0) == 0 );
        REQUIRE( countHSW(4,1, 3,0, 1,0, 2,0) == 0 );
        REQUIRE( countHSW(4,1, 3,0, 2,0, 0,0) == 1 );
        REQUIRE( countHSW(4,1, 3,0, 2,0, 1,0) == 0 );
    }

    SUBCASE( "All 1 x 4 boards" )
    {
        REQUIRE( countHSW(1,4, 0,0, 0,1, 0,2) == 0 );
        REQUIRE( countHSW(1,4, 0,0, 0,1, 0,3) == 1 );
        REQUIRE( countHSW(1,4, 0,0, 0,2, 0,1) == 0 );
        REQUIRE( countHSW(1,4, 0,0, 0,2, 0,3) == 0 );
        REQUIRE( countHSW(1,4, 0,0, 0,3, 0,1) == 1 );
        REQUIRE( countHSW(1,4, 0,0, 0,3, 0,2) == 0 );
        REQUIRE( countHSW(1,4, 0,1, 0,0, 0,2) == 0 );
        REQUIRE( countHSW(1,4, 0,1, 0,0, 0,3) == 0 );
        REQUIRE( countHSW(1,4, 0,1, 0,2, 0,0) == 0 );
        REQUIRE( countHSW(1,4, 0,1, 0,2, 0,3) == 0 );
        REQUIRE( countHSW(1,4, 0,1, 0,3, 0,0) == 0 );
        REQUIRE( countHSW(1,4, 0,1, 0,3, 0,2) == 0 );
        REQUIRE( countHSW(1,4, 0,2, 0,0, 0,1) == 0 );
        REQUIRE( countHSW(1,4, 0,2, 0,0, 0,3) == 0 );
        REQUIRE( countHSW(1,4, 0,2, 0,1, 0,0) == 0 );
        REQUIRE( countHSW(1,4, 0,2, 0,1, 0,3) == 0 );
        REQUIRE( countHSW(1,4, 0,2, 0,3, 0,0) == 0 );
        REQUIRE( countHSW(1,4, 0,2, 0,3, 0,1) == 0 );
        REQUIRE( countHSW(1,4, 0,3, 0,0, 0,1) == 0 );
        REQUIRE( countHSW(1,4, 0,3, 0,0, 0,2) == 1 );
        REQUIRE( countHSW(1,4, 0,3, 0,1, 0,0) == 0 );
        REQUIRE( countHSW(1,4, 0,3, 0,1, 0,2) == 0 );
        REQUIRE( countHSW(1,4, 0,3, 0,2, 0,0) == 1 );
        REQUIRE( countHSW(1,4, 0,3, 0,2, 0,1) == 0 );
    }

    SUBCASE( "Various n x 1 boards with n > 4" )
    {
        REQUIRE( countHSW(  5,1,   0,0,   1,0,   4,0) == 1 );
        REQUIRE( countHSW(  5,1,   2,0,   0,0,   4,0) == 0 );
        REQUIRE( countHSW(  7,1,   2,0,   0,0,   4,0) == 0 );
        REQUIRE( countHSW(  8,1,   7,0,   6,0,   0,0) == 1 );
        REQUIRE( countHSW( 20,1,   0,0,  19,0,   1,0) == 1 );
        REQUIRE( countHSW( 25,1,  24,0,   0,0,  22,0) == 0 );
        REQUIRE( countHSW(299,1, 298,0,   0,0, 297,0) == 1 );
        REQUIRE( countHSW(299,1, 297,0, 298,0,   0,0) == 0 );
    }

    SUBCASE( "Various 1 x n boards with n > 4" )
    {
        REQUIRE( countHSW(1,  5, 0,  4, 0,  3, 0,0) == 1 );
        REQUIRE( countHSW(1,  5, 0,  0, 0,  1, 0,4) == 1 );
        REQUIRE( countHSW(1,  6, 0,  1, 0,  5, 0,0) == 0 );
        REQUIRE( countHSW(1,  6, 0,  5, 0,  0, 0,4) == 1 );
        REQUIRE( countHSW(1, 33, 0, 15, 0,  0, 0,1) == 0 );
        REQUIRE( countHSW(1, 50, 0,  0, 0, 49, 0,1) == 1 );
        REQUIRE( countHSW(1,298, 0,296, 0,297, 0,0) == 0 );
        REQUIRE( countHSW(1,299, 0,  0, 0,298, 0,1) == 1 );
    }
}


TEST_CASE( "Small boards" )
{
    SUBCASE( "Various small boards" )
    {
        REQUIRE( countHSW(2,2, 0,0, 1,0, 1,1) ==   1 );
        REQUIRE( countHSW(2,2, 1,0, 1,1, 0,0) ==   1 );
        REQUIRE( countHSW(8,2, 1,0, 1,1, 0,0) ==   0 );
        REQUIRE( countHSW(8,2, 1,0, 0,0, 5,0) ==  96 );
        REQUIRE( countHSW(2,8, 0,1, 1,1, 0,0) ==   0 );
        REQUIRE( countHSW(2,8, 0,1, 0,0, 1,4) ==  64 );
        REQUIRE( countHSW(3,3, 0,0, 0,2, 1,1) ==   6 );
        REQUIRE( countHSW(4,4, 0,2, 2,1, 3,3) == 181 );
        REQUIRE( countHSW(3,5, 0,0, 1,1, 2,4) == 355 );
        REQUIRE( countHSW(2,3, 1,0, 0,1, 1,2) ==   1 );
        REQUIRE( countHSW(3,2, 0,0, 1,0, 1,1) ==   0 );
        REQUIRE( countHSW(4,2, 2,1, 3,0, 0,1) ==   4 );
        REQUIRE( countHSW(3,4, 1,1, 0,3, 2,3) ==  16 );
    }
}


TEST_CASE( "Large boards" )
{
    SUBCASE( "Various large boards" )
    {
        REQUIRE( countHSW(3, 6, 0,0, 1,0, 1,1) ==  945 );
        REQUIRE( countHSW(4, 5, 3,1, 2,0, 0,0) == 5076 );
        REQUIRE( countHSW(5, 4, 2,2, 0,0, 1,3) == 5488 );
        REQUIRE( countHSW(2,10, 0,1, 0,0, 1,0) ==    0 );
        REQUIRE( countHSW(6, 3, 5,2, 4,1, 1,2) == 1047 );
        REQUIRE( countHSW(9, 2, 0,1, 4,0, 1,0) ==  128 );
        REQUIRE( countHSW(7, 2, 3,0, 0,1, 5,0) ==   48 );
    }
}


TEST_CASE( "Slide Examples" )
{
    SUBCASE( "Examples from \"Thoughts on Project 4\" slides" )
    {
        REQUIRE( countHSW(4,2, 1,0, 0,0, 3,1) ==     4 );
        REQUIRE( countHSW(3,2, 2,0, 1,0, 2,1) ==     2 );
        REQUIRE( countHSW(4,1, 1,0, 0,0, 3,0) ==     0 );
        REQUIRE( countHSW(5,4, 4,3, 4,2, 0,0) == 40887 );
    }
}
*/


TEST_CASE( "Function return types are correct" )
{
    SUBCASE( "hdtCount returns int by value" )
    {
        int && ii(hdtCount(1, 2, 0, 0, 0, 1));
        (void)ii;  // Avoid unused-variable warnings
        INFO( "hdtCount must return int by value" );
        REQUIRE( TypeCheck<int>::check(hdtCount(1, 2, 0, 0, 0, 1)) );
    }
}


TEST_CASE( "1 x n boards" )
{
    SUBCASE( "All 1 x n boards with n <= 4" )
    {
        REQUIRE( hdtCount(   1,   2,  0,  0,  0,  1) ==     1 );
        REQUIRE( hdtCount(   1,   3,  0,  0,  0,  1) ==     0 );
        REQUIRE( hdtCount(   1,   3,  0,  0,  0,  2) ==     0 );
        REQUIRE( hdtCount(   1,   3,  0,  1,  0,  2) ==     0 );
        REQUIRE( hdtCount(   1,   4,  0,  0,  0,  1) ==     1 );
        REQUIRE( hdtCount(   1,   4,  0,  0,  0,  2) ==     0 );
        REQUIRE( hdtCount(   1,   4,  0,  0,  0,  3) ==     1 );
        REQUIRE( hdtCount(   1,   4,  0,  1,  0,  2) ==     0 );
        REQUIRE( hdtCount(   1,   4,  0,  1,  0,  3) ==     0 );
        REQUIRE( hdtCount(   1,   4,  0,  2,  0,  3) ==     1 );
    }

    SUBCASE( "w == 1, h < 10" )
    {
        REQUIRE( hdtCount(   1,   5,  0,  0,  0,  4) ==     0 );
        REQUIRE( hdtCount(   1,   6,  0,  0,  0,  1) ==     1 );
        REQUIRE( hdtCount(   1,   6,  0,  0,  0,  3) ==     1 );
        REQUIRE( hdtCount(   1,   6,  0,  0,  0,  4) ==     0 );
        REQUIRE( hdtCount(   1,   6,  0,  0,  0,  5) ==     1 );
        REQUIRE( hdtCount(   1,   6,  0,  2,  0,  5) ==     1 );
        REQUIRE( hdtCount(   1,   6,  0,  3,  0,  5) ==     0 );
        REQUIRE( hdtCount(   1,   6,  0,  4,  0,  5) ==     1 );
        REQUIRE( hdtCount(   1,   7,  0,  2,  0,  3) ==     0 );
        REQUIRE( hdtCount(   1,   8,  0,  2,  0,  3) ==     1 );
        REQUIRE( hdtCount(   1,   9,  0,  2,  0,  3) ==     0 );
    }

    SUBCASE( "w == 1, 10 <= h <= 1000" )
    {
        REQUIRE( hdtCount(   1,  10,  0,  2,  0,  3) ==     1 );
        REQUIRE( hdtCount(   1,  10,  0,  3,  0,  4) ==     0 );
        REQUIRE( hdtCount(   1,  10,  0,  4,  0,  5) ==     1 );
        REQUIRE( hdtCount(   1,  10,  0,  2,  0,  7) ==     1 );
        REQUIRE( hdtCount(   1, 100,  0,  0,  0,  1) ==     1 );
        REQUIRE( hdtCount(   1, 100,  0,  0,  0, 49) ==     1 );
        REQUIRE( hdtCount(   1, 100,  0,  0,  0, 50) ==     0 );
        REQUIRE( hdtCount(   1, 100,  0,  0,  0, 99) ==     1 );
        REQUIRE( hdtCount(   1, 100,  0,  1,  0, 99) ==     0 );
        REQUIRE( hdtCount(   1, 100,  0, 31,  0, 99) ==     0 );
        REQUIRE( hdtCount(   1, 101,  0,  0,  0,  1) ==     0 );
        REQUIRE( hdtCount(   1, 101,  0,  0,  0,100) ==     0 );
        REQUIRE( hdtCount(   1, 999,  0,  0,  0,  1) ==     0 );
        REQUIRE( hdtCount(   1,1000,  0,  0,  0,  1) ==     1 );
        REQUIRE( hdtCount(   1,1000,  0,  0,  0,530) ==     0 );
        REQUIRE( hdtCount(   1,1000,  0,  0,  0,531) ==     1 );
        REQUIRE( hdtCount(   1,1000,  0, 36,  0,927) ==     1 );
        REQUIRE( hdtCount(   1,1000,  0, 37,  0,928) ==     0 );
        REQUIRE( hdtCount(   1,1000,  0, 37,  0,927) ==     0 );
    }
}


TEST_CASE( "n x 1 boards" )
{
    SUBCASE( "All n x 1 boards with n <= 4" )
    {
        REQUIRE( hdtCount(   2,   1,  0,  0,  1,  0) ==     1 );
        REQUIRE( hdtCount(   3,   1,  0,  0,  1,  0) ==     0 );
        REQUIRE( hdtCount(   3,   1,  0,  0,  2,  0) ==     0 );
        REQUIRE( hdtCount(   3,   1,  1,  0,  2,  0) ==     0 );
        REQUIRE( hdtCount(   4,   1,  0,  0,  1,  0) ==     1 );
        REQUIRE( hdtCount(   4,   1,  0,  0,  2,  0) ==     0 );
        REQUIRE( hdtCount(   4,   1,  0,  0,  3,  0) ==     1 );
        REQUIRE( hdtCount(   4,   1,  1,  0,  2,  0) ==     0 );
        REQUIRE( hdtCount(   4,   1,  1,  0,  3,  0) ==     0 );
        REQUIRE( hdtCount(   4,   1,  2,  0,  3,  0) ==     1 );
    }

    SUBCASE( "w < 10, w == 1" )
    {
        REQUIRE( hdtCount(   5,   1,  0,  0,  4,  0) ==     0 );
        REQUIRE( hdtCount(   6,   1,  0,  0,  1,  0) ==     1 );
        REQUIRE( hdtCount(   6,   1,  0,  0,  3,  0) ==     1 );
        REQUIRE( hdtCount(   6,   1,  0,  0,  4,  0) ==     0 );
        REQUIRE( hdtCount(   6,   1,  0,  0,  5,  0) ==     1 );
        REQUIRE( hdtCount(   6,   1,  2,  0,  5,  0) ==     1 );
        REQUIRE( hdtCount(   6,   1,  3,  0,  5,  0) ==     0 );
        REQUIRE( hdtCount(   6,   1,  4,  0,  5,  0) ==     1 );
        REQUIRE( hdtCount(   7,   1,  2,  0,  3,  0) ==     0 );
        REQUIRE( hdtCount(   8,   1,  2,  0,  3,  0) ==     1 );
        REQUIRE( hdtCount(   9,   1,  2,  0,  3,  0) ==     0 );
    }

    SUBCASE( "10 <= w <= 1000, h == 1" )
    {
        REQUIRE( hdtCount(  10,   1,  2,  0,  3,  0) ==     1 );
        REQUIRE( hdtCount(  10,   1,  3,  0,  4,  0) ==     0 );
        REQUIRE( hdtCount(  10,   1,  4,  0,  5,  0) ==     1 );
        REQUIRE( hdtCount(  10,   1,  2,  0,  7,  0) ==     1 );
        REQUIRE( hdtCount( 100,   1,  0,  0,  1,  0) ==     1 );
        REQUIRE( hdtCount( 100,   1,  0,  0, 49,  0) ==     1 );
        REQUIRE( hdtCount( 100,   1,  0,  0, 50,  0) ==     0 );
        REQUIRE( hdtCount( 100,   1,  0,  0, 99,  0) ==     1 );
        REQUIRE( hdtCount( 100,   1,  1,  0, 99,  0) ==     0 );
        REQUIRE( hdtCount( 100,   1, 31,  0, 99,  0) ==     0 );
        REQUIRE( hdtCount( 101,   1,  0,  0,  1,  0) ==     0 );
        REQUIRE( hdtCount( 101,   1,  0,  0,100,  0) ==     0 );
        REQUIRE( hdtCount( 999,   1,  0,  0,  1,  0) ==     0 );
        REQUIRE( hdtCount(1000,   1,  0,  0,  1,  0) ==     1 );
        REQUIRE( hdtCount(1000,   1,  0,  0,530,  0) ==     0 );
        REQUIRE( hdtCount(1000,   1,  0,  0,531,  0) ==     1 );
        REQUIRE( hdtCount(1000,   1, 36,  0,927,  0) ==     1 );
        REQUIRE( hdtCount(1000,   1, 37,  0,928,  0) ==     0 );
        REQUIRE( hdtCount(1000,   1, 37,  0,927,  0) ==     0 );
    }
}


TEST_CASE( "2 x n boards" )
{
    SUBCASE( "w == 2, 1 <= h <= 20, forbidden (0,0), (1,0)" )
    {
        REQUIRE( hdtCount(   2,   1,  0,  0,  1,  0) ==     1 );
        REQUIRE( hdtCount(   2,   2,  0,  0,  1,  0) ==     1 );
        REQUIRE( hdtCount(   2,   3,  0,  0,  1,  0) ==     2 );
        REQUIRE( hdtCount(   2,   4,  0,  0,  1,  0) ==     3 );
        REQUIRE( hdtCount(   2,   5,  0,  0,  1,  0) ==     5 );
        REQUIRE( hdtCount(   2,   6,  0,  0,  1,  0) ==     8 );
        REQUIRE( hdtCount(   2,   7,  0,  0,  1,  0) ==    13 );
        REQUIRE( hdtCount(   2,   8,  0,  0,  1,  0) ==    21 );
        REQUIRE( hdtCount(   2,   9,  0,  0,  1,  0) ==    34 );
        REQUIRE( hdtCount(   2,  10,  0,  0,  1,  0) ==    55 );
        REQUIRE( hdtCount(   2,  11,  0,  0,  1,  0) ==    89 );
        REQUIRE( hdtCount(   2,  12,  0,  0,  1,  0) ==   144 );
        REQUIRE( hdtCount(   2,  13,  0,  0,  1,  0) ==   233 );
        REQUIRE( hdtCount(   2,  14,  0,  0,  1,  0) ==   377 );
        REQUIRE( hdtCount(   2,  15,  0,  0,  1,  0) ==   610 );
        REQUIRE( hdtCount(   2,  16,  0,  0,  1,  0) ==   987 );
        REQUIRE( hdtCount(   2,  17,  0,  0,  1,  0) ==  1597 );
        REQUIRE( hdtCount(   2,  18,  0,  0,  1,  0) ==  2584 );
        REQUIRE( hdtCount(   2,  19,  0,  0,  1,  0) ==  4181 );
        REQUIRE( hdtCount(   2,  20,  0,  0,  1,  0) ==  6765 );
        REQUIRE( hdtCount(   2,  21,  0,  0,  1,  0) == 10946 );
    }

    SUBCASE( "w == 2, 1 <= h <= 20, other forbidden" )
    {
        REQUIRE( hdtCount(   2,   2,  0,  1,  1,  0) ==     0 );
        REQUIRE( hdtCount(   2,   2,  1,  0,  1,  1) ==     1 );
        REQUIRE( hdtCount(   2,   3,  0,  0,  1,  2) ==     1 );
        REQUIRE( hdtCount(   2,   4,  0,  0,  0,  1) ==     2 );
        REQUIRE( hdtCount(   2,   5,  0,  0,  0,  1) ==     3 );
        REQUIRE( hdtCount(   2,   6,  0,  2,  1,  2) ==     6 );
        REQUIRE( hdtCount(   2,   7,  0,  3,  1,  3) ==     9 );
        REQUIRE( hdtCount(   2,  19,  0,  4,  1,  5) ==     0 );
        REQUIRE( hdtCount(   2,  20,  0,  6,  1,  6) ==  4901 );
    }
}


TEST_CASE( "n x 2 boards" )
{
    SUBCASE( "1 <= w <= 21, h == 2, forbidden (0,0), (0,1)" )
    {
        REQUIRE( hdtCount(   1,   2,  0,  0,  0,  1) ==     1 );
        REQUIRE( hdtCount(   2,   2,  0,  0,  0,  1) ==     1 );
        REQUIRE( hdtCount(   3,   2,  0,  0,  0,  1) ==     2 );
        REQUIRE( hdtCount(   4,   2,  0,  0,  0,  1) ==     3 );
        REQUIRE( hdtCount(   5,   2,  0,  0,  0,  1) ==     5 );
        REQUIRE( hdtCount(   6,   2,  0,  0,  0,  1) ==     8 );
        REQUIRE( hdtCount(   7,   2,  0,  0,  0,  1) ==    13 );
        REQUIRE( hdtCount(   8,   2,  0,  0,  0,  1) ==    21 );
        REQUIRE( hdtCount(   9,   2,  0,  0,  0,  1) ==    34 );
        REQUIRE( hdtCount(  10,   2,  0,  0,  0,  1) ==    55 );
        REQUIRE( hdtCount(  11,   2,  0,  0,  0,  1) ==    89 );
        REQUIRE( hdtCount(  12,   2,  0,  0,  0,  1) ==   144 );
        REQUIRE( hdtCount(  13,   2,  0,  0,  0,  1) ==   233 );
        REQUIRE( hdtCount(  14,   2,  0,  0,  0,  1) ==   377 );
        REQUIRE( hdtCount(  15,   2,  0,  0,  0,  1) ==   610 );
        REQUIRE( hdtCount(  16,   2,  0,  0,  0,  1) ==   987 );
        REQUIRE( hdtCount(  17,   2,  0,  0,  0,  1) ==  1597 );
        REQUIRE( hdtCount(  18,   2,  0,  0,  0,  1) ==  2584 );
        REQUIRE( hdtCount(  19,   2,  0,  0,  0,  1) ==  4181 );
        REQUIRE( hdtCount(  20,   2,  0,  0,  0,  1) ==  6765 );
        REQUIRE( hdtCount(  21,   2,  0,  0,  0,  1) == 10946 );
    }

    SUBCASE( "1 <= w <= 21, h == 2, other forbidden" )
    {
        REQUIRE( hdtCount(   2,   2,  1,  0,  0,  1) ==     0 );
        REQUIRE( hdtCount(   2,   2,  0,  1,  1,  1) ==     1 );
        REQUIRE( hdtCount(   3,   2,  0,  0,  2,  1) ==     1 );
        REQUIRE( hdtCount(   4,   2,  0,  0,  1,  0) ==     2 );
        REQUIRE( hdtCount(   5,   2,  0,  0,  1,  0) ==     3 );
        REQUIRE( hdtCount(   6,   2,  2,  0,  2,  1) ==     6 );
        REQUIRE( hdtCount(   7,   2,  3,  0,  3,  1) ==     9 );
        REQUIRE( hdtCount(  19,   2,  4,  0,  5,  1) ==     0 );
        REQUIRE( hdtCount(  20,   2,  6,  0,  6,  1) ==  4901 );
    }
}


TEST_CASE( "Larger boards" )
{
    SUBCASE( "w & h both odd" )
    {
        REQUIRE( hdtCount(   3,   3,  0,  1,  0,  2) ==     0 );
        REQUIRE( hdtCount(   3,   5,  0,  1,  0,  2) ==     0 );
        REQUIRE( hdtCount(   3,  11,  0,  1,  0,  2) ==     0 );
        REQUIRE( hdtCount(   3,  13,  0,  1,  0,  2) ==     0 );
        REQUIRE( hdtCount(   5,   7,  0,  1,  0,  2) ==     0 );
        REQUIRE( hdtCount(   7,   3,  2,  2,  5,  1) ==     0 );
    }

    SUBCASE( "Either w or h even, but still no tiling" )
    {
        REQUIRE( hdtCount(   3,   4,  1,  1,  2,  2) ==     0 );
        REQUIRE( hdtCount(   4,   5,  0,  0,  2,  2) ==     0 );
        REQUIRE( hdtCount(   4,   6,  1,  3,  2,  0) ==     0 );
        REQUIRE( hdtCount(   5,   8,  1,  5,  4,  2) ==     0 );
        REQUIRE( hdtCount(   6,   7,  1,  4,  3,  2) ==     0 );
        REQUIRE( hdtCount(   6,   7,  0,  0,  0,  2) ==     0 );
        REQUIRE( hdtCount(   6,   7,  0,  0,  1,  1) ==     0 );
        REQUIRE( hdtCount(   7,   6,  0,  0,  1,  1) ==     0 );
    }

    SUBCASE( "Larger boards with tilings" )
    {
        REQUIRE( hdtCount(   3,   4,  1,  1,  2,  3) ==     3 );
        REQUIRE( hdtCount(   4,   5,  0,  0,  2,  3) ==    15 );
        REQUIRE( hdtCount(   4,   6,  1,  3,  2,  1) ==    29 );
        REQUIRE( hdtCount(   5,   8,  1,  5,  4,  3) ==  1080 );
        REQUIRE( hdtCount(   6,   7,  1,  4,  3,  3) ==  3312 );
        REQUIRE( hdtCount(   6,   7,  0,  0,  0,  1) == 14603 );
        REQUIRE( hdtCount(   6,   7,  0,  0,  1,  0) == 16926 );
        REQUIRE( hdtCount(   7,   4,  1,  0,  3,  1) ==   100 );
        REQUIRE( hdtCount(   7,   6,  0,  0,  3,  0) ==  7216 );
        REQUIRE( hdtCount(  14,   3,  5,  1,  2,  1) ==   459 );
    }
}


TEST_CASE( "Slide Examples" )
{
    SUBCASE( "Examples from \"Thoughts on Project 4\" slides" )
    {
        REQUIRE( hdtCount(   4,   3,  2,  0,  3,  2) ==     4 );
        REQUIRE( hdtCount(   3,   2,  2,  1,  0,  0) ==     1 );
        REQUIRE( hdtCount(   4,   1,  1,  0,  3,  0) ==     0 );
        REQUIRE( hdtCount(   8,   5,  6,  4,  7,  4) ==  8291 );
    }
}


// *********************************************************************
// Main Program
// *********************************************************************


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Run all tests. Prompt for ENTER before exiting.
int main(int argc,
         char *argv[])
{
    doctest::Context dtcontext;
                             // Primary doctest object
    int dtresult;            // doctest return code; for return by main

    // Handle command line
    dtcontext.applyCommandLine(argc, argv);
    dtresult = 0;            // doctest flags no command-line errors
                             //  (strange but true)

    if (!dtresult)           // Continue only if no command-line error
    {
        // Run test suites
        cout << "BEGIN tests for " << test_suite_name << "\n" << endl;
        dtresult = dtcontext.run();
        cout << "END tests for " << test_suite_name << "\n" << endl;
    }

    // If we want to do something else here, then we need to check
    // context.shouldExit() first.

    // Wait for user
    std::cout << "Press ENTER to quit ";
    userPause();

    // Program return value is return code from doctest
    return dtresult;
}

