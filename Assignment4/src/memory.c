#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define MEMORY_SIZE 100

int swappedIn = 0;

char* initializeMemory()
{
	char* memory = (char*) malloc(MEMORY_SIZE * sizeof(char));
	int i = 0;
    while(i < MEMORY_SIZE)
   	{
       	memory[i++] = '.'; //dots are holes in memory
   	}

    return memory;
}

void printMemory(char* memory)
{
	int i = 0;
	while(i < MEMORY_SIZE)
	{
		if(i % 25 == 0) printf("\n");
		printf("%c", memory[i++]);
	}
	printf("\n");
}

/**
 * Add process to first memory space big enough to store it
 */
bool addToMemory(Process* process, char* memory, int p_Index)
{
	int p_Size = process[p_Index].size;
	int index = findMemoryIndex(p_Size, memory);
	if(index != -1){
		while (p_Size != 0)
		{
			memory[index] = process[p_Index].pid;
			index++;
			p_Size--;
		}
		printf("\n+ Added Process %c | Size: %2d | Duration: %d\n", process[p_Index].pid, process[p_Index].size, process[p_Index].duration);
		process[p_Index].added = true;
		swappedIn++;
		return true;
	}
	else{
		printf("\nCannot fit process %c\n", process[p_Index].pid);
		return false;
	}
}

/**
 * Add process to the next memory space big enough to store it
 */
int addToNextMemory(Process* process, char* memory, int p_Index, int m_Index)
{
	int p_Size = process[p_Index].size;
	int index = findNextMemoryIndex(p_Size, memory, m_Index);
	if(index != -1){
		while (p_Size != 0)
		{
			memory[index] = process[p_Index].pid;	
			index++;
			p_Size--;
		}
		printf("+ Added Process %c | Size: %2d | Duration: %d\n", process[p_Index].pid, process[p_Index].size, process[p_Index].duration);
		process[p_Index].added = true;
		swappedIn++;
		m_Index = index;	
	}
	else{
		//no spaces currently available in memory
		//reset index to 0
		m_Index = 0;	
	}
	return m_Index;
}

/**
 * Add process to the best memory space big enough to store it
 */
bool addToBestMemory(Process* process, char* memory, int p_Index, int size)
{
	int p_Size = process[p_Index].size;
	int index = findBestMemoryIndex(p_Size, memory);
	if(index != -1)
	{
		while (p_Size != 0)
		{
			memory[index] = process[p_Index].pid;
			index++;
			p_Size--;
		}
		printf("+ Added Process %c | Size: %2d | Duration: %d\n", process[p_Index].pid, process[p_Index].size, process[p_Index].duration);
		process[p_Index].added = true;
		swappedIn++;
		return true;
	}
	else
	{
		printf("\nCannot fit process %c\n", process[p_Index].pid);
		return false;
	}
}

/**
 * Find the first index in memory that has enough space for the process
 */
int findMemoryIndex(int sizeNeeded, char* memory)
{
	int countSpace = 0;
	int i;
	
	for (i = 0; i < MEMORY_SIZE; i++)
	{
		if(memory[i] == '.'){
			countSpace++;
			if (countSpace == sizeNeeded){
				return i - sizeNeeded + 1;
			}
		}
		else{
			countSpace = 0;
		}		
	}
	//no spaces available
	return -1;	
}

/**
 * Find the next index in memory that has enough space for the process
 */
int findNextMemoryIndex(int sizeNeeded, char* memory, int fromIndex)
{
	int countSpace = 0;
	int i;
	
	printf("Required size %d\n", sizeNeeded);

	//find memory space between fromIndex and MEMORY_SIZE
	for (i = fromIndex; i < MEMORY_SIZE; i++)
	{
		if(memory[i] == '.'){
			countSpace++;
			if (countSpace == sizeNeeded){
				return i - sizeNeeded + 1;
			}
		}
		else{
			countSpace = 0;
		}		
	}

	countSpace = 0;
	//find memory space between 0 and fromIndex - 1
	for (i = 0; i < fromIndex; i++)
	{
		if(memory[i] == '.'){
			countSpace++;
			if (countSpace == sizeNeeded){
				return i - sizeNeeded + 1;
			}
		}
		else{
			countSpace = 0;
		}		
	}

	//no spaces currently available
	return -1;	
}

/**
 * Find the index in memory that best fits the process
 */
int findBestMemoryIndex(int sizeNeeded, char* memory)
{
	int countSpace = 0;
	int bestFit = 999;
	int bestFitIndex = 0;
	int i = 0;
	
	while(i <= MEMORY_SIZE)
	{
		if(memory[i] == '.')
		{
			countSpace++;
		}
		else
		{
			if(countSpace == sizeNeeded){
				return i - sizeNeeded;
			}
			else if(countSpace >= sizeNeeded && countSpace < bestFit){
				bestFit = countSpace;
				bestFitIndex = i;
			}
			countSpace = 0;
		}
		i++;
	}
	
	if(bestFit == 999) 
	{
		return -1;
	}
	else 
	{
		return bestFitIndex - bestFit;
	}
}

/**
 * Remove Processes whose duration has elasped.
 */
void removeFromMemory(Process* process, char* memory, int numberOfProcesses)
{
	int i, j;
	for(i = 0; i < MEMORY_SIZE; i++)
	{
		for(j = 0; j < numberOfProcesses; j++)
		{
			if(memory[i] == process[j].pid){
				if(process[j].duration == process[j].waitTime){
					memory[i] = '.';
				}
			}
		}
	}
}

int getSwapCount()
{
	return swappedIn;
}