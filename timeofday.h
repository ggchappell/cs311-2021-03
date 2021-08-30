// timeofday.h
// Glenn G. Chappell
// Started: 2021-08-27
// Updated: 2021-08-30
//
// For CS 311 Fall 2021
// Header for class TimeOfDay
// Time of day: hours, minutes, seconds

#ifndef FILE_TIMEOFDAY_H_INCLUDED
#define FILE_TIMEOFDAY_H_INCLUDED

#include <ostream>  // For std::ostream
#include <cassert>  // For assert


// *********************************************************************
// class TimeOfDay - Class definition
// *********************************************************************


// class TimeOfDay
// Time of day: hours, minutes, seconds.
class TimeOfDay {

// ***** TimeOfDay: Friend declarations *****

    friend
    std::ostream & operator<<(std::ostream & str,
                              const TimeOfDay & obj);

// ***** TimeOfDay: Ctors, dctor, op= *****
public:

    // Default ctor
    // Set time to midnight.
    TimeOfDay()
    {
        setTime(0, 0, 0);
    }

    // Ctor from hours, minutes, seconds
    // Set time to given # of hours, minutes, seconds past midnight.
    TimeOfDay(int hh,
              int mm,
              int ss)
    {
        assert(0 <= hh && hh < 24);
        assert(0 <= mm && mm < 60);
        assert(0 <= ss && ss < 60);

        setTime(hh, mm, ss);
    }

    // We use the automatically generated destructor and copy/move
    // operations.

// ***** TimeOfDay: General public operators *****
public:

    // op++ [pre]
    // Move time one second forward.
    TimeOfDay & operator++()
    {
        assert(0 <= _secs && _secs < 24*60*60);

        ++_secs;
        if (_secs == 24*60*60)
            _secs = 0;
        return *this;
    }

    // op++ [post]
    // Move time one second forward.
    TimeOfDay operator++([[maybe_unused]] int dummy)
    {
        assert(0 <= _secs && _secs < 24*60*60);

        auto save = *this;
        ++(*this);
        return save;
    }

    // op-- [pre]
    // Move time one second backward.
    TimeOfDay & operator--()
    {
        assert(0 <= _secs && _secs < 24*60*60);

        --_secs;
        if (_secs == -1)
            _secs = 24*60*60-1;
        return *this;
    }

    // op-- [post]
    // Move time one second backward.
    TimeOfDay operator--([[maybe_unused]] int dummy)
    {
        assert(0 <= _secs && _secs < 24*60*60);

        auto save = *this;
        --(*this);
        return save;
    }

// ***** TimeOfDay: General public functions *****
public:

    // getTime
    // Return hours, minutes, seconds in reference parameters.
    // Function defined in source file.
    void getTime(int & hh,
                 int & mm,
                 int & ss) const;

    // setTime
    // Set time to given # of hours, minutes, seconds past midnight.
    // Function defined in source file.
    void setTime(int hh,
                 int mm,
                 int ss);

// ***** TimeOfDay: Data members *****
private:

    int _secs;  // Seconds past midnight (range 0 .. 24*60*60-1)

};  // End class TimeOfDay


// *********************************************************************
// class TimeOfDay - Declarations of associated global operators
// *********************************************************************


// operator<< (ostream,TimeOfDay)
// Prints given TimeOfDay object as "hh:mm:ss", with hh padded on the
// left with blanks, and mm, ss padded on the left with zeroes.
// Function defined in source file.
std::ostream & operator<<(std::ostream & str,
                          const TimeOfDay & obj);


#endif  //#ifndef FILE_TIMEOFDAY_H_INCLUDED

