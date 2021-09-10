#!/usr/bin/env python3
# range.py
# Glenn G. Chappell
# 2021-09-10
#
# For CS 311 Fall 2021
"""Example of a range specification in Python.
Requires Python 3."""


import sys  # for .exit


# main
def main():
    """Demonstrate Python's range functionality.

    """
    print("Printing values in \"range(2, 7)\":")
    for i in range(2, 7):
        print(f"  {i}")
    print()

    print("Python follows the same first/just-past-last convention for")
    print("specifying ranges as the C++ STL.")
    print()

    return 0  # Success


# If this module is executed as a program (instead of being imported):
# Call function main and exit with its return value.
if __name__ == "__main__":
    sys.exit(main())

