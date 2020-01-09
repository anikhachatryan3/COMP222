/*
Ani Khachatryan
Comp 222 - Fall 2019
Assignment 0
*/

#include <stdio.h>

int main() {

   int x;
   int y;
   int z;
   
   printf("Please enter sets of two integers:\n\nX\tY\tZ");
   do {
      scanf("%d%d", &x, &y);
      z = x + y;
      printf("\n%d \t%d\t%d", x, y, z);
   } while(z != 0);

}