/*
 Comp 222 - Fall 2019
 Ani Khachatryan
 Programming Assignment 1: Performance
*/

#include <stdio.h>
#include <stdlib.h>

//initialize values
int i;
int* cpi_i;
int* count_i; //define cpi_i as a pointer to one of more integers
float cpi_sum;
int classes;
int mhz;
int instr_total;
float time;
float mips;

// procedure to read all input parameters
void enter_params() {
  //initialize counter variables
  cpi_sum=0;
  instr_total=0;

  scanf("%d", &mhz);// input frequency
  
  scanf("%d",&classes);// input number of instruction classes

  cpi_i = (int*)malloc(classes*sizeof(int)); //dynamically allocate an array 
  count_i = (int*)malloc(classes*sizeof(int));//dynamically allocate a second array

  instr_total =0;
  for (i=0; i < classes; i++) {
      scanf("%d", &cpi_i[i]);// input instruction's cpi
      scanf("%d", &count_i[i]);// input instruction's count
      instr_total += count_i[i];
      cpi_sum = cpi_sum + (cpi_i[i] * count_i[i]);
    }
  printf("\n");
  return;  
   
}

//function computes average cpi
float calc_CPI() {
  //cpi_sum = (cpi_i[i]*count_i);
  cpi_sum = cpi_sum/instr_total;
  return cpi_sum;
}


//function computes execution time
float calc_CPU_time() {
  // for(int i = 0; i < classes; i++) {
  //   time = (count_i[i]*cpi_i[i]);
  // }
  time = (cpi_sum*instr_total)/((float)mhz);
  return time;
}


//function computes mips
float calc_MIPS() {
  // for(i = 0; i < classes; i++) {
    mips = ((float)mhz*10E6)/(cpi_sum*10E6);
  // }
  return mips;
}

//procedure prints input values that were read
void print_params() {
  printf("FREQUENCY (MHz): ");
  printf("%d\n", mhz);
  printf("\nINSTRUCTION DISTRIBUTION\n");
  printf("\nCLASS\tCPI\tCOUNT\n");
  for(i = 0; i < classes; i++) {
    printf("%d\t%d\t%d\n", i+1, cpi_i[i], count_i[i]);
  }
}


//procedure prints calculated values
void print_performance() {
  printf("\nPERFORMANCE VALUES\n\n");
  printf("AVERAGE CPI %.2f", calc_CPI());
  printf("\nTIME (ms) %.2f", calc_CPU_time()*1000);
  printf("\nMIPS %.2f", calc_MIPS());
}


//main program keeps reading menu selection and dispatches accordingly
int main() {
  int input;
  do {
    scanf("%d", &input);
    if(input == 1) {
      enter_params();
    }
    if(input == 2) {
      print_params();
      print_performance();
    }
  } while(input != 3);
  printf("\n\nPROGRAM TERMINATED NORMALLY");
  free(cpi_i);
  free(count_i);
   
  return 0;
}


