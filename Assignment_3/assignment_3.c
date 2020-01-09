/*
Ani Khachatryan
Comp 222 - Fall 2019
Programming Assignment 3 - Pipelining
*/

#include <stdio.h>
#include <stdlib.h>

/* Declare global variables */
int instr;
// int overlap;
int cycles = 0;
 
/* Define structure for instruction containing fields for destination register, 
2 source registers, and individual instruction delay and a variable as pointer to 
structure for creating a dynamic array of instructions*/
typedef struct instr_struct {
    /* registers: */
    int destReg;
    int sourceReg1;
    int sourceReg2;
    /* delay: */
    int delay;
    /* array to store instructions in: */
    char instrArr[8];
} instructions;
instructions *instr1;

/**************************************************************/

/* method prints the pipeline chart */
void printChart() {
    /* Declare local variables */
    int i; 
    int j;
    int k;
    int count = 0;
    
    /* for however many instructions there are: */
    for(i = 1; i <= instr; i++) {
        /* if there is 1 instruction */
        if(i == 1) {
            /* there are 5 cycles */
            cycles = 5;
        }
        /* if the delay = 2 */
        if(instr1[i].delay == 2) {
            /* increment cycles and counter by 2 */
            cycles = cycles + 2;
            count = count + 2;
        }
        /* if the delay = 1 */
        else if(instr1[i].delay == 1) {
            /* increment cycles and counter by 1 */
            count  = count + 1;
            cycles = cycles + 1;
        }
        /* if there are more than 1 instructions */
        if(i > 1) {
            /* increment cycles by 1 for each instruction */
            cycles = cycles + 1;
        }
       
        /* print when each instruction is fetched */
        printf("\n\nInstruction %d is fetched at Cycle %d", i, (cycles-4));
        /* print number corresponding to instruction number */
        printf("\n%d)", i);
       
        /* for counter: */
        for(k = 1; k <= count; k++) {
            /* print as many tabs needed based on counter */
            printf("\t");
        }
        for(j = 1; j < i; j++) {
            /* prints the amount of tabs needed */
            printf("\t");
        }
        /* this is the chart */
        printf("IF\tID\tEX\tMM\tWB");
    }
    
    /* give some space */
    printf("\n\n");
    return;
}
    
/**************************************************************/

void enterInstr() {
    /* Declare local variables */
    int i;
    
    /* Prompt for total number of instructions */
    printf("\nEnter number of instructions: ");
    scanf("%d", &instr);

    /* Allocate memory to hold a set of instructions based on total number of 
    instructions+1 (instruction 0 used for dependency checking)*/
    instr1 = (instructions*)malloc((instr+1)*sizeof(instructions));
    
    /* Initialize instruction 0's destination register to -1 to prevent false 
    RAW dependency w/ instruction 2 */
    instr1[0].destReg = -1;

    /* for however many instructions there are: */
    for(i = 1; i <= instr; i++) {
        /* print number for corresponding instruction */
        printf("\n%d) ", i);
        
        /* scan/prompt for user's input (instruction) */
        scanf("%s", instr1[i].instrArr);
        
        /* print the user's input (instruction) */
        printf("%s", instr1[i].instrArr);
        
        /* get numeric value of each register number: destination, source 1, and source 2 */
        instr1[i].destReg = instr1[i].instrArr[1]-'0';
        instr1[i].sourceReg1 = instr1[i].instrArr[4]-'0';
        instr1[i].sourceReg2 = instr1[i].instrArr[7]-'0';
    }
    
    /* give some space */
    printf("\n\n");
    return;
}
    
/***************************************************************/

/* method calculates when instructions are fetched */
void calcCycle() {
    /* Declare local variables */
    int i;
   //  overlap = 0;
    // cycles = 5;
    // instr1[1].delay = 0;
    
    /* begin for-loop */
    /* For each instruction i from 2 to total number of instructions: */
    for(i = 2; i <= instr; i++) {
        /* initialize delay = 0 */
        instr1[i].delay = 0;
        
        /* Calculate individual delay for current instruction: */
        /* check for dependency between instruction (i-2) and i */
        if(((instr1[i].sourceReg1 == instr1[i-2].destReg) || (instr1[i].sourceReg2 == instr1[i-2].destReg))
        && instr1[i-1].delay != 2) {
            /* delay=1 if instruction i depends on instruction (i-2) */
            instr1[i].delay = 1;
            
        }
        
        /* check for dependency between instruction (i-1) and i */
        else if((instr1[i].sourceReg1 == instr1[i-1].destReg) || (instr1[i].sourceReg2 == instr1[i-1].destReg)) {
            /* delay=2 if instruction i depends on instruction (i-1) */
            instr1[i].delay = 2;
        }
        
        /* if none of the above: */
        else {
            /* no overlap of dependencies delay=0 */
            instr1[i].delay = 0;
        }
    }
    
    /* for however many instructions there are: */
    for(i = 1; i <= instr; i++) {
        /* if there's 1 instruction*/
        if(i == 1) {
            /* 5 cycles total/default */
            cycles = 5;
        }
        /* if delay = 2 */
        if(instr1[i].delay == 2) {
            /* add 2 to current amount of cycles */
            cycles = cycles + 2;
        }
        /* if delay = 1 */
        else if(instr1[i].delay == 1) {
            /* add 1 to current amount of cycles */
            cycles = cycles + 1;
        }
        /* if there are more than 1 instructions */
        if(i > 1) {
            /* add 1 to current amount of cycles for each instruction */
            cycles = cycles + 1;
        }
    }
    /* end for-loop */

    /* print the total amount of cycles */
    printf("\nTotal number of cycles: %d", cycles);
    /* print the chart */
    printChart();

    return;
}

/* method prints the statement "Program Terminated Normally" */
void quitProgram() {
    printf("\nProgram Terminated Normally\n");
    /* freeing space in instr1 */
    free(instr1);
    return;
}
        
/***************************************************************/
        
/***************************************************************/
        
int main() {
    /* Declare local variables */
    int option;

    /* Until user quits: */
    while(option != 3) {
        /* print menu */
        printf("Pipelined instruction performance\n\n");
        printf("1) Enter instructions\n2) Determine when instructions are fetched\n3) Exit\n");
        printf("\nEnter selection:");
        /* prompt for user input */
        scanf("%d", &option);
        /* select corresponding function: */
        switch(option) {
            /* if user chooses option 1 */
            case 1:
                /* go to enter instructions method */
                enterInstr();
                break;
            /* if user chooses option 2 */
            case 2:
                /* determine when each instruction is fetched */
                calcCycle();
                break;
            /* if user chooses option 3 */
            case 3:
                /* quit the program */
                quitProgram();
                break;
        }
    }
    
    return 1;
}
