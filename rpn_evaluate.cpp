// rpn_evaluate.cpp
// Glenn G. Chappell
// 2021-10-27
//
// For CS 311 Fall 2021
// Reverse Polish Notation expression evaluation
// Example application of a Stack

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <sstream>
using std::istringstream;
#include <string>
using std::string;
using std::getline;
#include <stack>
using std::stack;
#include <cctype>
using std::isdigit;
using std::isspace;
#include <utility>
using std::pair;
#include <stdexcept>
using std::domain_error;
using std::out_of_range;
using std::overflow_error;
#include <cstdlib>
using std::atoi;


// isInteger
// Given a string, returns true if it represents an integer, that is, if
// it consists of one or more ASCII digits preceded by an optional sign
// ('+', '-').
// No-Throw Guarantee
bool isInteger(const string & str) noexcept
{
    if (str.empty())
        return false;
    char c = str.front();
    if (!isdigit(c) && c != '+' && c != '-')
        return false;

    for (size_t i = 1; i < str.size(); ++i)
    {
        if (!isdigit(str[i]))
            return false;
    }

    // Now either we have an integer, or we have "+" or "-"
    return isdigit(str.back());
}


// isBinop
// Given a string, returns true if it consists of a single arithmetic
// binary-operation character ('+', '-', '*', '/').
// No-Throw Guarantee
bool isBinop(const string & str) noexcept
{
    if (str.size() != 1)
        return false;
    char c = str.front();
    return c == '+' || c == '-' || c == '*' || c == '/';
}


// rpn
// Reverse-Polish Notation computation.
// Given a string and a stack<int>, interpret the string as a command,
// and use it to operate on the stack.
//   c, C: clear stack.
//   <integer>: push value on stack.
//   +, -, *, /: binary arithmetic operator.
//     Operands taken from top 2 stack items; stack underflow throws.
//     "/" is integer division; x/0 throws.
//     Result is left in top item on stack.
//   Unknown command: throws.
// May throw std::bad_alloc on out-of-memory, std::domain_error on
// unknown command, std::out_of_range on stack underflow, and
// std::overflow_error on division by zero.
// Basic Guarantee
void rpn(const string & token,
         stack<int> & s)
{
    if (token == "c" || token == "C")
    {
        stack<int>().swap(s);  // Clear stack
        return;
    }

    if (isInteger(token))
    {
        s.push(atoi(token.c_str()));
        return;
    }

    if (!isBinop(token))
    {
        throw domain_error("Unknown command: \"" + token + "\"");
    }

    // We have a binary arithmetic operator: +, -, *, /

    if (s.size() < 2)
    {
        throw out_of_range("Stack underflow in \"" + token
                         + "\" operation");
    }

    int b = s.top();
    s.pop();
    int a = s.top();
    s.pop();

    if (token == "+")
        s.push(a + b);
    else if (token == "-")
        s.push(a - b);
    else if (token == "*")
        s.push(a * b);
    else  // token == "/"
    {
        if (b == 0)
            throw overflow_error("Division by zero");
        else
            s.push(a / b);
    }
}


// readNonEmptyLine
// Print prompt and attempt to read a line from cin. If the line is
// empty, or it consists entirely of space characters, then try again.
// Returns { false, "" } on input error EOF; otherwise returns
// { true, line }.
// May throw std::bad_alloc on out of memory.
// Basic Guarantee
pair<bool, string> readNonemptyLine(const string & prompt)
{
    string line;  // Holds input line
    while (true)
    {
        // Input a line
        cout << prompt;
        cout.flush();
        getline(cin, line);

        // Check result
        if (!cin)
            return { false, "" };
        for (char c : line)
        {
            if (!isspace(c))
                return { true, line };
        }

        // Here, we have no error on cin, and our line consists entirely
        // of zero or more space characters. We try again.
    }
}


// Main program
// Repeatedly inputs space-separated token from standard input,
// operates on Stack (RPN operations) and prints top of Stack.
// May throw std::bad_alloc on out of memory.
int main()
{
    const string prompt = "Commands (q to quit): ";
    const string quitmsg = "*** Quitting";
    stack<int> s;

    while (true)
    {
        cout << endl;

        // Get line from stdin
        auto [valid, line] = readNonemptyLine(prompt);
        cout << "\n";

        // Quit on input error
        if (!valid)
        {
            cout << "\n" << quitmsg << "\n\n";
            return 0;
        }

        // Get space-deliminted commands from line
        istringstream lineStream(line);
        string token;
        while (lineStream >> token)  // Get space-deliminated command
                                     //  ("token") from line
        {
            // Quit?
            if (token == "q" || token == "Q")
            {
                cout << quitmsg << "\n" << endl;
                return 0;
            }

            // Do RPN processing
            try
            {
                rpn(token, s);
            }
            catch (domain_error & e)
            {
                cout << "*** ERROR - " << e.what() << "\n";
            }
            catch (out_of_range & e)
            {
                cout << "*** ERROR - " << e.what() << "\n";
            }
            catch (overflow_error & e)
            {
                cout << "*** ERROR - " << e.what() << "\n";
            }
            // std::bad_alloc exceptions will escape this function

            // Print top of stack
            if (s.empty())
                cout << "<Empty stack>\n";
            else
                cout << "Top of stack: " << s.top() << "\n";
        }
    }
}

