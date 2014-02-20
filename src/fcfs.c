#include <stdio.h>
#include <stdbool.h>
#include "process.c"

#define PROCESS_COUNT 50
#define SIMULATION_LENGTH 100

int main()
{
    Process* queue = randomProcessQueue(PROCESS_COUNT);
    sortProcessesByArrival(queue, 0, PROCESS_COUNT - 1);
    int i = 0;
    int currentProcessIndex = 0;
    bool okToEnd = false;
    while(!okToEnd)
    {
        printf("%d:\n", i);
        if(queue[currentProcessIndex].arrival < i)
        {
            printf("Current process: %d (%.1f remaining)\n", currentProcessIndex, queue[currentProcessIndex].runtime);
            queue[currentProcessIndex].runtime = queue[currentProcessIndex].runtime - 1.0f;
            if(queue[currentProcessIndex].runtime <= 0)
            {
                printf("\tComplete!\n");
                currentProcessIndex++;
                if(i >= SIMULATION_LENGTH)
                {
                    okToEnd = true;
                }
            }
        } else {
            printf("Process %d has not arrived!\n", currentProcessIndex);
            printf("\t(Arrives @ %.1f)\n", queue[currentProcessIndex].arrival);
        }
        i++;
    }
    return 0;
}

