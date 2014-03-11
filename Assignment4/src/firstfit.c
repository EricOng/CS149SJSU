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

	return 0;
}