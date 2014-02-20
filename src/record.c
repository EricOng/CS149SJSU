#include <stdlib.h>
#include <stdio.h>
#include "process.c"
#include "record.h"

#define MAX_TABLE_SIZE 20

Record newRecord()
{
    return *((Record*) malloc(sizeof(Record)));
}

void addProcess(Record* r, Process p)
{
    (*r).processCount = (*r).processCount + 1;
    Process* newArray = (Process*) malloc(sizeof(Process) * (*r).processCount);
    int i;
    for(i = 0; i < (*r).processCount - 1; i++)
    {
        newArray[i] = (*r).process[i];
    }
    newArray[(*r).processCount - 1] = p;
    (*r).process = newArray;
}

void addTimeslice(Record* r, Timeslice t)
{
    (*r).timesliceCount = (*r).timesliceCount + 1;
    Timeslice* newArray = (Timeslice*) malloc(sizeof(Timeslice) * (*r).timesliceCount);
    int i;
    for(i = 0; i < (*r).timesliceCount - 1; i++)
    {
        newArray[i] = (*r).timeslice[i];
    }
    newArray[(*r).timesliceCount - 1] = t;
    (*r).timeslice = newArray;
}

void printRecord(Record r)
{
    printf(" PID | Arrival | Priority | Duration\n");
    printf("-----+---------+----------+---------\n");
    int i;
    for(i = 0; i < r.processCount; i++)
    {
        char c = (char) (65 + i);
        printf(" %3c | %7.1f | %8d | %8.1f\n", c, r.process[i].arrival, r.process[i].priority, r.process[i].runtime);
    }
    int base;
    for(base = 0; base < r.timesliceCount; base = base + MAX_TABLE_SIZE)
    {
        printf("-----------+");
        for(i = 0; base + i < r.timesliceCount && i < MAX_TABLE_SIZE; i++)
        {
            printf("-----+");
        }
        printf("\n");
        printf(" Timeslice |");
        for(i = 0; base + i < r.timesliceCount && i < MAX_TABLE_SIZE; i++)
        {
            printf(" %3d |", r.timeslice[base + i].index);
        }
        printf("\n");
        printf("   Process |");
        for(i = 0; base + i < r.timesliceCount && i < MAX_TABLE_SIZE; i++)
        {
            printf(" %3c |", r.timeslice[base + i].pid);
        }
        printf("\n");
        printf("-----------+");
        for(i = 0; base + i < r.timesliceCount && i < MAX_TABLE_SIZE; i++)
        {
            printf("-----+");
        }
        printf("\n");
    }
}

