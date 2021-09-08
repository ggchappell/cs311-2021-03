// iterators.cpp
// Glenn G. Chappell
// 2021-09-07
//
// For CS 311 Fall 2021
// Iterator & STL Demo

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <iterator>
using std::begin;
using std::end;
using std::ostream_iterator;
#include <algorithm>
using std::copy;
using std::equal;
using std::sort;


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Make datasets & manipulate them with STL algorithms.
int main()
{
    // Initialize vector using initializer list
    vector<int> data { 5, 3, 2, 10, 5, 9, 8, 0, 6, 1, -4 };

    // Create new vector with same size
    vector<int> data2(data.size());

    // Copy contents of 1st vector to 2nd with std::copy
    // Note. More easily done using vector copy ctor or copy assignment
    cout << "Copying from 1st vector to 2nd using std::copy" << endl;
    copy(begin(data), end(data), begin(data2));
    cout << endl;

    // Check equality of 2 vectors using std::equal
    // Note. More easily done using vector op==
    cout << "Do vectors have the same data?" << endl;
    cout << "std::equal says: ";
    if (equal(begin(data), end(data), begin(data2), end(data2)))
    {
        cout << "YES";
    }
    else
    {
        cout << "no";
    }
    cout << endl << endl;

    // Print 1st vector using ostream_iterator & std::copy
    ostream_iterator<int> out(cout, " ");
    cout << "Vector contents (printed using ostream_iterator):" << endl;
    copy(begin(data), end(data), out);
    cout << endl << endl;

    // Sort part of 1st vector & print again
    cout << "Sorting items 3-7 in vector using std::sort" << endl;
    sort(begin(data)+3, begin(data)+7+1);
        // Specify range: iter to 1st item, iter to just past last item
    cout << endl;
    cout << "Vector contents (printed using ostream_iterator):" << endl;
    copy(begin(data), end(data), out);
    cout << endl << endl;

    // Sort all of 1st vector & print again
    cout << "Sorting entire vector using std::sort" << endl;
    sort(begin(data), end(data));
    cout << endl;
    cout << "Vector contents (printed using ostream_iterator):" << endl;
    copy(begin(data), end(data), out);
    cout << endl << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

