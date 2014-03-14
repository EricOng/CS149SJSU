#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
	bool added;
	char pid;
	int size;
	int duration;
	int waitTime;
} Process;

Process createProcess(int index)
{
	Process* p = (Process*) malloc(sizeof(Process));
	p->added = false;
	p->pid = (65 + index);
	p->size = pow(2,(rand() % 4 + 2));
	p->duration = rand() % 5 + 1;
	p->waitTime = 0;
	return *p;
}

Process* processQueue(int size)
{
    Process* queue = (Process*) malloc(size * sizeof(Process));
   	int i = 0;
    while(i < size)
   	{
       	queue[i++] = createProcess(i);
   	}

    return queue;
}

void incrementProcesses(Process* queue, int size)
{
	int i;
	//printf("Attempting to increment process timer\n");
	for (i = 0; i < size; i++){
		if(queue[i].added){
			queue[i].waitTime += 1;
			//printf("Process %c incremented\n", queue[i].pid);
		}
	}
}

void printProcesses(Process* queue, int size)
{
	printf("Process|Size|Duration\n");
	int i = 0;
	while(i < size)
	{
		Process p = queue[i++];
		printf("%4c   |%3d |%3d sec\n", p.pid, p.size, p.duration);
	}
}