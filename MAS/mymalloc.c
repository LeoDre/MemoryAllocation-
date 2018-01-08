#include "mymalloc.h"

static char myblock[5000];
static struct metadata *head; //poionts to the first metadata

//when the target memory block is larger than the size of a new metadata plus the requested allocation
void split(struct metadata *target, int size)
{
	struct metadata *newMetadata = (void *) ((void*) target + size + sizeof(struct metadata)); //as void pointer
	newMetadata->size = target->size - size - sizeof(struct metadata);
	newMetadata->isFree = 1;
	newMetadata->next = target->next;
	target->next = newMetadata;
	target->size = size;
	target->isFree = 0;
}



/* a function that takes a pointer to the head of metadata linked list and the target size of memory storage
 * by comparing all free metadata->size with target size, check if the memory is saturated
 * The memory is saturated only when there's no free metadata block or all free metadata blocks are not large enough to hold
 * Return 0 if cannot find an available memory spot, is saturated; Return 1 if there is available space, is not saturated.
 */
int saturated(int size)
{
	struct metadata *curr = head;
	while(curr != NULL)
	{
		if(curr->isFree && curr->size >= size) return 1;
		curr = curr->next;		
	}
	return 0;
}

/* initialize the array if not by assigning a first metadata block
 * traverse through all the metadata blocks to see if the memory block is free or not
 * if free, check if it is large enough
 * if it is larger than the requested size, split it and assign a new metadata to the spare part
 * check if there is no free data block, or the free data blocks are not large enough (Error D)
 */
void *mymalloc(int size, char *file, unsigned int line)
{
	struct metadata *curr;
	static int initialized = 0;
	void *result = NULL;
	//check if myblock[5000] is initialized
	if(!(initialized))
	{
		head = (struct metadata*) myblock;
		head->size = 5000 - sizeof(struct metadata);
		head->isFree = 1;
		head->next = NULL;
		initialized = 1;
	}
	
	curr = head;
	while(curr != NULL)
	{
		if(curr->isFree && curr->size >= size)
		{
			if(curr->size > (sizeof(struct metadata) + size))
			{
				split(curr, size);
				printf("Allocated with a split\n");
			}
			//skip the split if the memory block cannot store a new metadata block after allocation
			curr->isFree = 0;
			printf("Memory allocated of size %d\n", curr->size);	
			result = (void *)(++curr);
			return result;	
		}
		curr = curr->next;
		//printf("One metadata checked\n");
	}
	if(result == NULL)
	{
	printf("Error D: Saturation of dynamic memory. There's no sufficient space for memory allocation. Error occurs at file %s, line %d\n", file, line);
	}
	return result;
}

/* called when a memory block is successfuly freed, check if the adjacent metadata blocks are also free
 * starting from the metadata block that is right ahead of the free()d one,  merge the free blocks together
 */
int merge(struct metadata *target, struct metadata *prev)
{
        struct metadata *curr;
        if(!prev) curr = target;
	 //if the target metadata is the head metadata block
	else{
		curr = prev;
	}
        while(curr != target->next && curr->next != NULL)
        {
                if((curr->isFree)&&(curr->next->isFree))
                {
                        curr->size += curr->next->size + sizeof(struct metadata);
                        curr->next = curr->next->next;
			printf("Merged, new memory block size is %d byte.\n",curr->size);
                }
                curr = curr->next;
        }
	return 0;
}

/* free the memory block by setting the corresponding metadata isFree to 1
 * traverse all metadata blocks to see if the pointer points to one of the metadata blocks (Error B)
 * during the loop, detect if the pointer points to a metadata that is already freed (Error C)
 */
void myfree(void *ptr, char *file, unsigned int line)
{
	if(ptr < (void*)&myblock[0] || ptr > (void*)&myblock[4999])
	{
		printf("Error A: Free()ing addresses that are not pointers. Error occurs at file %s, line %d\n", file, line);
	}

	struct metadata *curr = head, *prev = NULL;
	//prev is kept for future possible merging use
	struct metadata *target = (struct metadata *) ((char*)ptr - sizeof(struct metadata)); 
	//the input pointer is not pointing to the metadata, so adjust the target comparison
	for(curr = head; curr != NULL; curr = curr -> next)
	{
		if(curr == target)
		{
			if(curr->isFree == 1)
			{
				printf("Error C: Redundant free()ing of the same pointer. Or the pointer has not been allocated. Error occurs at file %s, line %d\n", file, line);
				return;
			}
			curr->isFree = 1;
			printf("Successfully freed a memory block with size of %d byte.\n",curr->size);
			merge(curr, prev);//merge the free blocks from head till curr
			return;
		}
		prev = curr;
	}
	printf("Error B: Free()ing pointers that were not allocated by malloc(). Error occurs at file %s, line %d\n", file, line);
	//???How to detect error A: if is not freeing a pointer
}

