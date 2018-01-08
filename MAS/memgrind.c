#include "mymalloc.h"
#include <time.h>
#include <sys/time.h>

/* test the memory allocator with the following workloads */

int main(int argc, char*argv[])
{
	printf("Choose from workload A to F to test the memory allocation\n");
	char choice = getchar();
	char *pointers[5000];
	struct timeval start, end;
	int i = 0, j = 0;
	long unsigned int workload = 0;
	switch(choice)
	{
        	case'A':
        		printf("A: 1000 separate malloc()s of 1 byte, then free() the 1000 pointers one by one\n");
			gettimeofday(&start, NULL);
			for(i = 0; i < 1000; i++)
        		{
        			pointers[i] = malloc(1);
					if(saturated(1)==1){
						printf("allocated %d\n", i+1);
					}
        		}
        		for(j = 0; j < 1000; j++)
        		{
        			free(pointers[j]);
        		}
			printf("freed 1000 pointers one by one\n");
        		gettimeofday(&end, NULL);
			break;

        	case'B':
        		printf("B: first malloc() 1 byte and immediately free it - do this 1000 times\n");
        		gettimeofday(&start, NULL);
			for(i = 0; i < 1000; i ++)
        		{
        			void* pp = malloc(1);
        			free(pp);
				printf("allocated and freed %d time\n", i+1);
        		}
			gettimeofday(&end, NULL);
        		break;

        	case'C':
        		printf("C: Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer - do this 1000 times\n");
        		gettimeofday(&start, NULL);
				int counter = 0;
				void* var[1000];
				int abcd;
				for(abcd=0; abcd<1000; abcd++){
					var[abcd]=NULL;
				}
				while(counter!=999){
					int rd = rand() %2;
					if(rd==0){
						void* test = malloc(1);
						var[counter] = test;
						counter++;
					}else if(rd==1){
						int i;
						for(i=0; i<1000; i++){
							if(var[i]!=NULL){
								free(var[i]);
								var[i] = NULL;
								break;
							}
						}
					}
				}
				int i;
				for(i=0; i<1000; i++){
					if(var[i]!=NULL){
						free(var[i]);
					}
				}
                
			
			gettimeofday(&end, NULL);	
			break;
	    	/* keep track of each malloc make sure do not exceed the total memory capacity
      	       	 * eventually malloc() 1000 times
       	       	 * eventually free() all pointers
     		 * choose a random allocation size between 1 and 64 bytes
      		 */
        	case'D':
        		printf("D: Randomly choose between a randomly-sized malloc() or free()ing a pointer - do this many times\n");
				gettimeofday(&start, NULL);
				int counter1 = 0;
				void* vara[1000];
				int abc ;
				for(abc=0; abc<1000; abc++){
					vara[abc]=NULL;
				}
				while(counter1!=999){
					int rd = rand() %2;
					if(rd==0){
						int sz = rand() %65;
						while(sz==0){
							sz = rand() %65;
						}
						if(saturated(sz)==0){
							rd=1;
						}
						void* test = malloc(sz);
						vara[counter1] = test;
						counter1++;
					}else if(rd==1){
						int ii;
						for(ii=0; ii<1000; ii++){
							if(vara[ii]!=NULL){
								free(vara[ii]);
								vara[ii] = NULL;
								break;
							}
						}
					}
				}
				int ii;
				for(ii=0; ii<1000; ii++){
					if(vara[ii]!=NULL){
						free(vara[ii]);
					}
				}
                
			
			gettimeofday(&end, NULL);
        		break;
		case'E':
			printf("E: test\n");
        		gettimeofday(&start, NULL);
			int c;
			void* pt[1000];
			while(c!=999){
				int ds = rand() %2;
				if(ds==0){
					int ch = rand() %3;
					if(ch == 0){
						pt[c] = malloc(sizeof(int));
					}else if(ch==1){
						pt[c] = malloc(sizeof(char));
					}else if(ch==2){
						pt[c] = malloc(sizeof(double));
					}
					c++;
				}else if(ds==1){
					int ic;
					for(ic=0; ic<1000;ic++){
						if(pt[ic]!=NULL){
							free(pt[ic]);
							pt[ic] = NULL;
						}
					}
				}
			}
			int icd;
			for(icd=0; icd<1000;icd++){
				if(pt[icd]!=NULL){
				free(pt[icd]);
				pt[icd] = NULL;
				}
			}		
			printf("E: test finished\n");
        		gettimeofday(&end, NULL);
			break;	
		case'F':
        		printf("F: \n");
			gettimeofday(&start, NULL);
			int cd;
			void* ptt[1000];
			while(cd!=999){
				int ds = rand() %2;
				if(ds==0){
					int ch = rand() %11;
					while(ch==0){
						ch = rand() %11;
					}
					ptt[cd] = malloc(ch*sizeof(int));
					cd++;
				}else if(ds==1){
					int ic;
					for(ic=0; ic<1000;ic++){
						if(ptt[ic]!=NULL){
							free(ptt[ic]);
							ptt[ic] = NULL;
						}
					}
				}
			}
			int ibd;
			for(ibd=0; ibd<1000;ibd++){
				if(pt[ibd]!=NULL){
				free(pt[ibd]);
				pt[ibd] = NULL;
				}
			}		
			gettimeofday(&end, NULL);
			break;
		default:
			printf("Please enter a valid choice from A to F\n");
			int siz = (int) sizeof(struct metadata);
			printf("The size of self-defined metadata struct is %i.\n", siz);
	}
	workload = end.tv_sec * 1000000 + end.tv_usec - (start.tv_sec * 1000000 + start.tv_usec);
	printf("The timing of workload %c is %lu microseconds.\n", choice, workload);
	return 0;
}
