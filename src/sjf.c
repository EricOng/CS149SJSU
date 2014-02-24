#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "record.c"

#define PROCESS_COUNT 50
#define SIMULATION_LENGTH 100

int main()
{
    Process* queue = randomProcessQueue(PROCESS_COUNT);
    sortProcessesByArrival(queue, 0, PROCESS_COUNT - 1);
    int i = 0;
    float time = 0;
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
            queue[currentProcessIndex].timeRemaining = queue[currentProcessIndex].timeRemaining - 1.0f; 
		int j;
		for(j = currentProcessIndex+1; j < PROCESS_COUNT; j++){
			if(queue[j].arrival < i){
				queue[j].waitTime +=1.0f;
			}
		}
            if(queue[currentProcessIndex].timeRemaining <= 0)
            {
		queue[currentProcessIndex].turnaroundTime = queue[currentProcessIndex].runtime + queue[currentProcessIndex].waitTime;

                addProcess(&record, queue[currentProcessIndex]);
                if(i >= SIMULATION_LENGTH)
                {
                    okToEnd = true;
                } else {
			time = time + queue[currentProcessIndex].turnaroundTime;
		    currentProcessIndex++;
			int x = 0;
			bool swapped = false;
			int indexOfNextMin = currentProcessIndex;
			for(x = currentProcessIndex; x < PROCESS_COUNT - 1; x++)
			{
				if(queue[x].arrival < i)
				if(queue[x].runtime < queue[currentProcessIndex].runtime)
				{
					indexOfNextMin = x;
					swapped = true;
				}
			}
			if(swapped){
			printf("at time %d\n", i);
			Process p = queue[currentProcessIndex];
			printf("swap p%d arrival %8.1f, run %8.1f \n",currentProcessIndex, p.arrival, p.runtime);
			printf("with p%d arrival %8.1f, run %8.1f \n",indexOfNextMin, queue[indexOfNextMin].arrival, queue[indexOfNextMin].runtime);
			queue[currentProcessIndex] = queue[indexOfNextMin];
			queue[indexOfNextMin] = p;
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

