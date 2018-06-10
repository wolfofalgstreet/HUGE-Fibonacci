//
//  Isaias Perez
//

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "Fibonacci.h"

///////////////////////
///HELPER FUNCTIUONS///
///////////////////////

// Reuturn the largest length variable //
int findMax(HugeInteger *p, HugeInteger *q) {
    //return (p->length > q->length) ? (p->length) : (q->length);
    if (p->length == q->length) {
        return p->length;
    } else if (p->length > q->length) {
        return p->length;
    } else {
        return q->length;
    }
}

// Return the number of digits //
int getLength(unsigned int n) {
    int digits = 0;
    while (n > 9) {
        n /= 10; digits++;
    }
    return (digits + 1);
}
// test_copy //
int getLength2(unsigned int n) {
    int digits = 0;
    do {
        n /= 10;    digits++;
    } while (n > 9);
    return digits;
}

//////////////////////////////
///END OF HELPER FUNCTIUONS///
//////////////////////////////

//////////////////////////////
/////TEST CASE FUNCTIONS//////
//////////////////////////////

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

//////////////////////////////
//END OF TEST CASE FUNCTIONS//
//////////////////////////////


// Return a HugeInteger struct pointer from the addition of p and q //
HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q) {
    
    // Check that arguments are non-null
    if (p == NULL || q == NULL) {
        return NULL;
    } else {
        // Create HugeInteger
        HugeInteger *hugeAddition = NULL;
        hugeAddition = malloc(sizeof(HugeInteger));
        if (hugeAddition != NULL) {
            hugeAddition->length = findMax(p, q);
        }
        // If hugeAddition is NULL, return NULL, else return hugeAddition
        return (hugeAddition == NULL) ? NULL : hugeAddition;
    }
}
// NEEDS WORK //
// Destroy the HugeInteger //
HugeInteger *hugeDestroyer(HugeInteger *p) {
    /*if (p != NULL)
        if(p->digits == NULL) {
            free(p);    p = NULL;
        }
        if (p->digits != NULL) {
            free(p->digits);    free(p);    p = NULL;
        }
     */
    /*
    if (p == NULL) {
        return NULL;
    }
    if (p->length != NULL) {
        free(p->length);
    }
    if (p->digits != NULL) {
        for (int i = 0; i < p->length; i++) {
            free(p->digits[i]);
        }
        free(p->digits);
    }
    free(p);    p = NULL;
    */
    if (p) {
        p->digits;
        free(p);
        return NULL;
    }
    else
        return NULL;
}

// Convert string to HugeInteger format //
HugeInteger *parseString(char *str) {
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

// NEEDS WORK //
// Convert unsigned int n to HugeInteger format //
HugeInteger *parseInt(unsigned int n) {
    
    HugeInteger *parsedInt = NULL;
    parsedInt = malloc(sizeof(HugeInteger));
    if (parsedInt == NULL)
        return NULL;
    
    if(n > UINT_MAX) {
        return NULL;
    } else if ( n < 10) {
        //parsedInt->length = getLength(n);
        int x;
        x = (unsigned int) 0;
        parsedInt->digits = &x;
    } else {
        //parsedInt->length = (getLength(n) + 1); //? n > 10
        for (int i = parsedInt->length - 1; i >= 0; i--) {
            n /= 10;
            parsedInt->digits[i] = n;
        }
    }

    return (parsedInt == NULL) ? NULL : parsedInt;
}

//..
unsigned int *toUnsignedInt(HugeInteger *p) {
    if (p == NULL) {
        return NULL;
    }   //PAR = int to be converted
    if (p->length > UINT16_MAX) {
        return  NULL;
    }
    //assign HugeIneger p to unsigned int n
    unsigned int *n = NULL;
    n = malloc(sizeof(unsigned int));
    //..
    return n;
}

int main(void) {
    
    //unsigned int n = 123456789;
    
    //printf("n has %d digits\n", getLength(n));
    HugeInteger *p;
    
    hugePrint(p = parseString("12345"));
    hugeDestroyer(p);
    
    hugePrint(p = parseString("354913546879519843519843548943513179"));
    hugeDestroyer(p);
    
    hugePrint(p = parseString(NULL));
    hugeDestroyer(p);
    
    hugePrint(p = parseInt(246810));
    hugeDestroyer(p);
    
    hugePrint(p = parseInt(0));
    hugeDestroyer(p);
    
    hugePrint(p = parseInt(INT_MAX));
    hugeDestroyer(p);
    
    hugePrint(p = parseInt(UINT_MAX));
    hugeDestroyer(p);


    return 0;
}
