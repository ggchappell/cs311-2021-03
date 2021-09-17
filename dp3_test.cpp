// dp3_test.cpp
// Glenn G. Chappell
// 2021-09-16
//
// For CS 311 Fall 2021
// Test program for Project 3 functions & templates
// For Project 3, Exercises A, B, C, D
// Uses the "doctest" unit-testing framework, version 2
// Requires doctest.h, dp3.h, dp3.cpp

// Includes for code to be tested
#include "dp3.h"             // For Project 3 functions & templates
#include "dp3.h"             // Double-inclusion check, for testing only

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
#include <stdexcept>
using std::out_of_range;
using std::runtime_error;
#include <vector>
using std::vector;
#include <algorithm>
using std::equal;
#include <deque>
using std::deque;
#include <forward_list>
using std::forward_list;
#include <utility>
using std::pair;
#include <string>
using std::string;
#include <initializer_list>
using std::initializer_list;

// Printable name for this test suite
const std::string test_suite_name =
    "Project 3 functions & templates"
    " - CS 311 Proj 3, Ex A, B, C, D";


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


// thisThrows
// Throws a std::runtime_error. For passing to function doesItThrow.
// Will throw std::runtime_error.
void thisThrows()
{
    throw std::runtime_error("Hi!");
}

// thisThrowsStrangely
// Throws an int. For passing to function doesItThrow.
// Will throw int.
void thisThrowsStrangely()
{
    throw -42;
}

// class FuncObj
// Class for do-nothing function objects.
// Do "FuncObj x;", and then we can do "x();".
// The operator() returns nothing and does not throw.
// Invariants: None.
class FuncObj {

// ***** FuncObj: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, Big 5 are used
    FuncObj() = default;
    FuncObj(const FuncObj & other) = default;
    FuncObj & operator=(const FuncObj & other) = default;
    FuncObj(FuncObj && other) = default;
    FuncObj & operator=(FuncObj && other) = default;

// ***** FuncObj: public operators *****
public:

    // operator()
    // Makes an object of this class callable like a function.
    // Does not throw.
    void operator()() const
    {}

};  // end class FuncObj


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "Function return types are correct" )
{
    int throw_stat;  // 0: no throw, 1: throw, 2: throw other

    SUBCASE( "lookup returns value type by value" )
    {
        LLNode<int> * headi = nullptr;
        headi = new LLNode<int>(1, headi);
        try
        {
            [[maybe_unused]] int && ii(lookup(headi, 0));
            throw_stat = 0;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup does not throw" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup returns int" );
        REQUIRE( TypeCheck<int>::check(lookup(headi, 0)) );
        }

        LLNode<double> * headd = nullptr;
        headd = new LLNode<double>(1.1, headd);
        try
        {
            [[maybe_unused]] double && dd(lookup(headd, 0));
            throw_stat = 0;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup does not throw" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup returns double" );
        REQUIRE( TypeCheck<double>::check(lookup(headd, 0)) );
        }
    }

    SUBCASE( "uniqueCount returns size_t by value" )
    {
        vector<int> v { 1, 2, 3 };
        size_t && st(uniqueCount(v.begin(), v.end()));
        (void)st;  // Avoid unused-variable warning
        INFO( "uniqueCount must return std::size_t" );
        REQUIRE( TypeCheck<size_t>::check(uniqueCount(v.begin(),
                                                      v.end())) );
    }

    SUBCASE( "gcd returns int by value" )
    {
        [[maybe_unused]] int && i(gcd(2,3));
        INFO( "gcd returns int by value" );
        REQUIRE( TypeCheck<int>::check(gcd(2,3)) );
    }
}


