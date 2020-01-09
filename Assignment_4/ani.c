

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

struct Cache {
  int lineCount;  // how many lines or blocks can be stored in the cache
  int* tags;      // array of tags, 1 tag per line
  int** lines;    // data for blocks, array or arrays
} typedef Cache;

Cache * cache = NULL;

int cacheSize;
int mainMemorySize;
int blockSize;

//Method that prints header/prologue
void writePrologue() {
  printf("Programming Assignment 4: Cache Simulation\n");
  printf("Comp 222 - Fall 2019\n");
}

//Procedure to Free Allocated Memory
void freeMM(struct MainMemory* mainMemory) {
  if(mainMemory->data) {
    free(mainMemory->data);
  }
}

//Procedure to Free Allocated Cache Blocks
void freeCache() {
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

// pointer to sizes and pointer to cache to allocate
void initCache() {
  int i;
  // number of lines is the cache divided by block size
  // how many block the cache may hold
  cache->lineCount = cacheSize / blockSize;
  // allocate array of pointers to blocks
  cache->lines=malloc(cache->lineCount * sizeof(int*));
  // allocate array of tags
  cache->tags=malloc(cache->lineCount * sizeof(int));
  // allocate each block pointer
  for(i=0; i < cache->lineCount; i++) {
    cache->lines[i] = malloc(blockSize * sizeof(int));
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

/* All data valid, allocate */
void EnterSizes() {
  // Read values
  // Keep prompting and reading until scanf correcly parses 1 data piece and it is over zero
  // not clearly wrong input
  do {
    printf("\nEnter main memory size (words): ");
  } while(scanf("%d", &(mainMemorySize))!=1 || mainMemorySize <= 0);

  // same for cache size
  do {
    printf("\nEnter cache size (words): ");
  } while(scanf("%d", &(cacheSize))!=1 || cacheSize <= 0);
  // same for block size
  do {
    printf("\nEnter block size (words/block): \n");
  } while(scanf("%d", &(blockSize))!=1 || blockSize <= 0);
    
  // check if everything is the power of 2
  // Caches size must be larger than block size (we cache whole blocks)
  // Cache size should the the multiple of the block size (whole blocks)
  if(!PowerTwo(mainMemorySize)) {
    printf("*** Error - Main Memory Size is not a Power of 2\n");
    mainMemorySize = cacheSize = blockSize = -1; // reset to -1 if wrong
  }
  else if(!PowerTwo(cacheSize)) {
    printf("*** Error - Cache Size is not a Power of 2\n");
    mainMemorySize = cacheSize = blockSize = -1; // reset to -1 if wrong
  } 
  else if(!PowerTwo(blockSize)) {
    printf("*** Error - Block Size is not a Power of 2\n");
    mainMemorySize = cacheSize = blockSize = -1; // reset to -1 if wrong
  } 
  else if(blockSize > cacheSize) {
    printf("*** Error - Block size is larger than cache size\n");
    mainMemorySize = cacheSize = blockSize = -1; // reset to -1 if wrong
  } 
  /*else if(sizes->cache % sizes->block != 0) {
    printf("*** Error - Cache Size is not a multiple of Block Size\n");
    sizes->mainMemory = sizes->cache = sizes->block = -1; //reset to -1 if wrong
  }*/
}

/* Read Cache */
//Enter Address to Read
void readCache(struct MainMemory* mem) {
  int addr = -1;
  int block, tag, line, lineofs;
  if(mainMemorySize==-1) {
    return;
  }
  // first obtain the address to read
  do {
    printf("\nEnter Main Memory Address to Read: \n");
  } while(scanf("%d", &addr)!=1);
  if(addr < 0 || addr >= mainMemorySize) {
    printf("\n*** Error – Read Address Exceeds Memory Address Space\n");
    return;
  }
  // calculate the block number
  block = addr / (blockSize);
  // calculate the the address within block
  lineofs = addr % blockSize;
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
    memcpy(cache->lines[line], mem->data + block * blockSize, blockSize * sizeof(int));
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
void writeCache(struct MainMemory* mem) {
  int addr = -1;
  int block, tag, line, lineofs;
  int value;
  if(mainMemorySize == -1) {
    return;
  }
  do {
    printf("\nEnter Main Memory Address to Write: \n");
  } while(scanf("%d", &addr) != 1);
  do {
    if(addr >= 0 && addr < mainMemorySize) {
      printf("Enter Value to Write: \n");
    }
  } while(scanf("%d", &value) != 1);
  
  if(addr < 0 || addr >= mainMemorySize) {
    printf("\n*** Error – Write Address Exceeds Memory Address Space\n");
    return;
  }

  block = addr / (blockSize);
  lineofs = addr % blockSize;
  line = block % cache->lineCount;
  tag = block / cache->lineCount;
    
  if(cache->tags[line] != tag) {
    cache->tags[line] = tag;
    memcpy(cache->lines[line], mem->data + block * blockSize, blockSize * sizeof(int));
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
  mainMemorySize = -1;
  blockSize = -1;
  cacheSize = -1;
  struct MainMemory mem = {NULL};
  cache = {-1, NULL, NULL};

  int option = 0;
  writePrologue();
  // return 0;
  while(option != '4') {
    printf("\nMain Menu - Main Memory to Cache Memory Mapping\n");
    printf("------------------------------------------------\n");
    printf("1) Enter sizesuration Parameters\n");
    printf("2) Read from Cache\n");
    printf("3) Write to Cache\n");
    printf("4) Quit Program\n\n");
    printf("Enter selection: \n");

    option = -1; // reset the old option
    //prompt user until option is between '1' and '4'
    while(option == -1 || option == '\n' || option == '\r') {
      option = getchar();
    }
    switch (option) {
      case '1': {
        EnterSizes();
        if(mainMemorySize != -1) {
          int i;
          printf("\n*** All Input Parameters Accepted. Starting to Process Write/Read Requests\n");
          freeMM(&mem);
          freeCache();
          mem.data = malloc(mainMemorySize * sizeof(int));
          for(i = 0; i < mainMemorySize; i++) {
            mem.data[i] = mainMemorySize - i;
          }
          initCache();
      }
      break;
      } 
      case '2':
        if(mainMemorySize != -1) {
          readCache(&mem);
        }
        else {
          printf("\n*** Error - Invalid Menu Option Selected\n");
        }
        break;
      case '3':
        if(mainMemorySize != -1) {
          writeCache(&mem);
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
  freeCache();
  printf("\n*** Memory Freed Up - Program Terminated Normally\n");
  return 0;
}
