#include <stdio.h>
#include <stdlib.h>

#define CYLINDERS 5000
#define QUEUE_SIZE 10
#define STARTPOS 2255

int request[10] = {2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};
int handled[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int currentPosition = 2255;
int previousPosition = 1723;
int totalDistance = 0;
int wrappedAround = 0;

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
	int bestDistance = CYLINDERS + 1;
	// Check for the best option in the same direction
	int j;
	for(j = 0; j < QUEUE_SIZE; j++) {
	    if(!handled[j]) {
	        int trialDistance = request[j] - currentPosition;
	        if(trialDistance < 0) {
        	    trialDistance += CYLINDERS;
	        }
	        if(trialDistance < bestDistance) {
		    bestDistance = trialDistance;
		    bestChoice = j;
	        }
	    }
	}
	printf("Choice: %d ", request[bestChoice]);
	totalDistance += bestDistance;
	handled[bestChoice] = 1;
	previousPosition = currentPosition;
	currentPosition = request[bestChoice];
	if(wrappedAround == 0){
		if(request[bestChoice] < STARTPOS){
			totalDistance += CYLINDERS + (CYLINDERS - previousPosition) - bestDistance + currentPosition;
			wrappedAround = 1;
		}
		else if(request[bestChoice] > STARTPOS)
			wrappedAround = 0;
	}
	
	printf("Current Distance: %d\n", totalDistance);
    }
    printf("Total distance: %d\n", totalDistance);
}

