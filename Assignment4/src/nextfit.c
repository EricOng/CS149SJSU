#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "process.c"
#include "memory.c"

#define PROCESS_COUNT 150
#define SIMULATION_LENGTH 60

int main()
{
	srand(time(0));
	char* memory = initializeMemory();
	Process* queue = processQueue(PROCESS_COUNT);
	printProcesses(queue, PROCESS_COUNT);

	int i;	
	int currentMemoryIndex = 0;
	int time = 0, count = 0;
	
	//Fill memory before starting swapping
	while(addToMemory(queue, memory, count)){
		count++;
	}
	printMemory(memory);

	for (i = count; i < PROCESS_COUNT; i++)
	{
		printf("\n00:%02d\n", time);

		incrementProcesses(queue, PROCESS_COUNT);
		removeFromMemory(queue, memory, PROCESS_COUNT);
		printf("Current process in queue: %c\n", queue[i].pid);	
		printf("Current index 		: %d\n", currentMemoryIndex);	
		currentMemoryIndex = addToNextMemory(queue, memory, i, currentMemoryIndex);
		printMemory(memory);

		if(time >= 60){
			printf("Simulation Time Exceeded\n");
			printf("Swapped Processes: %d\n", getSwapCount());
			return 0;
		}
		time++;
	}
	printf("Out of Processes\n");
	printf("Swapped Processes: %d\n", getSwapCount());
	return 0;
}