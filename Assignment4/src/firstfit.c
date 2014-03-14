#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "process.c"
#include "memory.c"

#define PROCESS_COUNT 60
#define SIMULATION_LENGTH 60

int main()
{
	char* memory = initializeMemory();
	printMemory(memory);
	Process* queue = processQueue(PROCESS_COUNT);
	printProcesses(queue, PROCESS_COUNT);

	int i;
	int time = 0;

	for (i = 0; i < PROCESS_COUNT; i++)
	{
		printf("\n00:%02d", time);

		incrementProcesses(queue, PROCESS_COUNT);
		removeFromMemory(queue, memory, PROCESS_COUNT);
		if(addToMemory(queue, memory, i)){
		}
		else{
			i--;
		}
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