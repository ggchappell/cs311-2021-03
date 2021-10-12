// fsarray_main.cpp
// Glenn G. Chappell
// 2021-10-12
//
// For CS 311 Fall 2021
// Check whether FSArray package compiles

#include "fsarray.h"  // For class FSArray
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <utility>
using std::move;
#include <cassert>
// For assert


// use_all_FSArray
// Use all functionality of class FSArray.
// Calls to FSArray functionality are not actually executed.
void use_all_FSArray()
{
    // Fake the compiler out. Return, but in a way that will make the
    //  compiler unsure whether we always return.
    for (int i = 0; i < 3; ++i)
    {
        if (i == 2)
            return;
    }
    assert(false);  // Do not execute past this point!

    [[maybe_unused]] int ii;  // For returned int values
    FSArray aa;               // For returned FSArray values

    // Member type size_type
    auto s = FSArray::size_type(9);

    // Member type value_type
    FSArray::value_type v;

    // Member type iterator
    FSArray::iterator it;

    // Member type const_iterator
    FSArray::const_iterator cit;

    // Default ctor
    const FSArray ca1;

    // Ctor from size
    FSArray a2(s);

    // Copy ctor
    FSArray a3(ca1);

    // Move ctor
    FSArray atmp1;
    FSArray a4(move(atmp1));

    // Dctor
    // Called when function exits after creating FSArray objects

    // Copy op=
    aa = (a2 = ca1);

    // Move op=
    FSArray atmp2;
    aa = (a3 = move(atmp2));

    // Bracket op, non-const
    a2[s] = v;
    ii = a2[s];

    // Bracket op, const
    ii = ca1[s];

    // size
    s = ca1.size();

    // empty
    if (ca1.empty()) cout << "empty";

    // begin, non-const
    it = a2.begin();
    *it = v;
    ii = *it;

    // begin, const
    cit = ca1.begin();
    ii = *cit;

    // end, non-const
    it = a2.end()-1;
    *it = v;
    ii = *it;

    // end, const
    cit = ca1.end()-1;
    ii = *cit;

    // resize
    a2.resize(s);

    // insert
    it = a2.insert(it, v);

    // erase
    it = a2.erase(it);

    // push_back
    a2.push_back(v);

    // pop_back
    a2.pop_back();

    // swap
    a2.swap(a3);
}


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Pretend to call all functions in FSArray package. Print message.
int main()
{
    // Use all functionality in FSArray package
    use_all_FSArray();

    // Inform the user what's up
    cout << "\n";
    cout << "**********************************\n";
    cout << "* FSArray package compiles. Yay! *\n";
    cout << "**********************************\n";
    cout << "\n";
    cout << "This program checks whether the FSArray package compiles."
         << " It includes\n";
    cout << "calls to all package functions, and it uses all package"
         << " member types.\n";
    cout << "However, when the program is executed, none of these"
         << " function calls are\n";
    cout << "actually made, and no FSArray objects are created.\n";
    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

