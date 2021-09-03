// intarray.h
// Glenn G. Chappell
// 2021-09-03
//
// For CS 311 Fall 2021
// Header for class IntArray
// Simple RAII class holding dynamic array of int.
// There is no associated source file.

#ifndef FILE_INTARRAY_H_INCLUDED
#define FILE_INTARRAY_H_INCLUDED

#include <cstddef>  // For std::size_t


// *********************************************************************
// class IntArray - Class definition
// *********************************************************************


// class IntArray
// Simple RAII class holding dynamic array of int.
// A const IntArray does not allow modification of its array items.
class IntArray {

// ***** IntArray: Types *****
public:

    using size_type = std::size_t;  // Unsigned type for size of array,
                                    //  indices
    using value_type = int;         // Type of item in this container

// ***** IntArray: Ctors, dctor, op= *****
public:

    // Ctor from size
    // Not an implicit type conversion.
    // Parameter size must be nonnegative.
    explicit IntArray(size_type size)
        :_arrayptr(new value_type[size])
    {}

    // Dctor
    ~IntArray()
    {
        delete [] _arrayptr;
    }

    // No default ctor, copy/move ops
    IntArray() = delete;
    IntArray(const IntArray & other) = delete;
    IntArray & operator=(const IntArray & other) = delete;
    IntArray(IntArray && other) = delete;
    IntArray & operator=(IntArray && other) = delete;

// ***** IntArray: General public operators *****
public:

    // op[] - non-const & const
    // Parameter index must be in the range [1, size), where size is the
    // parameter passed to the ctor.
    value_type & operator[](size_type index)
    {
        return _arrayptr[index];
    }
    const value_type & operator[](size_type index) const
    {
        return _arrayptr[index];
    }

// ***** IntArray: Data members *****
private:

    value_type * _arrayptr;  // Pointer to our dynamic array
                             //   Points to memory allocate with new [],
                             //   owned by *this, large enough to hold
                             //   *size* value-type objects, where size
                             //   is the parameter passed to the ctor.

};  // End class IntArray


#endif  //#ifndef FILE_INTARRAY_H_INCLUDED

