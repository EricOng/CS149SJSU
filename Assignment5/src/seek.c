#include <stdio.h>
#include <stdlib.h>

#define MAX_CYLINDER 4999
#define QUEUE_SIZE 10

int request[10] = {2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};
int handled[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int currentPosition = 2255;
int previousPosition = 1723;
int totalDistance = 0;

int main();

int main() {
    int i;
    printf("Requests: ");
    for(i = 0; i < QUEUE_SIZE; i++) {
	printf("%d ", request[i]);
    }
    printf("\n");
    // Loop 10 times (until all requests are handled)
    for(i = 0; i < QUEUE_SIZE; i++) {
	int bestChoice = -1;
	// Check for the best option in the same direction
	int j;
	for(j = 0; j < QUEUE_SIZE; j++) {
	    if(!handled[j]) {
		if(currentPosition > previousPosition) { // "Same direction" is forward
		    if(request[j] > currentPosition) {
			if(bestChoice == -1 || request[bestChoice] > request[j]) {
			    bestChoice = j;
			}
		    }
		} else { // "Same direction" is backward
		    if(request[j] < currentPosition) {
			if(bestChoice == -1 || request[bestChoice] < request[j]) {
			    bestChoice = j;
			}
		    }
		}
	    }
	}
	if(bestChoice == -1) { // In case we didn't find anything in the right direction
	    for(j = 0; j < QUEUE_SIZE; j++) {
		if(!handled[j]) {
		    if(bestChoice == -1 || abs(request[bestChoice] - currentPosition) > abs(request[j] - currentPosition)) {
			bestChoice = j;
		    }
		}
	    }
	}
	printf("Choice: %d\n", request[bestChoice]);
	totalDistance += abs(request[bestChoice] - currentPosition);
	handled[bestChoice] = 1;
	previousPosition = currentPosition;
	currentPosition = request[bestChoice];
    }
    printf("Total distance: %d\n", totalDistance);
}

