#include <stdlib.h>
#include <stdio.h>
#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)


/* metadata is used to store the information of the data
 * size int stores the size of the memory block that can be used for future allocation
 * isFree indicates whether the memory block is allocated or not, 0 when allocated, 1 when free
 * metadata are stored in a linked list structure, so next points to the next metadata
 */
struct metadata
{
	int size;
	int isFree;
	struct metadata *next;
};

void *mymalloc(int size , char *file, unsigned int line);

int saturated(int size);

int  merge(struct metadata *, struct metadata *);

void myfree(void *ptr, char *file, unsigned int line);



