/*
Ani Khachatryan
Comp 222 - Fall 2019
Programming Assignment 2: Conversion
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*************************/
void convertToIEEE() {
    /* declare local variables */
    int exp = 0;
    int sign;
    unsigned int ieee;
    int expVar; 
    float decVar;
    float dec;
    int i;
    unsigned mantVar;

    /* prompt for floating point decimal number */ 
    printf("\nEnter the decimal representation: ");
    scanf("%f", &dec);
    /* Check for 0--if so, print result */
    if (dec == 0) {
        printf("\n");
        printf("*** Sign: 0\n");
        printf("*** Biased Exponent: 00000000\n");
        printf("*** Mantissa: 00000000000000000000000\n");
        printf("***The IEEE-754 representation is: 0.000000\n");
    }
    else {
        if (dec <= 0) {
            sign = 1;
            printf("\n*** Sign: 1\n");
        }
        else {
            sign = 0;
            printf("\n*** Sign: 0\n");
        }
        
        /* take absolute value of number before generating significand */ 
        if(dec < 0) {
          dec = 0 - dec;
        }


        /* Normalize number:
        while number >=2, divide by 2, increment exponent
        while number <1, multiply by 2, decrement exponent
        */
        decVar = dec;
        while(decVar >= 2) {
            decVar = decVar/2;
            exp++;
        }
        while(decVar < 1) {
            decVar = decVar*2;
            exp--;
        }

        /* Bias exponent by 127 and print each bit in binary with 8-iteration for-loop*/
        exp = exp + 127;
        expVar = exp;
        printf("*** Biased Exponent: ");
        i = 0;
        while(i < 8) {
            if (expVar <= 127) {
                expVar = expVar * 2;
                printf("0");
            }
            else {
                expVar = expVar - 128;
                printf("1");
            }
            i++;
        }
        printf("\n");

        /* Hide 1 and print significand in binary with 23-iteration for-loop*/
        printf("*** Mantissa: ");
        mantVar = 0;
        decVar = decVar - 1;
        i = 0;
        while(i < 23) {
           mantVar <<= 1;
            if(decVar < 0.5) {
                printf("0");
            }
            else {
                printf("1");
                decVar = decVar - 0.5;
                mantVar |= 1;
            }
            decVar = decVar * 2;
            i++;
        }
        printf("\n");

        /* Print IEEE-754 representation */
        ieee = (((unsigned int)sign) << 31)|(((unsigned int)exp) << 23)|mantVar;
        printf("*** IEEE HEX: %x\n", ieee);
    } 
    printf("\n");
    return;
}

/***********************************************************************/
void convertToDecimal() {
    /* declare local variables */
    float mant;
    int sign;
    int ieee;
    float dec;
    int exp;

    /* prompt for IEEE-754 representation */
    printf("\n");
    printf("Enter the IEEE-754 representation: ");
    scanf("%x", &ieee);

    /* Mask sign from number: if sign=0, print "+", else print "-" */
    if(ieee < 0x80000000) {
        sign = 1;
        printf("\n*** Sign: +\n");
    }
    else {
        sign = -1;
        printf("\n*** Sign: -\n");
    }

    /* check for special cases: 0, -0, +infinity, -infinity, NaN, 
    if so, print and return */ 
    if(ieee == 0x80000000) {
        //-0
        printf("*** Special Case: -0\n");
    }
    else if(ieee == 0) {
        //+0
        printf("*** Special Case: +0\n");
    }
    else if(ieee == 0xFF800000) {
        //-infinity
        printf("Special Case: -infinity\n");
    }
    else if(ieee == 0x7F800000) {
        //+infinity
        printf("Special Case: +infinity\n");
    }
    else if((ieee & 0x7FFFFFFF) > (0x7F800000)) {
        //NaN
        printf("*** Special Case: NaN\n");
    }
    else {
        /* Mask biased exponent and significand from number */

        /* If biased exponent=0, number is denormalized with unbiased exponent of -126, 
	    print denormalized number as fraction * 2^(-126), return */
        exp = ((ieee & 0x7FFFFFFF) >> 23);
        mant = ((ieee << 9) * pow(2, -32));
        if(exp != 0) {	
            /* Unbias exponent by subtracting 127 and print */
            exp = exp - 127;
            printf("*** Unbiased exponent: %d\n", exp);
            /* Add hidden 1 and print normalized decimal number */
            if((mant + 1) < 1) {
               printf("*** Normalized decimal: %f\n", (mant + 2));
               dec = (sign *(mant + 2)) * pow(2, exp);
               /* Print decimal number */
               printf("*** Decimal: %f\n", dec);
            }
            else {
               printf("*** Normalized decimal: %f\n", (mant + 1));
               dec = (sign *(mant + 1)) * pow(2, exp);
               /* Print decimal number */
               printf("*** Decimal: %f\n", dec);
            }
        }
        else {
            printf("*** Unbiased exponent: -126 \nDenormalized Decimal: %f*(2^(-126))\n", mant);
        }

    }
    printf("\n");
    return;  
}

void quitProgram() {
	printf("\n*** Program Terminated Normally");
	return;
}

int main() {
    /* declare local variables */
    int option = 1;

    /* until user chooses to quit, prompt for choice and select appropriate function */
    while(option > 0 && option < 3) {
        printf("Floating-point conversion:\n\n");
        printf("1) Decimal to IEEE-754 conversion\n");
        printf("2) IEEE-754 to Decimal conversion\n");
        printf("3) Exit\n\n");
        printf("Enter Selection:");
        scanf("%d", &option);
        printf("\n");
        if(option == 1) {
            convertToIEEE();
        }
        else if(option == 2) {
            convertToDecimal();
        }
        else if(option == 3) {
            quitProgram();
            break;
        }
        else {
            printf("Invalid input. Please try again.");
        }
    }
    return 0;
}
