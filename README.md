# Extremely Large Numbers - Large Numbers Library C

The **LNLC - Large Numbers Library C** is a simple library for handling arbitrarily large integers (big integers). It allows basic arithmetic operations such as addition, subtraction, multiplication, and division on numbers larger than standard data types can hold.

## Features

- Arbitrary-length integers (up to 1000 digits by default).
- Support for signed numbers.
- Operations include addition, subtraction, multiplication, and division.
- String-based initialization for large numbers.
- Utility functions for printing, setting, and comparing numbers.

## Getting started

Build lib:

```
make
```

Add libGGN.a with GGN_lib.h to your project and compile:

```
gcc  -o your_program your_program.c -I. ./libeln.a
```

## Example Usage - Prints all powers of two untill given power

```c
#include <stdio.h>
#include "eln.h"

int main()
{
    int max_power;

    // Ask the user for the maximum power of 2
    printf("Enter the maximum power of 2: ");
    scanf("%d", &max_power);

    // Initialize base (2) as a El number
    elNum *two = init_int_el(2);

    elNum *current_power = init_int_el(1);

    printf("2^0 = ");
    print_el(current_power);
    puts("");

    // Loop through all powers of 2 up to the max_power
    for (int i = 1; i <= max_power; i++)
    {
        // Multiply the current power by 2 to get the next power of 2
        mult_el(current_power, two, current_power);

        // Print the result
        printf("2**%d = ", i);
        print_el(current_power);
        puts("");
    }

    // Free allocated memory
    freen_el(2,two, current_power);
    return 0;
}
```

## TODO:

EFFECTIVE MULTIPLICATION
TESTS
ERROR HANDELING
