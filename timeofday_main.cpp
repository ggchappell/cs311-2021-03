// timeofday_main.cpp
// Glenn G. Chappell
// 2021-08-26
//
// For CS 311 Fall 2021
// Simple main program for class TimeOfDay

#include "timeofday.h"  // For class TimeOfDay
#include "timeofday.h"  // Double-inclusion check (for testing only)

#include <iostream>
using std::cout;
using std::cin;


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Calls a number of member & associated global functions for class
// TimeOfDay. Prints expected and actual results.
int main()
{
    cout << "Simple main program for class TimeOfDay" << "\n";
    cout << "Each line below shows what should result, "
         << "and then what actually results." << "\n";
    cout << "This is NOT a thorough test program." << "\n";
    cout << "\n";

    const TimeOfDay t1;
    TimeOfDay t2(23, 59, 59);

    cout << "\" 0:00:00\"   - \"" << t1 << "\"" << "\n";

    ++t2;
    t2++;
    cout << "\" 0:00:01\"   - \"" << t2 << "\"" << "\n";

    --t2;
    t2--;
    cout << "\"23:59:59\"   - \"" << t2 << "\"" << "\n";

    int h, m, s;

    t1.getTime(h, m, s);
    cout << "\"(0,0,0)\"    - \"(" << h << "," << m << "," << s << ")\""
         << "\n";

    t2.getTime(h, m, s);
    cout << "\"(23,59,59)\" - \"(" << h << "," << m << "," << s << ")\""
         << "\n";

    t2.setTime(8,03,59);
    ++t2;
    cout << "\" 8:04:00\"   - \"" << t2 << "\"" << "\n";

    cout << "\n";

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

