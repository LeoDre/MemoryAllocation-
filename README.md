# MemoryAllocation++
##  Structure of this program
-mymalloc.c  
-mymalloc.h  
-memgrind.c  
-testcases.txt (how we test our program)
## General Information
This program uses a char array with size of 5000 named myblock[] to simulate
main memory. It contains two basic functions, mymalloc() and myfree(), developed
based on the regular malloc() and free() functions in C programming. The mymalloc()
function returns a pointer to a free block of memory somewhere belong to this array
that is ready for use if possible. During the whole process of memory allocation, this
program provides the information of errors including the file name and line number of
the execution that causes to the error.
## Data Structure
This program uses a char array to simulate main memory (static char
myblock[5000]). Whenever a memory allocation is needed (mymalloc() get called), it
generates a struct that stores the information of the following memory block in this
array. This self-defined struct is called metadata. The metadata struct stores the size of
the following memory block, whether the memory is free or not, and a struct pointer
that points to the next metadata struct. Since the program needs to traverse throughout
the whole main memory, the metadata structs are stored as a linked list data structure.

