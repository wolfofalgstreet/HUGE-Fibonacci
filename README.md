# Fibonacci

Program avoids repetitive computation by computing the sequence linearly form the bottom up: `F(0)` through `F(n)`. This implementation also overcomes the limitations of a 32-bit integer in C, overflow is avoided by representing integers as arrays of individual digits.


# Overview

## Computational Considerations for Recursive Fibonacci

Calculating Fibonacci numbers with the most straightforward recursive
implementation of the function is prohibitively slow, as there is a lot of repetitive computation:

```c
int fib(int n) {
 // base cases: F(0) = 0, F(1) = 1
 if (n < 2)
 return n;
 // definition of Fibonacci: F(n) = F(n – 1) + F(n - 2)
 return fib(n – 1) + fib(n – 2);
}
```

This recursive function sports an exponential runtime. Instead the approach is to achieve linear runtime by building from base cases, `F(0) = 0` and `F(1) = 1`, toward the desired result, `F(n)`. Thus avoid the expensive and exponentially EXplOsIVe recursive function calls.

## Representing Huge Integers in C

The linear Fibonacci function has a big problem, though, which is perhaps less obvious than the
original runtime issue: when computing the sequence, we quickly exceed the limits of C’s 32-bit
integer representation. On most modern systems, the maximum int value in C is 232-1, or
2,147,483,647. The first Fibonacci number to exceed that limit is `F(47) = 2,971,215,073`.

Even C’s 64-bit `unsigned long long int` type is only guaranteed to represent non-negative integers
up to and including 18,446,744,073,709,551,615 (which is 264-1).The Fibonacci number `F(93) =
12,200,160,415,121,876,738` which can be stored as an `unsigned long long int`. However, `F(94) =
19,740,274,219,868,223,167` which is too big to store in any of C’s extended integer data types.

To overcome this limitation, we will represent integers in this program using arrays, where each index
holds a single digit of an integer.

For reasons that will soon become apparent, we will store our integers in reverse order in these arrays. So, for example, the numbers 2,147,483,648 and 10,0087 would be represented as:

|               | 0             | 1     | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| ------------- |:-------------:| -----:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| **[a]**       | 8             | 4     | 6 | 3 | 8 | 4 | 7 | 4 | 1 | 2 |
| **[b]**       | 7             | 8     |0  | 0 | 0 | 1 |

Storing these integers in reverse order makes it really easy to add two of them together. The ones digits
for both integers are stored at index [0] in their respective arrays, the tens digits are at index [1], the
hundreds digits are at index [2], and so on.

So, to add these two numbers together, we add the values at index [0] (8 + 7 = 15), throw down the 5 at
index [0] in some new array where we want to store the sum, carry the 1, add it to the values at index
[1] in our arrays (1 + 4 + 8 = 13), and so on

In this program, we will use this array representation for integers. The arrays will be allocated
dynamically, and we will stuff each array inside a struct that also keeps track of the array’s length:

```c
typedef struct HugeInteger
{
 // a dynamically allocated array to hold the digits
 // of a huge integer, stored in reverse order
 int *digits;
 // the number of digits in the huge integer (which is
 // approximately equal to the length of the array)
 int length;
} HugeInteger;
```

## Unsigned Integers and limits.h

`unsigned int n;`

Because an `unsigned int` is typically 32 bits (like the normal `int` data type), but doesn’t need to use
any of those bits to signify a sign, it can make out a higher maximum positive integer value than a normal
`int`.

It is necessary to know what the maximum value is that can be represented using an `unsigned int` on the system where the program is running. That value is defined in the system’s `limits.h` file, which was `#include`d from the `Fibonacci.c` source
file, like so:

`#include <limits.h>`

`limits.h` defines a value called `UINT_MAX`, which is the maximum value an unsigned `int` can hold. It
also defines `INT_MAX` (the maximum value an `int` can hold), `UINT_MIN`, `INT_MIN`, and many others.

Note that `(UINT_MAX + 1)` necessarily causes integer overflow, but since an unsigned int can’t be negative, `(UINT_MAX + 1)` just wraps back around to zero.

# Functions

### hugeDestroyer()

