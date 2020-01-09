// /*
// Ani Khachatryan
// Programming Assignment 4: Cache Simulation
// Comp 222 – Fall 2019
// */

// #include <stdio.h>
// #include <stdlib.h>
// // #include <string.h>
// #include <stdbool.h>

// //Declare Variables
// int i;
// int mmSize = 0;
// int *mm;
// int blockSize = 0;
// int cacheSize = 0;

// //Define Structures
// struct node {
//     int tag;
//     int* block;
// } *cache = NULL;

// typedef struct node n;

// /* allocate space for MM and initialize */
// void allocMM() {
//   mm = (int*)malloc(mmSize * sizeof(int));
//   for(i = 0; i < mmSize; i++) {
//     mm[i] = mmSize - 1;
//   }
// }

// /* allocate space for cache and initialize */
// void allocCache() {
//   cache = (n*)malloc(blockSize * sizeof(n));
//   for(i = 0; i < cacheSize; i++){
//     cache[i].block = NULL;
//   }
// }

// //Procedure to Print Prologue
// void writePrologue() {
//   printf("Programming Assignment 4: Cache Simulation\n");
//   printf("Comp 222 - Fall 2019\n");
// }

// //Procedure to Print Menu
// void printMenuHeader() {
//   printf("\nMain Menu - Main Memory to Cache Memory Mapping\n");
//   printf("------------------------------------------------\n");
//   printf("1) Enter Configuration Parameters\n");
//   printf("2) Read from Cache\n");
//   printf("3) Write to Cache\n");
//   printf("4) Quit Program\n\n");
//   printf("Enter selection:\n");
// }

// //Procedure to Free Allocated Memory
// //  void freeMainMemory(struct MainMemory* mainMemory) {
// //  if(mainMemory->data) {
// //     free(mainMemory->data);
// //  }
// //  free(mm);
// // }

// //Procedure to Free Allocated Cache Blocks
// void freeCacheBlock() {
//   // for(i = 0; i <= sizeof(cache.block); i++) {
//   //   free(cache.block);
//   // }
//   free(cache);
// }

// //Procedure to Check for Power of 2
// bool PowerTwo(int input) {
//   bool result = true;
//   if(input == 0) {
//     return false;
//   }
//   if(input == 1) {
//     return true;
//   }
//   while(input > 1) {
//     if(input%2 != 0) {
//       result = false;
//     }
//     input = input/2;
//   }
//   return result;
// }

// //Procedure to Enter the Parameters Needed
// void enterParam() {
//   printf("\nEnter main memory size (words):\n");
//   scanf("%d", &mmSize);
//   printf("%d\n", mmSize);
//   printf("\nEnter cache size (words):\n");
//   scanf("%d", &cacheSize);
//   printf("%d\n", cacheSize);
//   printf("\nEnter block size (words/block):\n");
//   scanf("%d", &blockSize);
//   printf("%d\n", blockSize);
//   /* Not power of 2, error and return */
//   if(PowerTwo(mmSize) == false) {
//     printf("\n*** Error - Main Memory Size is not a Power of 2\n");
//     return;
//   }
//   /* Not power of 2, error and return */
//   else if(PowerTwo(blockSize) == false) {
//     printf("\n*** Error - Block Size is not a Power of 2\n");
//     return;
//   }
//   /* Not power of 2, error and return */
//   else if(PowerTwo(cacheSize) == false) {
//     printf("\n*** Error - Cache Size is not a Power of 2\n");
//     return;
//   }
//   /* Block size too big, error and return */
//   else if(blockSize > cacheSize) {
//     printf("\n*** Error - Block size is larger than cache size\n");
//     return;
//   }
//   /* All data valid, allocate */
//   else {
//     printf("\n*** All Input Parameters Accepted. Starting to Process Read/Write Requests\n");
//   }
//   return;
// }

// //Procedure to Read From Cache
// void cacheRead() {
//   int address = 0;
//   printf("\nEnter Main Memory Address to Read:\n");
//   scanf("%d", &address);
//   printf("%d\n", address);

