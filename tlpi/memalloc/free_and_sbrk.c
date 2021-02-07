/**
 * This demonstrates what happens to the memory break
 * when memory is freed.
 * 
 * Run this command line program by typing:
 *      $ ./free_and_sbrk 1000 10240 2
 * ,which will allocate 1000 blocks of memory and 
 * then free every second block.
 */

#include "../lib/tlpi_hdr.h"

#define MAX_ALLOCS 1000000

int main(int argc, char *argv[])
{
    char* memory_pool[MAX_ALLOCS];
    
    printf("\n");
    
    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s num-allocs block-size [step [min [max]]]\n", argv[0]);
    
    int number_of_allocated_bytes = getInt(argv[1], GN_GT_0, "num-allocs");
    
    if (number_of_allocated_bytes > MAX_ALLOCS)
        cmdLineErr("num-allocs > %d\n", MAX_ALLOCS);
    
    int block_size = getInt(argv[2], GN_GT_0 | GN_ANY_BASE, "block-size");
    
    int step = (argc > 3) ? getInt(argv[3], GN_GT_0, "step") : 1;
    
    int freeMin = (argc > 4) ? getInt(argv[4], GN_GT_0, "min") : 1;
    
    int freeMax = (argc > 5) ? getInt(argv[5], GN_GT_0, "max") : number_of_allocated_bytes;
    
    if (freeMax > number_of_allocated_bytes)
        cmdLineErr("free-max > num-allocs\n");
    
    printf("Initial program break: %10p\n", sbrk(0));
    
    printf("Allocating %d*%d bytes\n", number_of_allocated_bytes, block_size);
    
    for (int i = 0; i < number_of_allocated_bytes; i++)
    {
        memory_pool[i] = malloc(block_size);
        if (memory_pool[i] == NULL)
            errExit("malloc");
    }
    
    printf("Program break is now: %10p\n", sbrk(0));
    
    printf("Freeing blocks from %d to %d in steps of %d\n",
           freeMin, freeMax, step);
    
    for (int i = freeMin - 1; i < freeMax; i += step)
        free(memory_pool[i]);
    
    printf("After free(), program break is: %10p\n", sbrk(0));
    exit(EXIT_SUCCESS);
}