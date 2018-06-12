#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Fibonacci.h"

// print a HugeInteger (without a newline character)
void hugePrint(HugeInteger *p)
{
	int i;

	if (p == NULL || p->digits == NULL)
	{
		printf("(null pointer)");
		return;
	}

	for (i = p->length - 1; i >= 0; i--)
		printf("%d", p->digits[i]);
}

int main(void)
{
	int i;
	HugeInteger *p, *q, *r;

	// calculate INT_MAX + 1
	p = parseInt(INT_MAX);
	q = parseInt(1);
	r = hugeAdd(p, q);

	// demonstrate overflow
	printf("Overflow style:\n%d + %d = %d\n\n", INT_MAX, 1, INT_MAX + 1);

	// print result of INT_MAX + 1 with HugeIntegers
	printf("HugeInteger style:\n");
	hugePrint(p);
	printf(" + ");
	hugePrint(q);
	printf(" = ");
	hugePrint(r);
	printf("\n\n");

	// free memory
	hugeDestroyer(p);
	hugeDestroyer(q);
	hugeDestroyer(r);


	// now calculate UINT_MAX + 1
	p = parseInt(UINT_MAX);
	q = parseInt(1);
	r = hugeAdd(p, q);

	// demonstrate overflow
	printf("Overflow style:\n%u + %u = %u\n\n", UINT_MAX, 1, UINT_MAX + 1);

	// print result of UINT_MAX + 1 with HugeIntegers
	printf("HugeInteger style:\n");
	hugePrint(p);
	printf(" + ");
	hugePrint(q);
	printf(" = ");
	hugePrint(r);
	printf("\n");

	// free memory
	hugeDestroyer(p);
	hugeDestroyer(q);
	hugeDestroyer(r);


	return 0;
}
