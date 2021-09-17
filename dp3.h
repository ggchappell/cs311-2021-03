// dp3.h  SKELETON
// Glenn G. Chappell
// 2021-09-16
//
// For CS 311 Fall 2021
// Header for Project 3 functions

#ifndef FILE_DP3_H_INCLUDED
#define FILE_DP3_H_INCLUDED

#include "llnode.h"    // For LLNode
#include <cstddef>     // For std::size_t
#include <functional>  // For std::function


template <typename ValueType>
ValueType lookup(const LLNode<ValueType> * head,
                 std::size_t index)
{
    return ValueType();  // Dummy return
    // TODO: WRITE THIS!!!
}


// Implementation in source file
void didItThrow(const std::function<void()> & ff,
                bool & threw);


template <typename RAIter>
std::size_t uniqueCount(RAIter first,
                        RAIter last)
{
    return std::size_t(42);  // Dummy return
    // TODO: WRITE THIS!!!
}


// Implementation in source file
int gcd(int a,
        int b);


#endif  //#ifndef FILE_DP3_H_INCLUDED