//    return;
// }

// //Procedure to Write to Cache
// void cacheWrite() {
//   int value = 0;
//   int memAddress = 0;
//   printf("\nEnter Main Memory Address to Write:\n");
//   scanf("%d\n", &memAddress);
//   printf("%d\n", memAddress);
//   printf("\nEnter Value to Write:\n");
//   scanf("%d", &value);
//   printf("%d\n", value);

//   return;
// }

//   /* Read main memory size (words) */

//   /* Attempt to read cache size (words) */

//   /* Attempt to read block size (words / block) */



//   /* Check for Power of 2 */
// void PowerTwo() {
//   printf("*** Error – Read Address Exceeds Memory Address Space");
  
//   printf("*** Error – Write Address Exceeds Memory Address Space");

//   return;
// }
// /* Read Cache */
//    //Enter Address to Read

// /* Write Cache */
//    //Enter Address to Write
//    //Enter Data to Write
   
// /* Check for Collisions, etc. */

// /* Other Procedures to Process Data */


// /* Quit Program Method */
// void quitProgram() {
//   /* freeing/emptying cache */
//   freeCacheBlock();
//   printf("\n*** Memory Freed Up - Program Terminated Normally\n");
//   return;
// }

// /* Main Program */
// int main() {
//   int option = 1;
//   writePrologue();
//   while(option != 4) {
//     //print menu
//     printMenuHeader();
//     scanf("%d", &option);
//     if((option < 1) || (option > 4)) {
//       printf("\n*** Error - Invalid Menu Option Selected\n");
//     }
//     else {
//       switch(option) {
//         //if option = 1
//         case 1:
//           //enter configuration parameters
//           enterParam();
//           break;
//         //if option = 2
//         case 2:
//           //read the cache
//           cacheRead();
//           break;
//         //if option = 3
//         case 3:
//           //write to the cache
//           cacheWrite();
//           break;
//         //if option = 4
//         case 4:
//           //quit the program
//           quitProgram();
//           break;
//       }
//     }
//   }
//   return 1;
// }



/*
Ani Khachatryan
Programming Assignment 4: Cache Simulation
Comp 222 – Fall 2019
*/

//Declare Variables
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Define Structures
struct MainMemory {
  int* data;
};
struct Params {
  int mmSize;
  int cacheSize;
  int blockSize;
};

struct Cache {
  int lineCount;  // how many lines or blocks can be stored in the cache
  int* tags;      // array of tags, 1 tag per line
  int** lines;    // data for blocks, array or arrays
};


//Method that prints header/prologue
void writePrologue() {
  printf("Programming Assignment 4: Cache Simulation\n");
  printf("Comp 222 - Fall 2019\n");
}

//Method that prints the menu
void printMenuHeader() {
  printf("\nMain Menu - Main Memory to Cache Memory Mapping\n");
  printf("------------------------------------------------\n");
  printf("1) Enter Configuration Parameters\n");
  printf("2) Read from Cache\n");
  printf("3) Write to Cache\n");
  printf("4) Quit Program\n\n");
}

//Procedure to Free Allocated Memory
void freeMM(struct MainMemory* mainMemory) {
  if(mainMemory->data) {
    free(mainMemory->data);
  }
}

//Procedure to Free Allocated Cache Blocks
void freeCache(struct Cache *cache) {
  int i;
  if(cache->lines) {
    // walk through every cache line and free it
    for(i=0; i<cache->lineCount; i++) {
      if(cache->lines[i]) {
        free(cache->lines[i]);
      }
    }
    // free line pointers
    free(cache->lines);
  }
  // free tag array
  if(cache->tags) {
    free(cache->tags);
  }  
}
// pointer to config and pointer to cache to allocate
void initCache(struct Params *config, struct Cache *cache) {
  int i;
  // number of lines is the cacheSize divided by block size
  // how many block the cache may hold
  cache->lineCount = config->cacheSize / config->blockSize;
  // allocate array of pointers to blocks
  cache->lines=malloc(cache->lineCount * sizeof(int*));
  // allocate array of tags
  cache->tags=malloc(cache->lineCount * sizeof(int));
  // allocate each block pointer
  for(i=0; i < cache->lineCount; i++) {
    cache->lines[i] = calloc(config->blockSize, sizeof(int));
    cache->tags[i] = -1; // set each tag as invalid
  }
}

