// assertion.cpp
// Glenn G. Chappell
// 2021-08-25
// Demo of assert in C++

#include <iostream>
using std::cout;
using std::endl;
#include <cassert>
// For assert
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;


// sumTwo
// Takes a vector of ints and two indices. Returns the sum of the items
// with those indices.
int sumTwo(const vector<int> & v,
           size_t idx1,
           size_t idx2)
{
    assert(idx1 < v.size());
    assert(idx2 < v.size());
    return v[idx1] + v[idx2];
}


// Main program
// Call function sumTwo a couple of times.
int main()
{
    // Data to use for sumTwo calls
    vector<int> data { 4, 5, 9, 2, 8, 3, 11 };

    cout << "Sum #1: " << sumTwo(data, 0, 2) << endl;
    cout << "Sum #2: " << sumTwo(data, 0, 20) << endl;
}

