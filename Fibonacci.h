#ifndef __FIBONACCI_H
#define __FIBONACCI_H

typedef struct HugeInteger
{
	// a dynamically allocated array to hold the digits of a huge integer
	int *digits;

	// the number of digits in the huge integer (approx. equal to array length)
	int length;
} HugeInteger;


// Functional Prototypes

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q);

HugeInteger *hugeDestroyer(HugeInteger *p);

HugeInteger *parseString(char *str);

HugeInteger *parseInt(unsigned int n);

unsigned int *toUnsignedInt(HugeInteger *p);

HugeInteger *fib(int n);

double difficultyRating(void);

double hoursSpent(void);


#endif
