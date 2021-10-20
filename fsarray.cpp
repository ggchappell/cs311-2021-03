// fsarray.cpp  UNFINISHED
// VERSION 5
// Glenn G. Chappell
// Started: 2021-10-12
// Updated: 2021-10-19
//
// For CS 311 Fall 2021
// Source for class FSArray
// Frightfully smart array of int
// Preliminary to Project 5


#include "fsarray.h"  // For class FSArray definition
#include <algorithm>
using std::copy;


// *********************************************************************
// class FSArray - Member function definitions
// *********************************************************************


// Copy ctor
// See header for info.
FSArray::FSArray(const FSArray & other)
    :_size(other.size()),
     _data(other.size() == 0 ? nullptr
                             : new value_type[other.size()])
{
    copy(other.begin(), other.end(), begin());
    // The above call to std::copy does not throw, since it copies int
    // values. But if value_type is changed, then the call may throw, in
    // which case this copy ctor may need to be rewritten.
}


// Move ctor
// See header for info.
FSArray::FSArray(FSArray && other) noexcept
    :_size(other._size),
     _data(other._data)
{
    other._size = 0;
    other._data = nullptr;
}


// Copy assignment operator
// See header for info.
FSArray & FSArray::operator=(const FSArray & other)
{
    // TODO: WRITE THIS!!!
    return *this; // DUMMY
}


// Move assignment operator
// See header for info.
FSArray & FSArray::operator=(FSArray && other) noexcept
{
    // TODO: WRITE THIS!!!
    return *this; // DUMMY
}


// resize
// See header for info.
void FSArray::resize(FSArray::size_type newsize)
{
    // TODO: WRITE THIS!!!
}


// insert
// See header for info.
FSArray::iterator FSArray::insert(FSArray::iterator pos,
                                  const FSArray::value_type & item)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}


// erase
// See header for info.
FSArray::iterator FSArray::erase(FSArray::iterator pos)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}


// swap
// See header for info.
void FSArray::swap(FSArray & other) noexcept
{
    // TODO: WRITE THIS!!!
}

