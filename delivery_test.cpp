// delivery_test.cpp
// Glenn G. Chappell
// 2021-08-31
//
// For CS 311 Fall 2021
// Test program for class Delivery
// For Project 1, Exercise A
// Uses the "doctest" unit-testing framework, version 2
// Requires doctest.h, delivery.h, delivery.cpp

// Includes for code to be tested
#include "delivery.h"        // For class Delivery
#include "delivery.h"        // Double-inclusion check, for testing only

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
#include <string>
using std::string;
#include <ostream>
using std::ostream;
#include <sstream>
using std::ostringstream;
#include <cstddef>
using std::size_t;
#include <utility>
using std::move;
#include <vector>
using std::vector;

// Printable name for this test suite
const string test_suite_name =
    "class Delivery"
    " - CS 311 Proj 1, Ex A";


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


TEST_CASE( "Function return types are correct" )
{
    Delivery t1;
    Delivery t2;

    SUBCASE( "Copy assn returns Delivery by ref" )
    {
        [[maybe_unused]] Delivery & r(t1 = t2);  // By-ref ck
        REQUIRE( TypeCheck<Delivery>::check(t1 = t2) );
    }

    SUBCASE( "Move assn returns Delivery by ref" )
    {
        Delivery t_movable;
        [[maybe_unused]] Delivery & r(t1 = move(t_movable));  // By-ref ck
        REQUIRE( TypeCheck<Delivery>::check(t1 = move(t_movable)) );
    }

    SUBCASE( "Delivery::getName returns string by value" )
    {
        [[maybe_unused]] string && rr(t1.getName());  // by-value ck
        REQUIRE( TypeCheck<string>::check(t1.getName()) );
    }

    SUBCASE( "Delivery::getQuantity returns int by value" )
    {
        [[maybe_unused]] int && rr(t1.getQuantity());  // by-value ck
        REQUIRE( TypeCheck<int>::check(t1.getQuantity()) );
    }

    SUBCASE( "Delivery::getMonth returns int by value" )
    {
        [[maybe_unused]] int && rr(t1.getMonth());  // by-value ck
        REQUIRE( TypeCheck<int>::check(t1.getMonth()) );
    }

    SUBCASE( "Delivery::empty returns bool by value" )
    {
        [[maybe_unused]] bool && rr(t1.empty());  // by-value ck
        REQUIRE( TypeCheck<bool>::check(t1.empty()) );
    }

    SUBCASE( "Delivery::toString returns string by value" )
    {
        [[maybe_unused]] string && rr(t1.toString());  // by-value ck
        REQUIRE( TypeCheck<string>::check(t1.toString()) );
    }

    SUBCASE( "Delivery::operator++ [pre] returns Delivery by ref" )
    {
        [[maybe_unused]] Delivery & r(++t1);  // By-reference ck
        REQUIRE( TypeCheck<Delivery>::check(++t1) );
    }

    SUBCASE( "Delivery::operator++ [post] returns Delivery by value" )
    {
        [[maybe_unused]] Delivery && rr(t1++);  // by-value ck
        REQUIRE( TypeCheck<Delivery>::check(t1++) );
    }

    SUBCASE( "Delivery::operator-- [pre] returns Delivery by ref" )
    {
        [[maybe_unused]] Delivery & r(--t1);  // By-ref ck
        REQUIRE( TypeCheck<Delivery>::check(--t1) );
    }

    SUBCASE( "Delivery::operator-- [post] returns Delivery by value" )
    {
        [[maybe_unused]] Delivery && rr(t1--);  // by-value ck
        REQUIRE( TypeCheck<Delivery>::check(t1--) );
    }

    SUBCASE( "operator==(Delivery,Delivery) returns bool by value" )
    {
        [[maybe_unused]] bool && rr(t1 == t2);  // by-value ck
        REQUIRE( TypeCheck<bool>::check(t1 == t2) );
    }

    SUBCASE( "operator!=(Delivery,Delivery) returns bool by value" )
    {
        [[maybe_unused]] bool && rr(t1 != t2);  // by-value ck
        REQUIRE( TypeCheck<bool>::check(t1 != t2) );
    }

    SUBCASE( "operator<<(ostream,Delivery) returns ostream by ref" )
    {
        ostringstream ostr;
        [[maybe_unused]] ostream & r(ostr << t1);  // By-ref ck
        REQUIRE( TypeCheck<ostream>::check(ostr << t1) );
    }
}


