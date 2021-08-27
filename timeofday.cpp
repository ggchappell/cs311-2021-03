// timeofday.cpp  UNFINISHED
// Glenn G. Chappell
// 2021-08-27
//
// For CS 311 Fall 2021
// Source for class TimeOfDay
// Time of day: hours, minutes, seconds

#include "timeofday.h"
// For class TimeOfDay
#include <ostream>
using std::ostream;


// *********************************************************************
// class TimeOfDay - Definitions of member functions
// *********************************************************************


// TimeOfDay::getTime
void TimeOfDay::getTime(int & hh,
                        int & mm,
                        int & ss) const
{
    ss = _secs % 60;
    mm = (_secs / 60) % 60;
    hh = _secs / 60 / 60;
}

// TimeOfDay::setTime
void TimeOfDay::setTime(int hh,
                        int mm,
                        int ss)
{
    _secs = hh*60*60 + mm*60 + ss;
}


// *********************************************************************
// class TimeOfDay - Definitions of associated global operators
// *********************************************************************


// operator<< (ostream,TimeOfDay)
ostream & operator<<(ostream & str,
                     const TimeOfDay & obj)
{
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

