#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "page.c"

#define PAGE_FRAMES 4
#define PAGES_ON_DISK 10
#define PAGE_REFERENCES 100

int createReference()
{
	int get = rand() % 9;
	int* refNum = (int*) malloc(sizeof(int));
	if(get < 7)
	{
		*refNum = (-1) + (rand() % 2);
		return *refNum;
	}
	else if(get >= 7)
	{
		*refNum = 2 + (rand() % 7);
		return *refNum;
	}
}

int* generateReferences()
{
	int* queue = (int*) malloc(PAGE_REFERENCES * sizeof(int));
	int i = 0;
	while(i < PAGE_REFERENCES)
	{
		queue[i] = createReference();
		i++;	
	}	
	return queue;
}

void printPages(Page* inMemory, Page* disk, int rIndex)
{
	printf("= Pages: [%c|%c|%c|%c]\n", inMemory[0].pid,inMemory[1].pid,inMemory[2].pid,inMemory[3].pid);
}

int main()
{
	Page* physicalMemory = initializePages(PAGE_FRAMES, false);
	Page* diskPages = initializePages(PAGES_ON_DISK, true);
	srand(time(0));
	int* referenceQueue = generateReferences();	
	
	int mIndex = 0;
	int pIndex = 0;
	int count = 0, hitCount = 0;
	while(count != PAGE_REFERENCES)
	{
		pIndex = (pIndex + referenceQueue[count]);
		if(pIndex == -1){
			pIndex = 9;
		}
		else if(pIndex > 10){
			pIndex = pIndex - 11;
		}
		else if(pIndex == 10){
			pIndex = 0;
		}
		
		printf("0 Called page %c\n", diskPages[pIndex].pid);
		if(addToRandomMemory(physicalMemory, diskPages, PAGE_FRAMES, mIndex, pIndex, count))
		{
			mIndex++;
		}
		else{
			hitCount++;
		}	
		printPages(physicalMemory, diskPages, pIndex);		
		count++;
	}
	printf("----------------------------\n");
	printf("% Hit Ratio: %d\n", hitCount);
}