/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size = 64 bytes
    cache size = 4096 bytes
    associativity =
mystery1:
    block size = 8 bytes
    cache size = 8192 bytes
    associativity =
mystery2:
    block size = 32 bytes
    cache size = 32768 bytes
    associativity =
mystery3:
    block size = 16 bytes
    cache size = 4096 bytes
    associativity =
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  int size= 0;
  access_cache(size);
  while(access_cache(++size));
  return size;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  flush_cache();
  int count = 0;
  int i;
  while(1) {
    access_cache(count);
    for(i = 0; i < count; i += size)
      if(!access_cache(i))
        return count;
    count += size;
  }
  return -1;  //something went wrong
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  while(1) {
    int count = 0;
    int i;
    int test_cache = size;
    while(1) {
      access_cache(test_cache);
      for(i = size; i < test_cache; i += size)
        if(!access_cache(i))
          return count;
      test_cache += size;
      count++;
    }
  }
  return -1;
}

//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
