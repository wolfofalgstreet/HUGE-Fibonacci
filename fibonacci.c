//
// Created by Isaias Perez
// -----------------------
// Huge Fibonacci
// -----------------------


// Includes
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "Fibonacci.h"

// HELPER FUNCTIONS //

// print a HugeInteger (followed by a newline character)
void hugePrint(HugeInteger *p)
{
    int i;
    
    if (p == NULL || p->digits == NULL)
    {
        printf("(null pointer)\n");
        return;
    }
    
    for (i = p->length - 1; i >= 0; i--)
        printf("%d", p->digits[i]);
    printf("\n");
}

// Find which length is larger from p and q.
int isPlenLarger(HugeInteger *p, HugeInteger *q) {
    return (p->length > q->length) ? 1 : 0;
}

// Count digits
int findLength(unsigned int n) {
    int digits = 0;
    do {
        digits++;
        n /= 10;
    } while (n > 9); {
        return digits;
    }
}
// END OF HELPER FUNCTIONS //

// Add two huge structs and return the huge addition //
HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q) {
    // If arguments are valid proceed, else return null
    if (p == NULL || q == NULL) {
        return NULL;
    }
    else {
        int x, size = 0;
        HugeInteger *hugeAddition = NULL;
        hugeAddition = malloc(sizeof(HugeInteger));

        // If memory allocation didn't fail, continue allocating memory for struct->digits
        if(hugeAddition == NULL)
            return NULL;
        if(isPlenLarger(p,q) == 1)
            hugeAddition->digits = calloc(p->length + 7, sizeof(int));
        else hugeAddition->digits = calloc(q->length + 7, sizeof(int));
        
        // If allocation fails, destroy struct and reference
        if(hugeAddition->digits == NULL) {
            free(hugeAddition->digits); free(hugeAddition); hugeAddition = NULL;
            return NULL;
        }
        // Start with the largest struct
        if(isPlenLarger(p, q) == 1) {
            // from 0 to small struct length
            for(x = 0; x < q->length; x++) {
                
                // Huge addition
                hugeAddition->digits[x] = hugeAddition->digits[x] + q->digits[x] + p->digits[x];
                
                // If huge addition is greater than 9, divide by 10 and store remainder at x
                if(hugeAddition->digits[x] > 9) {
                    hugeAddition->digits[x+1] = hugeAddition->digits[x]/10;
                    // Remainder
                    hugeAddition->digits[x] = hugeAddition->digits[x]%10;
                }
        
                // If extra numbers place are created, update number's length
                if(hugeAddition->digits[p->length])
                    size++;
                size++;
            }
            
            // Repeat, from smaller struct to larger digit's length
            for(x = q->length; x < p->length; x++) {
                hugeAddition->digits[x]+= p->digits[x];
                if(hugeAddition->digits[x] > 9) {
                    hugeAddition->digits[x+1] = hugeAddition->digits[x]/10;
                    hugeAddition->digits[x] = hugeAddition->digits[x]%10;
                }
                if(hugeAddition->digits[p->length])
                    size++;
                size++;
            }
            hugeAddition->length = size;
        }
        else {
            for(x = 0; x < p->length; x++) {
                hugeAddition->digits[x] = hugeAddition->digits[x] + p->digits[x] + q->digits[x];
                if(hugeAddition->digits[x] > 9) {
                    hugeAddition->digits[x+1] = hugeAddition->digits[x]/10;
                    hugeAddition->digits[x] = hugeAddition->digits[x]%10;
                }
                if(hugeAddition->digits[q->length]) {
                    size++;
                }
                size++;
            }
            for(x = p->length; x < q->length; x++) {
                hugeAddition->digits[x]+= q->digits[x];
                if(hugeAddition->digits[x] > 9) {
                    hugeAddition->digits[x+1] = hugeAddition->digits[x]/10;
                    hugeAddition->digits[x] = hugeAddition->digits[x]%10;
                }
                if(hugeAddition->digits[q->length])
                    size++;
                size++;
            }
            hugeAddition->length = size;
        }
        return hugeAddition;
    }
}

// Free memory //
HugeInteger *hugeDestroyer(HugeInteger *p) {
    if(p != NULL) {
        // If digits exist, free them
        if (p->digits != NULL) {
            free(p->digits);
        }
        free(p); p = NULL;
        return NULL;
    } else return NULL;
}

