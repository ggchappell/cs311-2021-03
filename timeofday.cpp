// timeofday.cpp
// Glenn G. Chappell
// Started: 2021-08-27
// Updated: 2021-08-30
//
// For CS 311 Fall 2021
// Source for class TimeOfDay
// Time of day: hours, minutes, seconds

#include "timeofday.h"
// For class TimeOfDay
#include <ostream>
using std::ostream;
#include <cassert>
// For assert


// *********************************************************************
// class TimeOfDay - Definitions of member functions
// *********************************************************************


// TimeOfDay::getTime
void TimeOfDay::getTime(int & hh,
                        int & mm,
                        int & ss) const
{
    assert(0 <= _secs && _secs < 24*60*60);

    ss = _secs % 60;
    mm = (_secs / 60) % 60;
    hh = _secs / 60 / 60;
}

// TimeOfDay::setTime
void TimeOfDay::setTime(int hh,
                        int mm,
                        int ss)
{
    assert(0 <= hh && hh < 24);
    assert(0 <= mm && mm < 60);
    assert(0 <= ss && ss < 60);

    _secs = hh*60*60 + mm*60 + ss;
}


// *********************************************************************
// class TimeOfDay - Definitions of associated global operators
// *********************************************************************


// operator<< (ostream,TimeOfDay)
ostream & operator<<(ostream & str,
                     const TimeOfDay & obj)
{
    assert(0 <= obj._secs && obj._secs < 24*60*60);

    int hh, mm, ss;
    obj.getTime(hh, mm, ss);

    if (hh < 10)  // Left-pad with blank
        str << " ";
    str << hh << ":";

    if (mm < 10)  // Left-pad with zero
        str << "0";
    str << mm << ":";

    if (ss < 10)  // Left-pad with zero
        str << "0";
    str << ss;

    return str;
}

