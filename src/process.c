#include <stdlib.h>
#include "process.h"

int randInt(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

Process randomProcess()
{
    Process* p = (Process*) malloc(sizeof(Process));
    (*p).priority = randInt(1, 4);
    (*p).arrival = ((float) randInt(0, 990)) / 10;
    (*p).runtime = ((float) randInt(0, 100)) / 10;
    (*p).timeRemaining = (*p).runtime;
    return *p;
}

Process* randomProcessQueue(int queueSize)
{
    Process* queue = (Process*) malloc(queueSize * sizeof(Process));
    int i = 0;
    while(i < queueSize)
    {
        queue[i++] = randomProcess();
    }
    return queue;
}

void sortProcessesByArrival(Process* process, int low, int high)
{
    if(high <= low)
    {
        return;
    }
    int mid = (high + low) / 2;
    sortProcessesByArrival(process, low, mid);
    sortProcessesByArrival(process, mid + 1, high);
    int i = low;
    int j = mid + 1;
    int buff = 0;
    while(i <= mid + buff && j <= high)
    {
        if(process[j].arrival < process[i].arrival)
        {
            Process temp = process[j];
            int a = j;
            while(a > i)
            {
                process[a] = process[a - 1];
                a--;
            }
            buff++;
            j++;
            process[i] = temp;
        }
        i++;
    }
}