TEST_CASE( "Function template lookup" )
{
    int throw_stat;  // 0: no throw, 1: throw, 2: throw other
    bool nonempty_what;  // Valid only if throw_stat == 1

    LLNode<int> * headi;     // Head ptr for all int Linked Lists
    LLNode<double> * headd;  // Head ptr for all double Linked Lists

    int ival;                // int value
    double dval;             // double value

    SUBCASE( "Size 0" )
    {
        // Construct list
        headi = nullptr;

        // Index 0
        try
        {
            [[maybe_unused]] int && ii = lookup(headi, 0);
            throw_stat = 0;
        }
        catch (out_of_range & e)
        {
            throw_stat = 1;
            nonempty_what = (string("") != e.what());
        }
        catch (...)
        {
            throw_stat = 2;
        }

        {
        INFO( "lookup must throw on out-of-range index" );
        REQUIRE( throw_stat != 0 );
        }
        {
        INFO( "lookup must throw only std::out_of_range" );
        REQUIRE( throw_stat == 1 );
        }
        {
        INFO( "lookup must throw exception with nonempty .what()" );
        REQUIRE( nonempty_what );
        }

        // Index 1
        try
        {
            [[maybe_unused]] int && ii = lookup(headi, 1);
            throw_stat = 0;
        }
        catch (out_of_range & e)
        {
            throw_stat = 1;
            nonempty_what = (string("") != e.what());
        }
        catch (...)
        {
            throw_stat = 2;
        }

        {
        INFO( "lookup must throw on out-of-range index" );
        REQUIRE( throw_stat != 0 );
        }
        {
        INFO( "lookup must throw only std::out_of_range" );
        REQUIRE( throw_stat == 1 );
        }
        {
        INFO( "lookup must throw exception with nonempty .what()" );
        REQUIRE( nonempty_what );
        }
    }

    SUBCASE( "Size 1" )
    {
        // Construct list
        headd = nullptr;
        headd = new LLNode<double>(3.2, headd);

        // Index 0
        try
        {
            double && dd = lookup(headd, 0);
            throw_stat = 0;
            dval = dd;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup must not throw on in-range index" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup must return 3.2" );
        REQUIRE( dval == 3.2 );
        }

        // Index 1
        try
        {
            [[maybe_unused]] double && dd = lookup(headd, 1);
            throw_stat = 0;
        }
        catch (out_of_range & e)
        {
            throw_stat = 1;
            nonempty_what = (string("") != e.what());
        }
        catch (...)
        {
            throw_stat = 2;
        }

        {
        INFO( "lookup must throw on out-of-range index" );
        REQUIRE( throw_stat != 0 );
        }
        {
        INFO( "lookup must throw only std::out_of_range" );
        REQUIRE( throw_stat == 1 );
        }
        {
        INFO( "lookup must throw exception with nonempty .what()" );
        REQUIRE( nonempty_what );
        }
    }

    SUBCASE( "Size 9" )
    {
        // Construct list
        headi = nullptr;
        headi = new LLNode<int>(64, headi);
        headi = new LLNode<int>(49, headi);
        headi = new LLNode<int>(36, headi);
        headi = new LLNode<int>(25, headi);
        headi = new LLNode<int>(16, headi);
        headi = new LLNode<int>(9, headi);
        headi = new LLNode<int>(4, headi);
        headi = new LLNode<int>(1, headi);
        headi = new LLNode<int>(0, headi);

        // Index 0
        try
        {
            int && ii = lookup(headi, 0);
            throw_stat = 0;
            ival = ii;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup must not throw on in-range index" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup must return 0" );
        REQUIRE( ival == 0 );
        }

        // Index 5
        try
        {
            int && ii = lookup(headi, 5);
            throw_stat = 0;
            ival = ii;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup must not throw on in-range index" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup must return 25" );
        REQUIRE( ival == 25 );
        }

        // Index 8
        try
        {
            int && ii = lookup(headi, 8);
            throw_stat = 0;
            ival = ii;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup must not throw on in-range index" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup must return 64" );
        REQUIRE( ival == 64 );
        }

        // Index 9
        try
        {
            [[maybe_unused]] int && ii = lookup(headi, 9);
            throw_stat = 0;
        }
        catch (out_of_range & e)
        {
            throw_stat = 1;
            nonempty_what = (string("") != e.what());
        }
        catch (...)
        {
            throw_stat = 2;
        }

        {
        INFO( "lookup must throw on out-of-range index" );
        REQUIRE( throw_stat != 0 );
        }
        {
        INFO( "lookup must throw only std::out_of_range" );
        REQUIRE( throw_stat == 1 );
        }
        {
        INFO( "lookup must throw exception with nonempty .what()" );
        REQUIRE( nonempty_what );
        }

        // Index 100
        try
        {
            [[maybe_unused]] int && ii = lookup(headi, 100);
            throw_stat = 0;
        }
        catch (out_of_range & e)
        {
            throw_stat = 1;
            nonempty_what = (string("") != e.what());
        }
        catch (...)
        {
            throw_stat = 2;
        }

        {
        INFO( "lookup must throw on out-of-range index" );
        REQUIRE( throw_stat != 0 );
        }
        {
        INFO( "lookup must throw only std::out_of_range" );
        REQUIRE( throw_stat == 1 );
        }
        {
        INFO( "lookup must throw exception with nonempty .what()" );
        REQUIRE( nonempty_what );
        }
    }
}


