#ifndef BASIC_MATH_H
#define BASIC_MATH_H

// Initializes the Fibonacci sequence with the first two numbers.
extern void fibonacciInit(unsigned long long a, unsigned long long b);

// Generates the next Fibonacci number in the sequence.
extern bool fibonacciNext();

// Returns the current Fibonacci number in the sequence.
extern unsigned long long fibonacciCurrent();

// Returns the current index in the Fibonacci sequence.
extern unsigned fibonacciIndex();

// Math class for basic arithmetic operations.
class Math
{
public:
    Math();

    static double add(double a, double b);
    static double subtract(double a, double b);
    static double multiply(double a, double b);
    static double divide(double a, double b);
};

#endif // !BASIC_MATH_H
