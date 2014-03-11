#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct {
	char pid;
	int size;
	int duration;
} Process;

Process createProcess(int index)
{
	Process* p = (Process*) malloc(sizeof(Process));
	p->pid = (65 + index);
	p->size = pow(2,(rand() % 4 + 2));
	p->duration = rand() % 5 + 1;
	
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