TEST_CASE( "Function didItThrow" )
{
    bool didThrow;  // Whether function throws or not

    SUBCASE( "Function throws standard exception class" )
    {
        didThrow = false;
        try
        {
            didItThrow(thisThrows, didThrow);
            INFO( "Throwing function #1 - should re-throw same exception" );
            REQUIRE( false );
        }
        catch (std::runtime_error & e)
        {
            INFO( "Throwing function #1 - should re-throw same exception" );
            REQUIRE( std::string("Hi!") == e.what() );
        }
        catch (...)
        {
            INFO( "Throwing function #1 - should re-throw same exception" );
            REQUIRE( false );
        }
        {
        INFO( "Throwing function #1 - bool param is true" );
        REQUIRE( didThrow );
        }
    }

    SUBCASE( "Function throws int" )
    {
        didThrow = false;
        try
        {
            didItThrow(thisThrowsStrangely, didThrow);
            INFO( "Throwing function #2 - should re-throw same exception" );
            REQUIRE( false );
        }
        catch (int & e)
        {
            INFO( "Throwing function #2 - should re-throw same exception" );
            REQUIRE( e == -42 );
        }
        catch (...)
        {
            INFO( "Throwing function #2 - should re-throw same exception" );
            REQUIRE( false );
        }
        {
        INFO( "Throwing function #2 - bool param is true" );
        REQUIRE( didThrow );
        }
    }

    SUBCASE( "Function object, does not throw" )
    {
        didThrow = true;
        try
        {
            didItThrow(FuncObj(), didThrow);
            INFO( "Non-throwing function object - should not throw" );
            REQUIRE( true );
        }
        catch (...)
        {
            INFO( "Non-throwing function object - should not throw" );
            REQUIRE( false );
        }
        {
        INFO( "Non-throwing function object - bool param is false" );
        REQUIRE_FALSE( didThrow );
        }
    }
}


