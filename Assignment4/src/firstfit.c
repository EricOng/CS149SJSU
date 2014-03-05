#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "process.c"
#include "memory.c"

#define PROCESS_COUNT 26

int main()
{
	srand(time(0));
	char* memory = initializeMemory();
	printMemory(memory);
	Process* queue = processQueue(PROCESS_COUNT);
	printProcesses(queue, PROCESS_COUNT);

	int i;
	for (i = 0; i < PROCESS_COUNT; i++)
	{
		//removeFromMemory(queue, memory, PROCESS_COUNT);
		addToMemory(queue[i], memory);
		printMemory(memory);
	}

	return 0;
}