// binsearch2.cpp
// Glenn G. Chappell
// 2021-09-15
//
// For CS 311 Fall 2021
// Binary Search
// Implementation #2: recursive (improved)

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <utility>
using std::pair;
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <string>
using std::string;
using std::to_string;
#include <iterator>
using std::begin;
using std::end;
using std::distance;
using std::advance;
#include <cassert>
// For assert


// binSearch
// Does Binary Search on a range specified with iterators. Returns true
// if findme was found (using equivalence) in range, false otherwise.
// Recursive.
// Requirements on types:
//     FDIter is a forward iterator type.
//     ValueType is the value type of FDIter.
//     ValueType has a public operator<.
//     operator< is a total order on ValueType.
// Pre:
//     [first, last) is a valid range.
//     Values in the range are sorted by < (ascending).
// Throws what & when a ValueType operation (op<) throws. If no
// ValueType operation throws, then binSearch does not throw.
template <typename FDIter, typename ValueType>
bool binSearch(FDIter first,      // [first, last) is range to search
               FDIter last,
               const ValueType & findme)
                                  // value to find
{
    auto size = distance(first, last);  // Size of range

    // BASE CASE

    if (size <= 1)
    {
        if (size == 0)
            return false;
        return !(*first < findme) && !(findme < *first);
            // Check equivalence
    }

    // RECURSIVE CASE

    // Get iterator to pivot: item in middle position of range
    auto pivotiter = first;
    advance(pivotiter, size/2);

    if (findme < *pivotiter)
    {   // Recursively search first half of range
        return binSearch(first, pivotiter, findme);
    }
    else
    {   // Recursively search second half of range
        return binSearch(pivotiter, last, findme);
    }
}


// tryBinSearch
// Try a search using function binSearch with the given data & key.
// Print result.
// Pre:
//     Values in data are sorted by < (ascending).
//     expect is true if key is equivalent to an item in data, false
//      otherwise.
// Throws what & when binSearch throws. If binSearch does not throw,
// then tryBinSearch does not throw.
void tryBinSearch(const vector<int> & data,  // Data to search in
                  int key,                   // Key to search for
                  bool expect)               // Expected result
{
    // Do search
    cout << "Doing Binary Search for: " << key;
    cout.flush();

    bool success = binSearch(begin(data), end(data), key);

    // Print result
    cout << " - result: " << (success ? "found" : "not found");
    if (success == expect)
    {
        cout << " [correct]";
    }
    else
    {
        cout << " [INCORRECT] ****************************************";
    }
    cout << endl;
}


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// intWithSep
// Return string form of given integer with a separator (default: ",")
// every 3 digits.
// intWithSep(-123456789) returns "-123,456,789"s.
// intWithSep(1234567, ".") returns "1.234.567"s.
// Requirements on Types:
//     IntType must be an integer type.
template <typename IntType>
string intWithSep(IntType num,               // Integer to stringify
                  const string & sep = ",")  // Separator
{
    const auto SPACING = 3;  // How many digits between separators
    auto result = to_string(num);
    auto pos = result.size();
    while (pos > SPACING + (num < 0))
    {
        pos -= SPACING;
        result.insert(pos, sep);
    }
    return result;
}


// Main program
// Do several searches using binSearch. Print results.
int main()
{
    // Size of dataset - CHANGE THIS! - MUST BE GREATER THAN 100
    const size_t SIZE = 200'000'000;

    assert(SIZE > 100);

    // Initialize data to search
    cout << "Initializing data, SIZE = "
         << intWithSep(SIZE)
         << " ... ";
    cout.flush();

    vector<int> data;
    data.reserve(SIZE);
    for (size_t i = 0; i < SIZE; ++i)
        data.push_back(10*int(i));

    cout << "DONE" << "\n";
    cout << endl;

    // List of searches to do
    const vector<pair<int, bool>> searchfor {
        { 10,            true },  // search key, expect success?
        { 1000,          true },
        { (SIZE/10)*10,  true },
        { (SIZE/2)*10,   true },
        { (SIZE-1)*10,   true },
        { -1,            false },
        { 11,            false },
        { (SIZE/2)*10+1, false },
        { (SIZE*10),     false }
    };

    // Do Binary Search calls
    for (const auto & p : searchfor)
    {
        tryBinSearch(data, p.first, p.second);
    }
    cout << endl;

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

