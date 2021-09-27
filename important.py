#!/usr/bin/env python3
# important.py
# Glenn G. Chappell
# 2021-09-27
#
# For CS 311 Fall 2021
"""Print the sum from Analysis of Algorithms
Illustrates the most important part of a formula
Requires Python 3."""

import math  # for .log


def print_results(n):
    """Given an integer n, print the terms in the sum from the Analysis
    of Algorithms slides, along with the sum itself, each on a separate
    line, rounded to the nearest integer.

    """
    # Terms in sum
    a = round(n * math.log(n, 10))
    b = 72 * n
    c = 3 * n**2
    d = 936

    # The sum itself
    total = a+b+c+d

    # Print all values
    print(f"n log_10(n) {a}")
    print(f"72 n        {b}")
    print(f"3 n^2       {c}")
    print(f"936         {d}")
    print(f"SUM         {total}")


# Main program
# If this module is executed as a program (instead of being imported):
# input n, print numbers in nice format, repeat until blank line input.
if __name__ == "__main__":
    while True:
        print()
        print("Given n, I print the values of the terms in the sum")
        print("from the Analysis of Algorithms slides, along with the")
        print("sum itself. Values are rounded to the nearest integer.")
        print()
        try:
            line = input("Type n [blank line to exit]: ")
            if line == "": break
            n = int(line)
            if n < 0: raise Exception()
        except:
            print()
            print("Please type a nonnegative integer")
        else:
            print()
            print_results(n)
        print()
        print("-" * 60)
    print()

