#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MEMORY_SIZE 100

char* initializeMemory()
{
	char* memory = (char*) malloc(MEMORY_SIZE * sizeof(char));
	int i = 0;
    while(i < MEMORY_SIZE)
   	{
       	memory[i++] = '.'; //dots are holes in memory
   	}

    return memory;
}

void printMemory(char* memory)
{
	int i = 0;
	while(i < MEMORY_SIZE)
	{
		if(i % 25 == 0) printf("\n");
		printf("%c", memory[i++]);
	}
	printf("\n");
}

/**
 * Add process to first memory space big enough to store it
 */
void addToMemory(Process process, char* memory)
{
	int p_Size = process.size;
	int index = findMemoryIndex(p_Size, memory);
	while (p_Size != 0)
	{
		memory[index] = process.pid;
		index++;
		p_Size--;
	}
}

/**
 * Find the first index in memory that has enough space for the process
 */
int findMemoryIndex(int sizeNeeded, char* memory)
{
	int countSpace = 0;
	int i;
	
	for (i = 0; i < MEMORY_SIZE; i++)
	{
		if(memory[i] == '.'){
			countSpace++;
			if (countSpace == sizeNeeded){
				return i - sizeNeeded + 1;
			}
		}
		else{
			countSpace = 0;
		}		
	}
	//no spaces available
	return -1;	
}
