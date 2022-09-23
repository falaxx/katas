Write a method that returns the nth root of a given positive number.

Method signature

```public static double GetNthRoot(double number, int n)```

Assume following

·         number >= +1.00

·         root   >= +1

Rules:

·         You can only use 4 basic math operations + - * /

·         You cannot use any Math.* methods

# Solution

Without math library i chose a brute force approach.

First get an approximation of the Nth root with GetApprox(), in order to have more or less a number in the right size.

The approximation will always be less than the Nth root.

Then I try to increment the approximation until I reach enough precision.

The computing is relatively fast, instead of incrementing one by one the digit I first increment since I test digit+5 first, then if it's too much I iterate from 1 to 4, or 6 to 9 if it's less.

Due to floating point precision, I put a fixedPointCantCompute counter to track if the program is stuck where number+incrementation = number.

I put in the main some test case to see results, I compare the number of digits from number to the number of digit of Nthroot*root, and display the digit in common. Since double does not have perfect precision, we often get an approximation for big number or  big root.

Compile with ```g++ NthRoot.cpp -std=c++17```