```c
HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q);
```
* **Description:**  Return a pointer to a new, dynamically allocated `HugeInteger struct` that contains
 the result of adding the huge integers represented by `p` and `q`.
* **Notes:**  If a `NULL` pointer is passed to this function, it simply `returns NULL`. If any dynamic
memory allocation functions fail within this function, also `returns NULL`, consideration to avoid
memory leaks when you doing so needs to be taken.
* **Returns** A pointer to the newly allocated `HugeInteger struct`, or `NULL` in the special cases
mentioned above.

---

### parseString()

```c
HugeInteger *parseString(char *str);
```

* **Description:** Convert a number from string format to `HugeInteger` format. 
* **Notes:** : If the empty string (“”) is passed to this function, treat it as a zero (“0”). If any
dynamic memory allocation functions fail within this function, or if `str` is `NULL`, `return NULL`, again trying to avoid memory leaks when doing so. It is assumed the string will only contain ASCII digits ‘0’ through ‘9’, and that there will be no leading zeros in the string.
* **Returns:** A pointer to the newly allocated `HugeInteger struct`, or `NULL` if dynamic memory
allocation fails or if `str` is `NULL`.

---

### parseInt()

```c
HugeInteger *parseInt(unsigned int n)
```

* **Description** Convert the `unsigned integer` `n` to `HugeInteger` format.
* **Notes:** If any dynamic memory allocation functions fail within this function, `return NULL`, consider avoiding memory leaks when doing so.
* **Returns** A pointer to the newly allocated `HugeInteger struct`, or `NULL` if dynamic memory
allocation fails at any point.

---

### toUnsignedInt()

```c
unsigned int *toUnsignedInt(HugeInteger *p);
```

* **Description:** Convert the `integer` represented by `p` to a dynamically allocated `unsigned int`,
and return a pointer to that value. If `p` is `NULL`, simply `return NULL`. If the integer represented by
`p` exceeds the maximum unsigned `int` value defined in `limits.h`, `return NULL`.
* **Note:** The sole reason this function returns a pointer instead of an `unsigned int` is so that we
can `return NULL` to signify failure in cases where `p` cannot be represented as an `unsigned int`.
* **Returns:**  A pointer to the dynamically allocated `unsigned integer`, or `NULL` if the value cannot
be represented as an `unsigned integer` (including the case where `p` is `NULL`).

---

### fib()

```c
HugeInteger *fib(int n);
```

* **Description** This is the Fibonacci function; this is where the magic happens. Implementation of an
iterative solution that runs in `O(nk)` time and returns a pointer to a `HugeInteger struct` that
contains `F(n)`. (See runtime note below.) Making sure to prevent memory leaks before returning from
this function.
* **Runtime Consideration:** In the `O(nk)` runtime restriction, `n` is the parameter passed to the
function, and `k` is the number of digits in `F(n)`. So, within this function, you can make a total of
`n` calls to a function that is `O(k)` *(or faster)*.
* **Space Consideration:** When computing `F(n)` for large `n`, it’s important to keep as few
Fibonacci numbers in memory as necessary at any given time. For example, in building up to
`F(10000)`, you won’t want to hold Fibonacci numbers `F(0)` through `F(9999)` in memory all at
once. Find a way to have only a few Fibonacci numbers in memory at any given time over the
course of a single call to `fib()`.
* **Notes:** You may assume that `n` is a non-negative integer. If any dynamic memory
allocation functions fail within this function, `return NULL`, noting to avoid memory leaks
when doing so.
* **Returns:** A pointer to a `HugeInteger` representing `F(n)`, or `NULL` if dynamic memory allocation
fails.


# Compilation and Testing (Linux/Mac Command Line)

To compile the source file (.c files) at the command line:
```c
gcc main.c 
```

By default, this will produce an executable file called a.out, which can run by typing:
```c
./a.out
```

If you want to name the executable file something else, use:
```c
gcc Fibonacci.c testcase01.c -o fib.exe
```

...and then run the program using:
```c
./fib.exe
```

Running the program could potentially dump a lot of output to the screen. If you want to redirect your
output to a text file in Linux, it’s easy. Just run the program using the following command, which will
create a file called `whatever.txt` that contains the output from your program:

```c
./fib.exe > whatever.txt
```








