#include <stdlib.h>
#include <stdio.h>

#define QUEUE_SIZE 10
#define CYLINDERS 5000

int previous = 1723;
int current = 2255;
const int queue[QUEUE_SIZE] = {2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};

int main()
{
	int i;
	int total_distance = 0;
	
	printf("ACCESS ORDER\n");
	for(i = 0; i < QUEUE_SIZE; i++)
	{
		previous = current;
		current = queue[i];
		
		total_distance = total_distance + abs(current - previous);
		printf("%2d: %d\n", i + 1, current);
	}
	
	printf("TOTAL DISTANCE: %d\n", total_distance);
}