//Procedure to Check for Power of 2
//
// int PowerTwo(int x) {
//   return x > 0 && (x & (x - 1)) == 0;
// }
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

/* Read main memory size (words) */

/* Attempt to read cache size (words) */

/* Attempt to read block size (words / block) */



/* Check for Power of 2 */

/* Not power of 2, error and return */

/* Block size too big, error and return */

/* All data valid, allocate */
void EnterParam(struct Params *config) {
  // Read values
  // Keep prompting and reading until scanf correcly parses 1 data piece and it is over zero
  // not clearly wrong input
  do {
    printf("\nEnter main memory size (words): ");
  } while(scanf("%d", &(config->mmSize))!=1 || config->mmSize <= 0);

  // same for cache size
  do {
    printf("\nEnter cache size (words): ");
  } while(scanf("%d", &(config->cacheSize))!=1 || config->cacheSize <= 0);
  // same for block size
  do {
    printf("\nEnter block size (words/block): \n");
  } while(scanf("%d", &(config->blockSize))!=1 || config->blockSize <= 0);
    
  // check if everything is the power of 2
  // Caches size must be larger than block size (we cache whole blocks)
  // Cache size should the the multiple of the block size (whole blocks)
  if(!PowerTwo(config->mmSize)) {
    printf("*** Error - Main Memory Size is not a Power of 2\n");
    config->mmSize = config->cacheSize = config->blockSize = -1; // reset to -1 if wrong
  }
  else if(!PowerTwo(config->cacheSize)) {
    printf("*** Error - Cache Size is not a Power of 2\n");
    config->mmSize = config->cacheSize = config->blockSize = -1; // reset to -1 if wrong
  } 
  else if(!PowerTwo(config->blockSize)) {
    printf("*** Error - Block Size is not a Power of 2\n");
    config->mmSize = config->cacheSize = config->blockSize = -1; // reset to -1 if wrong
  } 
  else if(config->blockSize > config->cacheSize) {
    printf("*** Error - Block size is larger than cache size\n");
    config->mmSize = config->cacheSize = config->blockSize = -1; // reset to -1 if wrong
  } 
  /*else if(config->cacheSize % config->blockSize != 0) {
    printf("*** Error - Cache Size is not a multiple of Block Size\n");
    config->mmSize = config->cacheSize = config->blockSize = -1; //reset to -1 if wrong
  }*/
}

/* Read Cache */
//Enter Address to Read
void readCache(struct Params* config, struct MainMemory* mem, struct Cache* cache) {
  int addr = -1;
  int block, tag, line, lineofs;
  if(config->mmSize==-1) {
    return;
  }
  // first obtain the address to read
  do {
    printf("\nEnter Main Memory Address to Read: \n");
  } while(scanf("%d", &addr)!=1);
  if(addr < 0 || addr >= config->mmSize) {
    printf("\n*** Error – Read Address Exceeds Memory Address Space\n");
    return;
  }
  // calculate the block number
  block = addr / (config->blockSize);
  // calculate the the address within block
  lineofs = addr % config->blockSize;
  // calculate line number block number remainder of division to how many blocks per cache
  // 4 blocks per cache (Example)
  // 0(mem block) -> 0(cache line). 1(mem block) -> 1(cache line)
  // 2(mem block) -> 2(cache line), 3(mem block) -> 3(cache line)
  // 4(mem block) -> 0(cache line), 5(mem block) -> 1(cache line)
  line = block % cache->lineCount;
  // tag is the remaining portion of the block number
  // 0(mem block) -> 0(tag). 1(mem block) -> 0(tag)
  // 2(mem block) -> 0(tag), 3(mem block) -> 0(tag)
  // 4(mem block) -> 1(tag), 5(mem block) -> 1(tag)
  // tag and cache line -> make up the block number
  // tag * lineCount + lineNo
  tag = block / cache->lineCount;
  // does the tag match that stored in cache
  if(cache->tags[line] != tag) {
    // no, need to update the tag
    cache->tags[line] = tag;
    // and load the line
    memcpy(cache->lines[line], mem->data + block * config->blockSize, config->blockSize * sizeof(int));
    printf("\n*** Read Miss - First Load Block from Memory\n");
  }
  else {
    // yes, the block is already in cache
    printf("\n*** Cache Hit\n");
  }
  printf("\n*** Word %d of Cache Line %d with Tag %d contains the Value %d\n", lineofs, line, tag, cache->lines[line][lineofs]);
}

