#include <stdlib.h>
#include <stdio.h>

#define QUEUE_SIZE 10
#define CYLINDERS 5000

int previous = 1723;
int current = 2255;
int queue[QUEUE_SIZE] = {2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};

void least_seek_time()
{
	int k;
	int least_time = 5000;
	int least_index = 10;
	
	for(k = 0; k < QUEUE_SIZE; k++)
	{
		int difference = abs(current - queue[k]);
		if(queue[k] == -1) continue;
		else if(difference < least_time)
		{
			least_time = difference;
			least_index = k;
		}
	}
	previous = current;
	current = queue[least_index];
	queue[least_index] = -1;
}

int main()
{
	int i;
	int total_distance = 0;
	
	printf("ACCESS ORDER\n");
	for(i = 0; i < QUEUE_SIZE; i++)
	{
		least_seek_time();
		total_distance = total_distance + abs(current - previous);
		printf("%2d: %d\n", i + 1, current);
	}
	
	printf("TOTAL DISTANCE: %d\n", total_distance);
}