TEST_CASE( "Function template uniqueCount" )
{
    deque<int> di {                  // Test data
        1, 1, 2, 1, 2, 2, 3, -1, -1, -1, 5, 3, 3, 3, 2, 2, 1, 1, 1
    };
    const size_t bigsize = 10000;  // Size of very long ranges
                                   //  Must be > 9000

    SUBCASE( "Empty range" )
    {
        size_t && result = uniqueCount(di.rbegin(), di.rbegin());
        INFO( "uniqueCount must return 0" );
        REQUIRE( result == 0 );
    }

    SUBCASE( "Range of size 1" )
    {
        size_t && result = uniqueCount(di.rbegin()+3, di.rbegin()+4);
        INFO( "uniqueCount must return 1" );
        REQUIRE( result == 1 );
    }

    SUBCASE( "Range of size 2, equal integers" )
    {
        size_t && result = uniqueCount(di.rbegin()+3, di.rbegin()+5);
        INFO( "uniqueCount must return 1" );
        REQUIRE( result == 1 );
    }

    SUBCASE( "Range of size 2, distinct integers" )
    {
        size_t && result = uniqueCount(di.rbegin()+4, di.rbegin()+6);
        INFO( "uniqueCount must return 2" );
        REQUIRE( result == 2 );
    }

    SUBCASE( "Range of size 3, equal integers" )
    {
        size_t && result = uniqueCount(di.rbegin()+9, di.rbegin()+12);
        INFO( "uniqueCount must return 1" );
        REQUIRE( result == 1 );
    }

    SUBCASE( "Range of size 3, two values" )
    {
        size_t && result = uniqueCount(di.rbegin()+8, di.rbegin()+11);
        INFO( "uniqueCount must return 2" );
        REQUIRE( result == 2 );
    }

    SUBCASE( "Range of size 3, all distinct" )
    {
        size_t && result = uniqueCount(di.rbegin()+7, di.rbegin()+10);
        INFO( "uniqueCount must return 3" );
        REQUIRE( result == 3 );
    }

    SUBCASE( "Longer range #1" )
    {
        size_t && result = uniqueCount(di.rbegin()+5, di.rbegin()+13);
        INFO( "uniqueCount must return 3" );
        REQUIRE( result == 3 );
    }

    SUBCASE( "Longer range #2" )
    {
        size_t && result = uniqueCount(di.rbegin()+3, di.rbegin()+15);
        INFO( "uniqueCount must return 4" );
        REQUIRE( result == 4 );
    }

    SUBCASE( "Longer range #3" )
    {
        size_t && result = uniqueCount(di.rbegin(), di.rend());
        INFO( "uniqueCount must return 5" );
        REQUIRE( result == 5 );
    }

    SUBCASE( "Very long range #1" )
    {
        deque<int> di2(bigsize, 3);
        size_t && result = uniqueCount(di2.rbegin(), di2.rend());
        INFO( "uniqueCount must return 1" );
        REQUIRE( result == 1 );
    }

    SUBCASE( "Very long range #2" )
    {
        deque<int> di2(bigsize, 4);
        di2[9000] = 3;
        size_t && result = uniqueCount(di2.rbegin(), di2.rend());
        INFO( "uniqueCount must return 2" );
        REQUIRE( result == 2 );
    }

    SUBCASE( "Very long range #3" )
    {
        deque<int> di2(bigsize, 5);
        for (size_t i = 0; i < bigsize; i += 2)
            di2[i] = 6;
        size_t && result = uniqueCount(di2.rbegin(), di2.rend());
        INFO( "uniqueCount must return 2" );
        REQUIRE( result == 2 );
    }

    SUBCASE( "Very long range #4" )
    {
        deque<size_t> dsi2(bigsize);
        for (size_t i = 0; i < bigsize; ++i)
            dsi2[i] = i;
        size_t && result = uniqueCount(dsi2.rbegin(), dsi2.rend());
        INFO( "uniqueCount must return " << bigsize );
        REQUIRE( result == bigsize );
    }

    SUBCASE( "Strings, equal" )
    {
        vector<string> vs { "abc", "abc" };
        size_t && result = uniqueCount(vs.begin(), vs.end());
        INFO( "uniqueCount must return 1" );
        REQUIRE( result == 1 );
    }

    SUBCASE( "Strings, distinct" )
    {
        vector<string> vs { "abc", "def" };
        size_t && result = uniqueCount(vs.begin(), vs.end());
        INFO( "uniqueCount must return 2" );
        REQUIRE( result == 2 );
    }
}


TEST_CASE( "Function gcd" )
{
    // Test data
    vector<vector<int>> tdata {
        {       0,      1,     1 },
        {       1,      0,     1 },
        {       0,  27384, 27384 },
        {   27384,      0, 27384 },
        {       1,      1,     1 },
        {       3,     10,     1 },
        {      10,      3,     1 },
        {       6,     15,     3 },
        {      15,      6,     3 },
        {     546,  49335,    39 },
        {   49335,    546,    39 },
        {       5, 100000,     5 },
        {  100000,      5,     5 },
        {       5, 100001,     1 },
        {  100001,      5,     1 },
        {     910,     42,    14 },
        {      42,    910,    14 },
        {  311850, 429975,  4725 },
        {  429975, 311850,  4725 },
        {  196418, 317811,     1 },
        {  317811, 196418,     1 },
        {  196418, 317812,     2 },
        {  317812, 196418,     2 },
    };

    for (const auto v : tdata)
    {
        int && result = gcd(v[0], v[1]);
        INFO( "The GCD of " << v[0] << " and " << v[1] << " is " << v[2]
                  << ", but calling gcd(" << v[0] << ", " << v[1]
                  << ") returned " << result << "." );
        REQUIRE( result == v[2] );
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