/* Write Cache */
//Enter Address to Write
//Enter Data to Write
void writeCache(struct Params* config, struct MainMemory* mem, struct Cache* cache) {
  int addr = -1;
  int block, tag, line, lineofs;
  int value;
  if(config->mmSize == -1) {
    return;
  }
  do {
    printf("\nEnter Main Memory Address to Write: \n");
  } while(scanf("%d", &addr) != 1);
  do {
    if(addr >= 0 && addr < config->mmSize) {
      printf("Enter Value to Write: \n");
    }
  } while(scanf("%d", &value) != 1);
  
  if(addr < 0 || addr >= config->mmSize) {
    printf("\n*** Error – Write Address Exceeds Memory Address Space\n");
    return;
  }

  block = addr / (config->blockSize);
  lineofs = addr % config->blockSize;
  line = block % cache->lineCount;
  tag = block / cache->lineCount;
    
  if(cache->tags[line] != tag) {
    cache->tags[line] = tag;
    memcpy(cache->lines[line], mem->data + block * config->blockSize, config->blockSize * sizeof(int));
    printf("\n*** Write Miss - First Load Block from Memory\n");
  }
  else {
    printf("\n*** Cache Hit\n");
  }
  // write through, write data to both, memory and cache
  cache->lines[line][lineofs] = mem->data[addr] = value;
  printf("\n*** Word %d of Cache Line %d with Tag %d contains the Value %d\n", lineofs, line, tag, cache->lines[line][lineofs]);
}

/* Check for Collisions, etc. */

/* Other Procedures to Process Data */

/* Main Program */
int main() {
  struct Params config = {-1, -1, -1};
  struct MainMemory mem = {NULL};
  struct Cache cache = {-1, NULL, NULL};

  int option = 0;
  writePrologue();
  // return 0;
  while(option != '4') {
    printMenuHeader();
    printf("Enter selection: \n");
    option = -1; // reset the old option
    //prompt user until option is between '1' and '4'
    while(option == -1 || option == '\n' || option == '\r') {
      option = getchar();
    }
    switch (option) {
      case '1': {
        EnterParam(&config);
        if(config.mmSize != -1) {
          int i;
          printf("\n*** All Input Parameters Accepted. Starting to Process Write/Read Requests\n");
          freeMM(&mem);
          freeCache(&cache);
          mem.data = malloc(config.mmSize * sizeof(int));
          for(i = 0; i < config.mmSize; i++) {
            mem.data[i] = config.mmSize - i;
          }
          initCache(&config, &cache);
      }
      break;
      } 
      case '2':
        if(config.mmSize != -1) {
          readCache(&config, &mem, &cache);
        }
        else {
          printf("\n*** Error - Invalid Menu Option Selected\n");
        }
        break;
      case '3':
        if(config.mmSize != -1) {
          writeCache(&config, &mem, &cache);
        }
        else {
          printf("\n*** Error - Invalid Menu Option Selected\n");
        }
        break;
      case '4':
        break;
      default:
        printf("\n*** Error - Invalid Menu Option Selected\n");
        break;
    }
  }
  freeMM(&mem);
  freeCache(&cache);
  printf("\n*** Memory Freed Up - Program Terminated Normally\n");
  return 0;
}
