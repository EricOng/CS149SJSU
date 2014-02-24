#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "record.c"

#define PROCESS_COUNT 75
#define SIMULATION_LENGTH 100

int main()
{
    Process* queue = randomProcessQueue(PROCESS_COUNT);
    sortProcessesByArrival(queue, 0, PROCESS_COUNT - 1);
    int i = 0;
    int currentProcessIndex = 0;
    bool okToEnd = false;
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
            for(j = currentProcessIndex + 1; j < PROCESS_COUNT && i > queue[j].arrival; j++)
            {
                queue[j].waitTime += 1.0f;
                queue[j].responseTime += 1.0f;
            }
            if(queue[currentProcessIndex].timeRemaining <= 0)
            {
                queue[currentProcessIndex].turnaroundTime = ((float) i + 1) - queue[currentProcessIndex].arrival + queue[currentProcessIndex].timeRemaining;
                addProcess(&record, queue[currentProcessIndex]);
                if(i >= SIMULATION_LENGTH)
                {
                    okToEnd = true;
                } else {
                    currentProcessIndex++;
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

