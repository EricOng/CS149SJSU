#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "record.c"

#define PROCESS_COUNT 26
#define SIMULATION_LENGTH 100

bool done = false;

void updateReadyQueue();
void nextProcessIndex();

int main()
{
    Process* arrivalQueue = randomProcessQueue(PROCESS_COUNT);
    sortProcessesByArrival(arrivalQueue, 0, PROCESS_COUNT - 1);
	Process* readyQueue = (Process*) malloc(PROCESS_COUNT * sizeof(Process));
    int i = 0, size = 0;
    int currentProcessIndex = 0;
    bool okToEnd = false;
    Record record = newRecord();
    while(!okToEnd)
    {
        Timeslice* timeslice = (Timeslice*) malloc(sizeof(Timeslice));
        (*timeslice).index = i;
		if(i < SIMULATION_LENGTH) updateReadyQueue(arrivalQueue, readyQueue, i, &size);
        if(size > 0 && (readyQueue[currentProcessIndex].timeRemaining > 0))
        {
            (*timeslice).pid = (char) (65 + currentProcessIndex);
			readyQueue[currentProcessIndex].id = (*timeslice).pid;
            readyQueue[currentProcessIndex].timeRemaining = readyQueue[currentProcessIndex].timeRemaining - 1.0f;
            if(readyQueue[currentProcessIndex].timeRemaining <= 0)
            {
				readyQueue[currentProcessIndex].timeFinished = i + 1;
				readyQueue[currentProcessIndex].turnaroundTime = ((float) i + 1) - readyQueue[currentProcessIndex].arrival + readyQueue[currentProcessIndex].timeRemaining;
                addProcess(&record, readyQueue[currentProcessIndex]);
            }
        } else {
           (*timeslice).pid = '-';
        }
        addTimeslice(&record, (*timeslice));
		nextProcessIndex(readyQueue, &currentProcessIndex, i, size);
        i++;
	if(done) okToEnd = true;
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

void nextProcessIndex(Process* ready, int* nIndex, int index, int size)
{
	if(size == 0) return;
	int counter = 0;
	*nIndex += 1;
	while((*nIndex == size || (ready[*nIndex].timeRemaining <= 0.0f)) && counter != size)
	{
		if(*nIndex >= size)
		{
			*nIndex = 0;
		}
		if(ready[*nIndex].timeRemaining <= 0.0f)
		{
			*nIndex += 1;
		}
		counter++;
	}
	if(index >= SIMULATION_LENGTH && counter == size) done = true;
}