// Convert number from string to HugeInteger format //
HugeInteger *parseString(char *str)
{
     if (str == NULL) {
     return  NULL;
     }
     
     // Get length of string
     int strLength = strlen(str);
     HugeInteger *parsedString = NULL;
     parsedString = malloc(sizeof(HugeInteger));
     
     // If not NULL, dynamically allocate memory for digits
     if (parsedString == NULL) {
     return NULL;
     }
     
     parsedString->length = strLength;
     parsedString->digits = calloc(parsedString->length, sizeof(int));
     
     // If allocation didn't fail
     if (parsedString->digits == NULL){
     return NULL;
     }
     
     int counter = 0;
     for (int i = parsedString->length - 1; i >= 0; i--) {
     parsedString->digits[counter] = str[i];
     
     // Conver to integer format
     switch (parsedString->digits[counter]) {
     case 48:
     parsedString->digits[counter] = 0;
     break;
     case 49:
     parsedString->digits[counter] = 1;
     break;
     case 50:
     parsedString->digits[counter] = 2;
     break;
     case 51:
     parsedString->digits[counter] = 3;
     break;
     case 52:
     parsedString->digits[counter] = 4;
     break;
     case 53:
     parsedString->digits[counter] = 5;
     break;
     case 54:
     parsedString->digits[counter] = 6;
     break;
     case 55:
     parsedString->digits[counter] = 7;
     break;
     case 56:
     parsedString->digits[counter] = 8;
     break;
     case 57:
     parsedString->digits[counter] = 9;
     break;
     default:
     parsedString->digits[counter] = 0;
     break;
     }
     counter++;
     
     }
     // Lastly check if we have a valid parsedString or NULL and return
     return (parsedString == NULL) ? NULL : parsedString;
     
}

// Convert the unsigned integer n to HugeInteger format //
HugeInteger *parseInt(unsigned int n)
{
    int i = 0;
    
    HugeInteger *parsedInt;
    parsedInt = malloc(sizeof(HugeInteger));
    
    if (parsedInt == NULL)
        return NULL;
    
    else if (n < 10)
        parsedInt->length = findLength(n);
    
    else
        parsedInt->length = (findLength(n) + 1);
    
    parsedInt->digits = calloc(parsedInt->length + 1, sizeof(int));
    // If memory allocation failed, destroy struct and reference
    if (parsedInt->digits == NULL) {
        free(parsedInt); parsedInt = NULL;
        return NULL;
    }
    // Assign digits to struct
    for (i = 0; i < parsedInt->length; i++)
    {
        parsedInt->digits[i] = n % 10;
        n /= 10;
    }
    
    return parsedInt;
}

//Converts p from HugeInteger to unsigned int and returns its pointer //
unsigned int *toUnsignedInt(HugeInteger *p)
{
    // Structs for each integer type
    HugeInteger *integerHuge = parseInt(INT_MAX);
    HugeInteger *uIntHuge = parseInt(UINT_MAX);
    
    int x = 0; int y; int z = 0; int power = 1;
    int unsignedArray[uIntHuge->length];
    
    unsigned int temp = UINT_MAX;
    unsigned int *unsignedInt = malloc(sizeof(unsigned int));
    if (unsignedInt == NULL)
        return NULL;
    
    *unsignedInt = 0;
    
    if (p == NULL || p->length > integerHuge->length || p->length > uIntHuge->length)
        return NULL;
    if(p->length == uIntHuge->length) {

        while (x < uIntHuge->length) {
            unsignedArray[x] = temp % 10;
            temp /= 10;
            x++;
        }
        
        // Check if array is beyond UINT_MAX
        for (y = p->length-1 ; y >= 0; y--) {
            if (p->digits[y] < unsignedArray[y])
                break;
            
            if (p->digits[y] > unsignedArray[y])
                return NULL;
        }
    }

    while (z < p->length) {
        *unsignedInt += (p->digits[z] * power );
        power *= 10;
        z++;
    }
    
    return unsignedInt;
}

// Compute Fib sequence //
HugeInteger *fib(int n) {
    HugeInteger *x = NULL, *y = NULL, *z = NULL, *result = NULL;
    int j, m = 0, count = -1;
    //initialize structs
    x = parseInt(1); y = parseInt(2); z = parseInt(3);
    
    if(n == 0)
        return parseInt(0);
    else if(n == 1 || n == 2)
        return parseInt(1);
    
    for(j = 0; j < n; j++) {
        // Fib base cases
        if(j == 0 || j == 1 || j == 2) {
            count++;
            continue;
        }
        // Fib sequence addition
        
        // If remainder is 0
        if(j%3 == 0) {
            
            if (m == 0) {
                hugeDestroyer(z);
            }

            z = hugeAdd(y,x);
            hugeDestroyer(x);
            count++;
        }
        // If remainder is 1
        if(j%3 == 1) {
            
            if (m == 0) {
                hugeDestroyer(x);
            }
    
            x=hugeAdd(z,y);
            hugeDestroyer(y);
            count++;
        }
        
        // If remainder is 2
        if(j%3 == 2) {
            
            if (m == 0) {
                hugeDestroyer(y);
            }
            
            y = hugeAdd(x,z);
            hugeDestroyer(z);
            count++;
        }
        m = 1;
    }
    
    if(count%3 == 0) {
        result = z;
    } else if (count%3 == 1) {
        result = x;
    } else if(count%3 == 2) {
        result = y;
    }
    return result;
}

int main(void) {
    
    int i, f;
    HugeInteger *p;
    printf("\n\nEnter the number fibs you wish to calculate: ");
    scanf("%d", &f);    

    for (i = 0; i <= f; i++)
    {
        printf("F(%d) = ", i);
        hugePrint(p = fib(i));
        hugeDestroyer(p);
    }
    
    return 0;
}

