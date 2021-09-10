// allocate2_raii.cpp
// Glenn G. Chappell
// 2021-09-10
//
// For CS 311 Fall 2021
// Out-of-memory handling using exceptions, with RAII classes

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
#include <new>
using std::bad_alloc;
#include <memory>
using std::unique_ptr;
using std::make_unique;


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// class Named
// Given name on construction. Prints name, along with "created" on
// construction. Prints name, along with "DESTROYED" on destruction.
// Invariants: None.
class Named {

// ***** Named: ctors, dctor, op= *****
public:

    // Ctor from string
    // Store given string as my name. Print my name, then
    // " allocated\n", to cout.
    Named(const string & name)
        :_name(name)
    {
        // UNCOMMENT ONE OR MORE LINES BELOW TO SEE WHAT HAPPENS IF
        // ALLOCATION FAILS.

        //if (_name == "Object A") throw std::bad_alloc();
        //if (_name == "Object B") throw std::bad_alloc();

        // **********************************************************
        // * In practice, we NEVER do throws like those above;"new" *
        // * does them. These are fake throws, to see what would    *
        // * happen if "new" did actually throw.                    *
        // **********************************************************

        cout << _name << " created" << endl;
    }

    // Dctor
    // Print my name, then " deallocated\n", to cout.
    ~Named()
    {
        cout << _name << " DESTROYED" << endl;
    }

    // No other Big Five functions
    Named(const Named & other) = delete;
    Named(Named && other) = delete;
    Named & operator=(const Named & rhs) = delete;
    Named & operator=(Named && rhs) = delete;

// ***** Named: data members *****
private:

    string _name;  // Object's name; print on destruction

};


// allocate2
// Attempt to allocate two Named objects, with named "Object A" and
// "Object B". Return unique_ptrs to these in nptra, nptrb. Throws
// std::bad_alloc if either allocation is unsuccessful.
// Pre: None.
// Post:
//     nptra points to object with name "Object A".
//     nptrb points to object with name "Object B".
// May throw std::bad_alloc.
void allocate2(unique_ptr<Named> & nptra,
               unique_ptr<Named> & nptrb)
{
    nptra = make_unique<Named>("Object A");
    nptrb = make_unique<Named>("Object B");
}


// Main program
// Demonstrates calling allocate1, allocate2, with proper catching.
int main()
{
    // Call allocate2
    unique_ptr<Named> npa;
    unique_ptr<Named> npb;
    try
    {
        allocate2(npa, npb);
        cout << "Call to \"allocate2\" successful" << endl;
    }
    catch (std::bad_alloc & e)
    {
        cout << "Call to \"allocate2\" NOT successful" << endl;
    }
    cout << endl;

    // Deallocation is automatic; nothing more to do
    // (Isn't RAII great?)

    // Wait for user
    cout << "Press ENTER to quit ";
    userPause();
}

