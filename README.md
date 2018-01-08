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
## Error Detection
This program returns the at least one of the following four errors when an error is
detected.  
A: Free()ing addresses that are not pointers.  
B: Free()ing pointers that were not allocated by malloc().  
C: Redundant free()ing of the same pointer.  
D: Saturation of dynamic memory.  
Error A is detected by checking if the provided address is in the address range of
myblock[5000]. Error B is detected by checking all pointers against the target pointer
by traversing through the linked list of metadata blocks. So there are possibilities that
error A and B occur simultaneously, or only error B occurs. It is hard for us to tell the
difference between an address that is a pointer but does not point to the simulated
main memory, or it is simply not a pointer. Error C is detected by checking the isFree
data of the metadata ahead of the input pointer. Error D is detected by checking
whether there is any available metadata block, which is both free and large enough to
hold the requested data size.
##  Workload data
Different workload costs of time measured by function gettimeofday().(in microseconds)  

 A      | B     | C     | D     | E     | F     
 ------ | ----- | ----- | ----- | ----- | ----- 
 139983 | 35276 | 37724 | 29264 | 8984  | 34202 
 127544 | 37075 | 26532 | 29099 | 8929  | 36473 
 67910  | 34080 | 35183 | 18551 | 11133 | 18927 
 18181  | 60151 | 17750 | 17596 | 33209 | 18090 
 149366 | 33876 | 30888 | 14168 | 14281 | 21408 
 103849 | /     | /     | /     | /     | /     

##  Findings
The time that allocation needs to take varies overtime, and some of them stay in a
more steady range while others vary a lot. This may be caused by the randomness of
the memory size that is being allocated and freed. The workload A is most timeconsuming
on iLab machines which surprises us, we suppose that the cost of time
varies on different machines. We found that it is also impossible for workload A to
hold all of the 1000 allocation, because the size of metadata is too large compared to
the size of memory allocation that is being requested.
Apart from workload A, the time costs of workloads B and C are larger than those
of workloads D, E, and F in general. When the program allocates larger memory
blocks in general, less metadata blocks are needed to store the information of the
memory blocks, so the time of traversing through the metadata linked list will
decrease. The reason for workload A being most time-consuming may be the same—it
needs to traverse through the metadata structs with the least step taking each time.
The gap among the costs of time may will become more obvious when the size of
main memory increases (the size of myblock array).
##  Contributions
**Team Members**: Ran Sa, Chengguizi Han
