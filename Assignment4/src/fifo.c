#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "process.c"
#include "page.c"

#define PAGE_FRAMES 4
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
		printf("reference %d gets Num: %d\n", i, queue[i]);
		i++;	
	}	
	return queue;
}

void printPages(Page* inMemory)
{
	
}

int main()
{
	Page* physicalMemory = malloc(PAGE_FRAMES * sizeof(Page));
	Page* diskPages = initializePages();
	srand(time(0));
	int* referenceQueue = generateReferences();	

	

}
