// comparison.cpp
// Glenn G. Chappell
// 2021-10-06
//
// For CS 311 Fall 2021
// Passing comparisons to STL sorts

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <algorithm>
using std::sort;
#include <iterator>
using std::begin;
using std::end;
#include <functional>
using std::greater;


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// printItems
// Given a container cc, print all container items to cout, separated by
// blanks. No ending newline is printed.
// Requirements on Types:
//     For cont of type Container, begin(cont) and end(cont) must be
//      valid expressions returning forward iterators.
//     The value type of Container must have stream insertion (op<<).
// Pre:
//     [begin(c), end(c)) must be a valid range.
template<typename Container>
void printItems(const Container & cc)
{
    bool first = true;  // First item we're printing?
    for (const auto & x : cc)
    {
        if (first)
            first = false;
        else
            cout << " ";
        cout << x;
    }
}


// Main program
// Use STL sorting algorithms to sort a std::vector and a std::lst in
// various ways, passing comparisons to some of sorting calls. Print the
// results.
int main()
{
    // Create master dataset
    auto master = { 5, 2, 9, 4, 8, 1, 7, 3, 9, 4 };
    // The above has type std::initializer_list<int>. If you need the
    // declaration of this template, include header <initializer_list>.

    // ***************************
    // * Dataset #1: std::vector *
    // ***************************

    // Set up dataset #1
    vector<int> data1(master);
    cout << "***** Sorting a std::vector with std::sort\n\n";

    // Print unsorted data
    cout << "Initial data:  ";
    printItems(data1);
    cout << "\n";

    // Sort in standard order
    sort(begin(data1), end(data1));
    cout << "Normal sort:   ";
    printItems(data1);
    cout << "\n";

    // Sort in reverse order
    sort(begin(data1), end(data1), greater<int>());
    cout << "Reverse sort:  ";
    printItems(data1);
    cout << "   uses std::greater\n";

    // Sort in custom order (even before odd)
    sort(begin(data1), end(data1),
         [](int a, int b)  // Even before odd
         {
             if (a % 2 == 0 && b % 2 != 0)
                 return true;
             else if (a % 2 != 0 && b % 2 == 0)
                 return false;
             else
                 return a < b;
         }
    );
    cout << "Custom order:  ";
    printItems(data1);
    cout << "   even before odd, uses lambda\n";

    cout << endl;

    // *************************
    // * Dataset #2: std::list *
    // *************************

    // Set up dataset #2
    list<int> data2(begin(master), end(master));
    cout << "***** Sorting a std::list with member function sort\n\n";

    // Print unsorted data
    cout << "Initial data:  ";
    printItems(data2);
    cout << "\n";

    // Sort in standard order
    data2.sort();
    cout << "Normal sort:   ";
    printItems(data2);
    cout << "\n";

    // Sort in reverse order
    data2.sort(greater<int>());
    cout << "Reverse sort:  ";
    printItems(data2);
    cout << "   uses std::greater\n";

    // Sort in custom order (multiples of 3 first)
    auto divisible = [](int n, int k) { return n % k == 0; };
    auto div3 = [&](int n) { return divisible(n, 3); };
    auto comp3 = [&](int a, int b)
        {
            if (div3(a) && !div3(b))
                return true;
            else if (!div3(a) && div3(b))
                return false;
            else
                return a < b;
        };
    data2.sort(comp3);
    cout << "Custom order:  ";
    printItems(data2);
    cout << "   multiples of 3 first, uses lambda\n";

    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

