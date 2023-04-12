#include <utility>
#include <climits>

#include "basic_math.h"

static unsigned long long previous;
static unsigned long long current;
static unsigned index;

// Initializes the Fibonacci sequence with the first two numbers.
void fibonacciInit(unsigned long long a, unsigned long long b)
{
    index = 0;
    current = a;
    previous = b;
}

// Generates the next Fibonacci number in the sequence.
bool fibonacciNext()
{
    if ((ULLONG_MAX - previous < current) || (UINT_MAX == index))
    {
        return false;
    }

    if (index > 0)
    {
        previous += current;
    }

    std::swap(current, previous);
    ++index;

    return true;
}

// Returns the current Fibonacci number in the sequence.
unsigned long long fibonacciCurrent()
{
    return current;
}

// Returns the current index in the Fibonacci sequence.
unsigned fibonacciIndex()
{
    return index;
}

// Default constructor.
Math::Math() = default;

// Adds two numbers and returns the result.
double Math::add(double a, double b)
{
    return a + b;
}

// Subtracts two numbers and returns the result.
double Math::subtract(double a, double b)
{
    return a - b;
}

// Multiplies two numbers and returns the result.
double Math::multiply(double a, double b)
{
    return a * b;
}

// Divides two numbers and returns the result.
double Math::divide(double a, double b)
{
    return a / b;
}
