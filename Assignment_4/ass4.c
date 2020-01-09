/*
Ani Khachatryan
Programming Assignment 4: Cache Simulation
Comp 222 – Fall 2019
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//node struct
struct node {
  int tag;
  int *block;
}*cache = NULL;

typedef struct node line;
//main memory
int *main_mem = NULL;
int mem_size, cache_size, block_size;
int set, sa;

//method checks if input is power of 2
bool PowerTwo(int input) {
  bool result = true;
  if(input == 0) {
    return false;
  }
  if(input == 1) {
    return true;
  }
  while(input > 1) {
    if(input%2 != 0) {
      result = false;
    }
    input = input/2;
  }
  return result;
}

//method checks for any errors
int check() {
	if(!PowerTwo(mem_size)){
	   //main mem size is not power of 2
		printf("\n*** Error - Main Memory Size is not a Power of 2\n");
		return 1;
	}
	else if(!PowerTwo(block_size)) {
	   //block size is not power of 2
	   printf("\n*** Error - Block Size is not a Power of 2\n");
		return 1; 
	}
	else if(!PowerTwo(cache_size)){
	   //cache size is not power of 2
		printf("\n*** Error - Cache Size is not a Power of 2\n");
		return 1;
	}
	else if(block_size>cache_size){
	   //block size is larger than cache size
		printf("\n*** Error - Block size is larger than cache size\n\n");
		return 1;
	}
	//no errors. print params accepted
	printf("\n*** All Input Parameters Accepted. Starting to Process Write/Read Requests\n");
	return 0;

}

//user gives parameters
void set_params() {
	int i;
	int temp = 1;
   	if(temp!=0){
      	printf("\nEnter main memory size (words): ");
      	//prompt for main mem size
      	scanf("%d", &mem_size);
      	printf("\nEnter cache size (words): ");
      	//prompt for cache size
      	scanf("%d", &cache_size);
      	printf("\nEnter block size (words/block): \n");
      	//prompt for block size
      	scanf("%d", &block_size);
      	temp = check();	
      }
	   sa=1; 

     //allocate space for main mem
     main_mem = (int *) malloc(mem_size * sizeof(int));  
     for (i=0; i < mem_size; i++)
       main_mem[i] = mem_size - i;

     //allocate space for cache
     set = cache_size / block_size;
     cache = (line *) malloc(set * sizeof(line));
     for (i=0; i < set; i++)
       cache[i].block = NULL;
     return;
}

//method for reading address in memory
void read_addr() {
   int mmaddr=0;
   int tag, set, word, base;
   int index;
   printf("\nEnter main memory address to read: ");
   //prompt for read address
   scanf("%d", &mmaddr);
   if(mmaddr > mem_size) {
      //read address bigger than main mem size
     printf("\n*** Error – Read Address Exceeds Memory Address Space\n");
     return;
   }
  
   //calculating tag, word, cache line (set)
   tag = mmaddr / (cache_size / sa);
   set = (mmaddr % (cache_size / sa)) / block_size;
   word = mmaddr % block_size;
   base = mmaddr / block_size;

   if (cache[set].block == NULL) {
      //read miss. not in cache
      printf("\n*** Read Miss - First Load Block from Memory\n");
      cache[set].tag = tag;
      cache[set].block=(int*)malloc(block_size * sizeof(int));
      for (index=0; index < block_size; index++)
	     cache[set].block[index] = main_mem[base*block_size+index];
   }  
   else if (cache[set].tag == tag){ 
      //in cache
		printf("\n*** Cache Hit\n");
	}
   else {
      //read miss. not in cache
      printf("\n*** Read Miss - First Load Block from Memory\n");
      cache[set].tag = tag;
      for (index=0; index < block_size; index++)
	     cache[set].block[index] = main_mem[base*block_size+index];
   }
   //print word, cache line, tag, and value
   printf("*** Word %d of cache line %d with tag %d contains the value %d\n", word,set,tag,cache[set].block[word]);
   return;
}

//method for writing address in memory
void write_addr() {
  int mmaddr, tag, set, word, data, index, base;
  printf("\nEnter main memory address to write: ");
  //prompt for write address
  scanf("%d", &mmaddr);
  if(mmaddr > mem_size) {
      //write address bigger than main mem size
      printf("\n*** Error – Write Address Exceeds Memory Address Space\n");
      //ignore value
      scanf("%d", &data);
      data = 0;
      return;
  }
  printf("Enter value to write: ");
  //prompt for value to write
  scanf("%d", &data);

  //calculating tag, word, cache line (set)
  tag = mmaddr / (cache_size / sa);
  set = (mmaddr % (cache_size / sa)) / block_size;
  word = mmaddr % block_size;
  base = mmaddr / block_size;

  
  if (cache[set].block == NULL) {
      //write miss. not in cache
      printf("\n*** Write Miss - First Load Block from Memory\n");
      cache[set].tag = tag;
      cache[set].block =  (int *) malloc(block_size * sizeof(int));
      for (index=0; index < block_size; index++)
	     cache[set].block[index] = main_mem[base*block_size+index];
        cache[set].block[word] = data;
        main_mem[mmaddr] = data; 
   }  
   else if (cache[set].tag == tag) {
      //in cache
		printf("\n*** Cache Hit\n");
      cache[set].block[word] = data;
      main_mem[mmaddr] = data;
   }
  else {
     //write miss. not in cache
      printf("\n*** Write Miss - First Load Block from Memory\n");
      cache[set].tag = tag;
      
      for (index=0; index < block_size; index++)
	     cache[set].block[index] = main_mem[base*block_size+index];
        cache[set].block[word] = data;
      main_mem[mmaddr] = data;
    }
  //print word, cache line, tag, and value
  printf("*** Word %d of cache line %d with tag %d contains the value %d\n", word,set,tag,cache[set].block[word]);      
  return;
}

//method for freeing memory
void delete_cache() {
  int i;
   //freeing cache
   for (i=0; i < set; i++)
     if (cache[i].block != NULL)
     free(cache[i].block); 
   free(cache);
   
   //freeing main mem
   if (main_mem!=NULL)
     free(main_mem);
     //memory has been freed
   printf("\n*** Memory Freed Up - Program Terminated Normally\n");
   return;
}


int main() {
  int option = 0;
  //used to check if first option selected is 1 or 4
  bool first = false;
  //prints prologue
  printf("Programming Assignment 4: Cache Simulation\n");
  printf("Comp 222 - Fall 2019\n");
  while (option != 4) { 
     //prints main menu header
     printf("\nMain Menu - Main Memory to Cache Memory Mapping\n");
     printf("------------------------------------------------\n");
     printf("1) Enter Configuration Parameters\n");
     printf("2) Read from Cache\n");
     printf("3) Write to Cache\n");
     printf("4) Quit Program\n\n");
     printf("Enter selection:\n");
     //prompt user for option
     scanf("%d", &option);
     //if option is not 1,2,3, or 4
     if(option < 1 || option > 4) {
         //invalid menu option
         printf("\n*** Error - Invalid Menu Option Selected\n");
     }
      else {
         switch(option) {
            //if option = 1
      	   case 1:
      	      //first option is 1 or 4 (true)
         	   first = true;
         	   //go to enter params method
         	   set_params(); 
         		break;
	         case 2:
	            //if first option is 2 (not 1 or 4 so false)
            	if(first == false) {
            	   //bad option selected
            	   printf("\n*** Error - Invalid Menu Option Selected\n");
            	}
            	else {
            	   //go to read address method
            	   read_addr();
            	}
   			   break;
   	      case 3: 
   	         //if first option is 3 (not 1 or 4 so false)
   	         if(first == false) {
   	            //bad option selected
   	            printf("\n*** Error - Invalid Menu Option Selected \n");
   	         }
            	else {
            	   //go to write address method
   	            write_addr(); 
   	         }
			      break;
         	case 4: 
         	   //first option is 1 or 4 (true)
            	first = true;
            	//go to delete cache mem method
            	delete_cache(); 
         		break;
	     }
      }
   }
  return 0;
}