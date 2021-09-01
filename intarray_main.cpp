// intarray_main.cpp
// Glenn G. Chappell
// 2021-09-01
//
// For CS 311 Fall 2021
// Simple main program for class IntArray

#include "intarray.h"  // for class IntArray
#include "intarray.h"  // Double-inclusion check (for testing only)
#include <iostream>
using std::cout;
using std::endl;
using std::cin;


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Use all operations for class IntArray.
int main()
{
    // Make an IntArray of the following size
    const IntArray::size_type SIZE = 25;
    IntArray arr(SIZE);

    // Set all values in the array
    for (IntArray::size_type i = 0;
         i != SIZE;
         ++i)
    {
        arr[i] = 2*int(i)+2;
    }

    // Print all values (non-const IntArray)
    cout << "Below should be even numbers 2 .. " << 2*(SIZE-1)+2
         << "\n";
    for (IntArray::size_type i = 0;
         i != SIZE;
         ++i)
    {
        cout << arr[i] << " ";
    }
    cout << "\n\n";

    // Print all values (const IntArray)
    const IntArray & carr(arr);
    cout << "Below should be even numbers 2 .. " << 2*(SIZE-1)+2
         << " (again)" << endl;
    for (IntArray::size_type i = 0;
         i != SIZE;
         ++i)
    {
        cout << carr[i] << " ";
    }
    cout << "\n" << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

