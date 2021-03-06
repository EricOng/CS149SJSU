#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "record.c"

#define PROCESS_COUNT 50
#define SIMULATION_LENGTH 100

int main()
{
    srand(time(0));
    Process* queue = randomProcessQueue(PROCESS_COUNT);
    sortProcessesByArrival(queue, 0, PROCESS_COUNT - 1);
    int i = 0;
    float timer = 0;
    int RevIndex = PROCESS_COUNT - 1;
    int currentProcessIndex = 0;
    bool okToEnd = false;
    float wait = 0;
    Record record = newRecord();
    while(!okToEnd)
    {
        Timeslice* timeslice = (Timeslice*) malloc(sizeof(Timeslice));
        (*timeslice).index = i;
        if(queue[currentProcessIndex].arrival < i)
        {
             (*timeslice).pid = (char) (65 + currentProcessIndex);
		if((*timeslice).pid > 65+25){
			(*timeslice).pid += 6;
		}
            queue[currentProcessIndex].timeRemaining = queue[currentProcessIndex].timeRemaining - 1.0f; 
		int j;
		for(j = currentProcessIndex+1; j < PROCESS_COUNT; j++){
			if(queue[j].arrival < i){
				queue[j].waitTime +=1.0f;
				queue[j].responseTime += 1.0f;
				queue[j].age += 1;
				
			}
		}
            if(queue[currentProcessIndex].timeRemaining <= 0)
            {
		queue[currentProcessIndex].turnaroundTime = queue[currentProcessIndex].runtime + queue[currentProcessIndex].waitTime;
		queue[currentProcessIndex].timeFinished += i;
		queue[currentProcessIndex].id = (*timeslice).pid;
		
                addProcess(&record, queue[currentProcessIndex]);
                if(i >= SIMULATION_LENGTH)
                {
                    okToEnd = true;
                } else {
			timer = timer + queue[currentProcessIndex].turnaroundTime;
		    currentProcessIndex++;
			int x = 0;
			bool swapped = false;
			int indexOfNextMin = currentProcessIndex;
			for(x = currentProcessIndex; x < PROCESS_COUNT - 1; x++)
			{
				if(queue[x].arrival < i)
				if(queue[indexOfNextMin].priority > queue[x].priority)
				{
					printf("current time %d, swap priority %d with priority %d\n", i, queue[currentProcessIndex].priority, queue[x].priority);
					indexOfNextMin = x;
					swapped = true;
				}
			}
			if(swapped){
				currentProcessIndex = indexOfNextMin;
			}
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