TEST_CASE( "Functions are const-correct (passes if it compiles)" )
{
    SUBCASE( "Calling functions on a const Delivery object" )
    {
        const Delivery tc1;

        [[maybe_unused]] string s = tc1.getName();    // Delivery::getName
        [[maybe_unused]] int q = tc1.getQuantity();   // Delivery::getQuantity
        [[maybe_unused]] int m = tc1.getMonth();      // Delivery::getMonth
        [[maybe_unused]] bool b = tc1.empty();        // Delivery::empty
        [[maybe_unused]] string s2 = tc1.toString();  // Delivery::toString

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }

    SUBCASE( "Taking const Delivery arguments" )
    {
        const Delivery tc1;
        const Delivery tc2;

        Delivery t3 = tc1;      // Copy ctor
        t3 = tc1;                    // Copy assn

        [[maybe_unused]] bool b1 = (tc1 == tc2);      // op==(Delivery,Delivery)
        [[maybe_unused]] bool b2 = (tc1 != tc2);      // op!=(Delivery,Delivery)
        ostringstream ostr;
        ostr << tc1;                 // op<<(ostring,Delivery)

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }

    SUBCASE( "Taking const string arguments" )
    {
        const string s;

        Delivery t(s, 0, 1);         // Data ctor
        t.setName(s);                // Delivery::setName

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }
}


