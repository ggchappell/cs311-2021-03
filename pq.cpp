// pq.cpp
// Glenn G. Chappell
// 2021-11-08
//
// For CS 311 Fall 2021
// Priority Queues & Custom Comparisons

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <queue>
using std::priority_queue;
#include <vector>
using std::vector;
#include <functional>
using std::greater;


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// pqOut
// Given a std::priority_queue whose value type is printable, removes
// items from it and prints them, in the order removed. Items are
// printed to cout, a blank after each item, with an ending newline.
// Upon return, the given priority_queue will be empty.
// Requirements on Types:
//     The value type of FDIter must have stream insertion (op<<).
// Pre:
//     [first, last) must be a valid range.
// Basic Guarantee
template<typename PQ>
void pqOut(PQ & pq)
{
    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}


// Main program
// Do several sorts using custom comparisons. Print the results.
int main()
{
    // Print a note
    cout << "*******************************************************"
         << endl;
    cout << "* This code demonstrates use of std::priority_queue.  *"
         << endl;
    cout << "* But it does not really indicate what this is FOR.   *"
         << endl;
    cout << "* We will cover an application later in the semester. *"
         << endl;
    cout << "*******************************************************"
         << endl;
    cout << endl;

    // Create master dataset
    vector<int> master { 5, 2, 9, 4, 8, 1, 7, 3, 9, 4 };

    // Print initial data
    cout << "Initial data:  ";
    for (auto n : master)
    {
        cout << n << " ";
    }
    cout << endl;
    cout << "Below, items are inserted into each Priority Queue"
         << " in the above order."
         << endl;
    cout << endl;

    // Priority Queue #1: Normal
    priority_queue<int> pqnorm;
    for (auto n : master)
    {
        pqnorm.push(n);
    }
    cout << "Priority Queue #1: Normal" << endl;
    cout << "Items in order removed:  ";
    pqOut(pqnorm);
    cout << endl;

    // Priority Queue #2: Reversed, using std::greater
    priority_queue<int, vector<int>, greater<int>> pqrev;
    for (auto n : master)
    {
        pqrev.push(n);
    }
    cout << "Priority Queue #2: Reversed, using std::greater" << endl;
    cout << "Items in order removed:  ";
    pqOut(pqrev);
    cout << endl;

    // Priority Queue #3: Custom comparison (even before odd)
    // Comparison lambda from comparison.cpp
    auto even1st =        // Comparison: even before odd
        [](int a, int b)
        {
            if (a % 2 == 0 && b % 2 != 0)
                return true;
            else if (a % 2 != 0 && b % 2 == 0)
                return false;
            else
                return a < b;
        };
    priority_queue<int, vector<int>, decltype(even1st)> pqcust(even1st);
    for (auto n : master)
    {
        pqcust.push(n);
    }
    cout << "Priority Queue #3: Custom comparison"
         << " (even before odd, from 'comparison.cpp')" << endl;
    cout << "Items in order removed:  ";
    pqOut(pqcust);
    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

