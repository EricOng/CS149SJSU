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
       	memory[i++] = '.';
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