TEST_CASE( "Default-constructed Delivery object" )
{
    Delivery t1;

    SUBCASE( "Check initial values" )
    {
        REQUIRE( t1.getName() == "UNSPECIFIED" );
        REQUIRE( t1.getQuantity() == 0 );
        REQUIRE( t1.getMonth() == 1 );
        REQUIRE( t1.empty() );
    }

    SUBCASE( "Set name" )
    {
        t1.setName("abc");

        REQUIRE( t1.getName() == "abc" );
        REQUIRE( t1.getQuantity() == 0 );
        REQUIRE( t1.getMonth() == 1 );
        REQUIRE( t1.empty() );
    }

    SUBCASE( "Set quantity" )
    {
        t1.setQuantity(20);

        REQUIRE( t1.getName() == "UNSPECIFIED" );
        REQUIRE( t1.getQuantity() == 20 );
        REQUIRE( t1.getMonth() == 1 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set month" )
    {
        t1.setMonth(12);

        REQUIRE( t1.getName() == "UNSPECIFIED" );
        REQUIRE( t1.getQuantity() == 0 );
        REQUIRE( t1.getMonth() == 12 );
        REQUIRE( t1.empty() );
    }

    SUBCASE( "Set name, quantity" )
    {
        t1.setName("def");
        t1.setQuantity(30);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getQuantity() == 30 );
        REQUIRE( t1.getMonth() == 1 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set quantity, name" )
    {
        t1.setQuantity(40);
        t1.setName("ghi");

        REQUIRE( t1.getName() == "ghi" );
        REQUIRE( t1.getQuantity() == 40 );
        REQUIRE( t1.getMonth() == 1 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set name, month" )
    {
        t1.setName("jkl");
        t1.setMonth(11);

        REQUIRE( t1.getName() == "jkl" );
        REQUIRE( t1.getQuantity() == 0 );
        REQUIRE( t1.getMonth() == 11 );
        REQUIRE( t1.empty() );
    }

    SUBCASE( "Set month, name" )
    {
        t1.setMonth(10);
        t1.setName("mno");

        REQUIRE( t1.getName() == "mno" );
        REQUIRE( t1.getQuantity() == 0 );
        REQUIRE( t1.getMonth() == 10 );
        REQUIRE( t1.empty() );
    }

    SUBCASE( "Set quantity, month" )
    {
        t1.setQuantity(101);
        t1.setMonth(9);

        REQUIRE( t1.getName() == "UNSPECIFIED" );
        REQUIRE( t1.getQuantity() == 101 );
        REQUIRE( t1.getMonth() == 9 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set month, quantity" )
    {
        t1.setMonth(8);
        t1.setQuantity(102);

        REQUIRE( t1.getName() == "UNSPECIFIED" );
        REQUIRE( t1.getQuantity() == 102 );
        REQUIRE( t1.getMonth() == 8 );
        REQUIRE_FALSE( t1.empty() );
    }
}


TEST_CASE( "Data-constructed Delivery object" )
{
    Delivery t1("xyz", 100, 5);

    SUBCASE( "Check initial values" )
    {
        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getQuantity() == 100 );
        REQUIRE( t1.getMonth() == 5 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set name" )
    {
        t1.setName("abc");

        REQUIRE( t1.getName() == "abc" );
        REQUIRE( t1.getQuantity() == 100 );
        REQUIRE( t1.getMonth() == 5 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set quantity" )
    {
        t1.setQuantity(20);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getQuantity() == 20 );
        REQUIRE( t1.getMonth() == 5 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set month" )
    {
        t1.setMonth(12);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getQuantity() == 100 );
        REQUIRE( t1.getMonth() == 12 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set name, quantity" )
    {
        t1.setName("def");
        t1.setQuantity(30);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getQuantity() == 30 );
        REQUIRE( t1.getMonth() == 5 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set quantity, name" )
    {
        t1.setQuantity(0);
        t1.setName("ghi");

        REQUIRE( t1.getName() == "ghi" );
        REQUIRE( t1.getQuantity() == 0 );
        REQUIRE( t1.getMonth() == 5 );
        REQUIRE( t1.empty() );
    }

    SUBCASE( "Set name, month" )
    {
        t1.setName("def");
        t1.setMonth(11);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getQuantity() == 100 );
        REQUIRE( t1.getMonth() == 11 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set month, name" )
    {
        t1.setMonth(10);
        t1.setName("ghi");

        REQUIRE( t1.getName() == "ghi" );
        REQUIRE( t1.getQuantity() == 100 );
        REQUIRE( t1.getMonth() == 10 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set quantity, month" )
    {
        t1.setQuantity(101);
        t1.setMonth(9);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getQuantity() == 101 );
        REQUIRE( t1.getMonth() == 9 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Set month, quantity" )
    {
        t1.setMonth(8);
        t1.setQuantity(0);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getQuantity() == 0 );
        REQUIRE( t1.getMonth() == 8 );
        REQUIRE( t1.empty() );
    }
}


TEST_CASE( "Copied Delivery objects" )
{
    SUBCASE( "Copy-constructed Delivery object" )
    {
        Delivery t1("xyz", 100, 5);
        Delivery t2 = t1;

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getQuantity() == 100 );
        REQUIRE( t1.getMonth() == 5 );
        REQUIRE_FALSE( t1.empty() );
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getQuantity() == 100 );
        REQUIRE( t1.getMonth() == 5 );
        REQUIRE_FALSE( t2.empty() );

        t2.setName("abc");
        t2.setQuantity(10);
        t2.setMonth(3);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getQuantity() == 100 );
        REQUIRE( t1.getMonth() == 5 );
        REQUIRE_FALSE( t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getQuantity() == 10 );
        REQUIRE( t2.getMonth() == 3 );
        REQUIRE_FALSE( t2.empty() );

        t1.setName("def");
        t1.setQuantity(20);
        t1.setMonth(12);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getQuantity() == 20 );
        REQUIRE( t1.getMonth() == 12 );
        REQUIRE_FALSE( t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getQuantity() == 10 );
        REQUIRE( t2.getMonth() == 3 );
        REQUIRE_FALSE( t2.empty() );
    }

    SUBCASE( "Copy-assigned Delivery object" )
    {
        Delivery t1("xyz", 100, 5);
        Delivery t2;
        t2 = t1;

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getQuantity() == 100 );
        REQUIRE( t1.getMonth() == 5 );
        REQUIRE_FALSE( t1.empty() );
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getQuantity() == 100 );
        REQUIRE( t1.getMonth() == 5 );
        REQUIRE_FALSE( t2.empty() );

        t2.setName("abc");
        t2.setQuantity(10);
        t2.setMonth(3);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getQuantity() == 100 );
        REQUIRE( t1.getMonth() == 5 );
        REQUIRE_FALSE( t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getQuantity() == 10 );
        REQUIRE( t2.getMonth() == 3);
        REQUIRE_FALSE( t2.empty() );

        t1.setName("def");
        t1.setQuantity(0);
        t1.setMonth(12);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getQuantity() == 0 );
        REQUIRE( t1.getMonth() == 12 );
        REQUIRE( t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getQuantity() == 10 );
        REQUIRE( t2.getMonth() == 3 );
        REQUIRE_FALSE( t2.empty() );
    }
}


TEST_CASE( "String conversions" )
{
    Delivery t1;
    Delivery t2("xyz", 100, 5);
    Delivery t3("", 0, 11);
    vector<string> mostrs {
        "DUMMY", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    SUBCASE( "Delivery::toString" )
    {
        REQUIRE( t1.toString() == "UNSPECIFIED (0), Jan" );
        REQUIRE( t2.toString() == "xyz (100), May" );
        REQUIRE( t3.toString() == " (0), Nov" );
    }

    SUBCASE( "Delivery::toString - check all months" )
    {
        for (int mo = 1; mo <= 12; ++mo)
        {
            Delivery tm("x", 0, mo);
            REQUIRE( tm.toString() == "x (0), " + mostrs[mo] );
        }
    }

    SUBCASE( "operator<<(ostream,Delivery)" )
    {
        ostringstream ostr1;
        ostr1 << t1;
        REQUIRE( ostr1.str() == "UNSPECIFIED (0), Jan" );
        ostringstream ostr2;
        ostr2 << t2;
        REQUIRE( ostr2.str() == "xyz (100), May" );
        ostringstream ostr3;
        ostr3 << t3;
        REQUIRE( ostr3.str() == " (0), Nov" );
    }

    SUBCASE( "operator<<(ostream,Delivery) - check all months" )
    {
        for (int mo = 1; mo <= 12; ++mo)
        {
            Delivery tm("x", 0, mo);
            ostringstream ostrm;
            ostrm << tm;
            REQUIRE( ostrm.str() == "x (0), " + mostrs[mo] );
        }
    }

}


TEST_CASE( "Increment & decrement" )
{
    Delivery t1;
    Delivery t2("xyz", 10, 2);

    SUBCASE( "Increment ordinary object" )
    {
        Delivery t3 = (++t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getQuantity() == 11 );
        REQUIRE( t2.getMonth() == 2 );
        REQUIRE_FALSE( t2.empty() );
        REQUIRE( t3.getName() == "xyz" );
        REQUIRE( t3.getQuantity() == 11 );
        REQUIRE( t3.getMonth() == 2 );
        REQUIRE_FALSE( t3.empty() );

        Delivery t4 = (t2++);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getQuantity() == 12);
        REQUIRE( t2.getMonth() == 2 );
        REQUIRE_FALSE( t2.empty() );
        REQUIRE( t4.getName() == "xyz" );
        REQUIRE( t4.getQuantity() == 11 );
        REQUIRE( t4.getMonth() == 2 );
        REQUIRE_FALSE( t4.empty() );

        ++(++t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getQuantity() == 14 );
        REQUIRE( t2.getMonth() == 2 );
        REQUIRE_FALSE( t2.empty() );
    }

    SUBCASE( "Increment object with zero quantity" )
    {
        ++t1;
        REQUIRE( t1.getName() == "UNSPECIFIED" );
        REQUIRE( t1.getQuantity() == 1 );
        REQUIRE( t1.getMonth() == 1 );
        REQUIRE_FALSE( t1.empty() );

        t1++;
        REQUIRE( t1.getName() == "UNSPECIFIED" );
        REQUIRE( t1.getQuantity() == 2 );
        REQUIRE( t1.getMonth() == 1 );
        REQUIRE_FALSE( t1.empty() );
    }

    SUBCASE( "Decrement ordinary object" )
    {
        Delivery t3 = (--t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getQuantity() == 9 );
        REQUIRE( t2.getMonth() == 2 );
        REQUIRE_FALSE( t2.empty() );
        REQUIRE( t3.getName() == "xyz" );
        REQUIRE( t3.getQuantity() == 9 );
        REQUIRE( t3.getMonth() == 2 );
        REQUIRE_FALSE( t3.empty() );

        Delivery t4 = (t2--);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getQuantity() == 8 );
        REQUIRE( t2.getMonth() == 2 );
        REQUIRE_FALSE( t2.empty() );
        REQUIRE( t4.getName() == "xyz" );
        REQUIRE( t4.getQuantity() == 9 );
        REQUIRE( t4.getMonth() == 2 );
        REQUIRE_FALSE( t4.empty() );

        --(--t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getQuantity() == 6 );
        REQUIRE( t2.getMonth() == 2 );
        REQUIRE_FALSE( t2.empty() );
    }

    SUBCASE( "Decrement object with zero quantity" )
    {
        --t1;
        REQUIRE( t1.getName() == "UNSPECIFIED" );
        REQUIRE( t1.getQuantity() == 0 );
        REQUIRE( t1.getMonth() == 1 );
        REQUIRE( t1.empty() );

        t1--;
        REQUIRE( t1.getName() == "UNSPECIFIED" );
        REQUIRE( t1.getQuantity() == 0 );
        REQUIRE( t1.getMonth() == 1 );
        REQUIRE( t1.empty() );
    }
}


TEST_CASE( "Equality & inequality" )
{
    Delivery t1("abc", 10, 7);  // Base value
    Delivery t2("abc", 10, 7);  // Same
    Delivery t3("def", 10, 7);  // Different name
    Delivery t4("abc", 20, 7);  // Different quantity
    Delivery t5("def", 20, 7);  // Different name, quantity
    Delivery t6("abc", 10, 8);  // Different month
    Delivery t7("def", 10, 8);  // Different name, month
    Delivery t8("abc", 20, 8);  // Different quantity, month
    Delivery t9("def", 20, 8);  // Different name, quantity, month

    SUBCASE( "Equality" )
    {
        REQUIRE( t1 == t1 );
        REQUIRE( t1 == t2 );
        REQUIRE( t2 == t1 );
        REQUIRE_FALSE( t1 == t3 );
        REQUIRE_FALSE( t3 == t1 );
        REQUIRE_FALSE( t1 == t4 );
        REQUIRE_FALSE( t4 == t1 );
        REQUIRE_FALSE( t1 == t5 );
        REQUIRE_FALSE( t5 == t1 );
        REQUIRE_FALSE( t1 == t6 );
        REQUIRE_FALSE( t6 == t1 );
        REQUIRE_FALSE( t1 == t7 );
        REQUIRE_FALSE( t7 == t1 );
        REQUIRE_FALSE( t1 == t8 );
        REQUIRE_FALSE( t8 == t1 );
        REQUIRE_FALSE( t1 == t9 );
        REQUIRE_FALSE( t9 == t1 );
    }

    SUBCASE( "Inequality" )
    {
        REQUIRE_FALSE( t1 != t1 );
        REQUIRE_FALSE( t1 != t2 );
        REQUIRE_FALSE( t2 != t1 );
        REQUIRE( t1 != t3 );
        REQUIRE( t3 != t1 );
        REQUIRE( t1 != t4 );
        REQUIRE( t4 != t1 );
        REQUIRE( t1 != t5 );
        REQUIRE( t5 != t1 );
        REQUIRE( t1 != t6 );
        REQUIRE( t6 != t1 );
        REQUIRE( t1 != t7 );
        REQUIRE( t7 != t1 );
        REQUIRE( t1 != t8 );
        REQUIRE( t8 != t1 );
        REQUIRE( t1 != t9 );
        REQUIRE( t9 != t1 );
    }
}


TEST_CASE( "Large values" )
{
    const size_t bigname_len = 1000001;
    string bigname(bigname_len, 'x');  // We make this into a long string

    int bigquantity = 2147483641;      // Almost greatest 32-bit signed value
    int mo = 12;

    ostringstream ostr;
    ostr << bigname << " (" << bigquantity << "), Dec";
    string bigstringform = ostr.str();
                        // String form of Delivery(bigname, bigquantity)

    SUBCASE( "Construction from large values" )
    {
        Delivery t1(bigname, bigquantity, mo);

        REQUIRE( t1.getName() == bigname );
        REQUIRE( t1.getQuantity() == bigquantity );
        REQUIRE( t1.getMonth() == mo );
        REQUIRE_FALSE( t1.empty() );

        // Check size & prefix first, to avoid enormous error messages
        REQUIRE( t1.toString().size() == bigstringform.size() );
        REQUIRE( t1.toString().substr(0,20) == bigstringform.substr(0,20) );
        REQUIRE( t1.toString() == bigstringform );
    }

    SUBCASE( "Set functions, passing large values" )
    {
        Delivery t1;
        t1.setName(bigname);
        t1.setQuantity(bigquantity);
        t1.setMonth(mo);

        REQUIRE( t1.getName() == bigname );
        REQUIRE( t1.getQuantity() == bigquantity );
        REQUIRE( t1.getMonth() == mo );
        REQUIRE_FALSE( t1.empty() );

        // Check size & prefix first, to avoid enormous error messages
        REQUIRE( t1.toString().size() == bigstringform.size() );
        REQUIRE( t1.toString().substr(0,20) == bigstringform.substr(0,20) );
        REQUIRE( t1.toString() == bigstringform );
    }
}


TEST_CASE( "Same-object tests" )
{
    SUBCASE("Copy assignment returns *this")
    {
        Delivery t1;
        Delivery t2;
        Delivery & r(t1 = t2);
        REQUIRE( &r == &t1 );
    }

    SUBCASE("Move assignment returns *this")
    {
        Delivery t1;
        Delivery t_movable;
        Delivery & r(t1 = move(t_movable));
        REQUIRE( &r == &t1 );
    }

    SUBCASE("pre-increment returns *this")
    {
        Delivery t1;
        Delivery & r(++t1);
        REQUIRE( &r == &t1 );
    }

    SUBCASE("pre-decrement returns *this")
    {
        Delivery t1;
        Delivery & r(--t1);
        REQUIRE( &r == &t1 );
    }

    SUBCASE("post-increment returns copy")
    {
        Delivery t1;
        Delivery && rr1(t1++);
        Delivery && rr2(t1++);
        REQUIRE( &rr1 != &t1 );
        REQUIRE( &rr1 != &rr2 );
    }

    SUBCASE("post-decrement returns copy")
    {
        Delivery t1;
        Delivery && rr1(t1--);
        Delivery && rr2(t1--);
        REQUIRE( &rr1 != &t1 );
        REQUIRE( &rr1 != &rr2 );
    }

    SUBCASE("getName returns copy")
    {
        Delivery t1;
        string && rr1(t1.getName());
        string && rr2(t1.getName());
        REQUIRE( &rr1 != &rr2 );
    }

    SUBCASE("getQuantity returns copy")
    {
        Delivery t1;
        int && rr1(t1.getQuantity());
        int && rr2(t1.getQuantity());
        REQUIRE( &rr1 != &rr2 );
    }

    SUBCASE("empty returns copy")
    {
        Delivery t1;
        bool && rr1(t1.empty());
        bool && rr2(t1.empty());
        REQUIRE( &rr1 != &rr2 );
    }

    SUBCASE("operator<< returns original stream")
    {
        ostringstream ostr;
        Delivery t1;
        ostream & r(ostr << t1);
        REQUIRE( &r == &ostr );
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
    cout << "Press ENTER to quit ";
    userPause();

    // Program return value is return code from doctest
    return dtresult;
}

