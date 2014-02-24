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
            if(queue[currentProcessIndex].timeRemaining <= 0)
            {
                addProcess(&record, queue[currentProcessIndex]);
                if(i >= SIMULATION_LENGTH)
                {
                    okToEnd = true;
                } else {
		    wait = wait + queue
			[currentProcessIndex].runtime;
		    currentProcessIndex++;
			int x = 0;
			int indexOfNextMin = currentProcessIndex;
			for(x = currentProcessIndex; x < PROCESS_COUNT - 1; x++)
			{
				if(queue[x].arrival < i)
				if(queue[x].runtime < queue[currentProcessIndex].runtime)
				{
					indexOfNextMin = x;
				}
			}
			printf("at time %d\n", i);
			Process p = queue[currentProcessIndex];
			printf("swap arrival %8.1f, run %8.1f \n", p.arrival, p.runtime);
			printf("with arrival %8.1f, run %8.1f \n", queue[indexOfNextMin].arrival, queue[indexOfNextMin].runtime);
			queue[currentProcessIndex] = queue[indexOfNextMin];
			queue[indexOfNextMin] = p;
			

		    queue[currentProcessIndex].waitTime = wait;
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
