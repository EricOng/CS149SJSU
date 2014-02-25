#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "record.c"

#define PROCESS_COUNT 75
#define SIMULATION_LENGTH 100

void updateReadyQueue();
void findShortestProcessIndex();

int main()
{
    Process* arrivalQueue = randomProcessQueue(PROCESS_COUNT);
    sortProcessesByArrival(arrivalQueue, 0, PROCESS_COUNT - 1);
	Process* readyQueue = (Process*) malloc(PROCESS_COUNT * sizeof(Process));
    int i = 0, size = 0;
	int shortestProcessIndex = 0;
    int currentProcessIndex = 0;
    bool okToEnd = false;
    Record record = newRecord();
    while(!okToEnd)
    {
        Timeslice* timeslice = (Timeslice*) malloc(sizeof(Timeslice));
        (*timeslice).index = i;
		updateReadyQueue(arrivalQueue, readyQueue, i, &size);
		findShortestProcessIndex(readyQueue, &shortestProcessIndex, size);
        if(size > 0 && (readyQueue[shortestProcessIndex].timeRemaining > 0))
        {
            (*timeslice).pid = (char) (65 + shortestProcessIndex);
			readyQueue[shortestProcessIndex].id = (*timeslice).pid;
            readyQueue[shortestProcessIndex].timeRemaining = readyQueue[shortestProcessIndex].timeRemaining - 1.0f;
            if(readyQueue[shortestProcessIndex].timeRemaining <= 0)
            {
				readyQueue[shortestProcessIndex].timeFinished = i + 1;
				readyQueue[shortestProcessIndex].turnaroundTime = ((float) i + 1) - readyQueue[shortestProcessIndex].arrival + readyQueue[shortestProcessIndex].timeRemaining;
                addProcess(&record, readyQueue[shortestProcessIndex]);
                if(i >= SIMULATION_LENGTH)
                {
                    okToEnd = true;
                }
            }
        } else {
           (*timeslice).pid = '-';
        }
        addTimeslice(&record, (*timeslice));
        i++;
    }
    printRecord(record);
    return 0;
}

void updateReadyQueue(Process* queue, Process* ready, int index, int* size)
{
	if(index == 0) return;
	int i = *size;
	for(i; i < PROCESS_COUNT; i++)
	{
		if(queue[i].arrival > index) break;
		else if((queue[i].arrival > index - 1) && (queue[i].arrival <= index))
		{
			ready[*size] = queue[i];
			*size = i + 1;
		}
		else return;
	}
}

void findShortestProcessIndex(Process* ready, int* spIndex, int size)
{
	int i = 0;
	float currentShortestRuntime = 11.0f;
	for(i; i < size; i++)
	{
		if((ready[i].timeRemaining < currentShortestRuntime) && (ready[i].timeRemaining > 0.0f))
		{
			currentShortestRuntime = ready[i].timeRemaining;
			*spIndex = i;
		}
	}
}