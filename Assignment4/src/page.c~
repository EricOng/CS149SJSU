#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define PAGE_SIZE 10

typedef struct {
	bool inMemory;
	int pid;
	int size;
	int lastRef;
} Page;

Page createPage(int index)
{
	Page* p = (Page*) malloc(sizeof(Page));
	(*p).inMemory = false;
	(*p).pid = (65 + index);
	(*p).size = PAGE_SIZE;
	(*p).lastRef = 999;
	return *p;
}

Page* initializePages(int size, bool create)
{
	Page* book = (Page*) malloc(size * sizeof(Page));
	if(create){	
		int i = 0;
		while(i < size)
		{
			book[i] = createPage(i);
			i++;
		}
	}	
	return book;
}

void removeFirstPage(Page* memory, Page* pages, int memSize)
{
	printf("Removed page %d        Pages:  |%d|%d|%d \n", memory[0].pid, memory[1].pid, memory[2].pid, memory[3].pid);
	int i;
	for(i = 0; i < 10; i++)
	{
		if(memory[0].pid == pages[i].pid)
		{			
			pages[i].inMemory = false;
			break;		
		}
	}	
	int count = 0;
	while(count != memSize)
	{
		if(count + 1 < memSize)
		{	
			memory[count] = memory[count + 1];
		}
		count++;
	}
}

int removeLRUPage(Page* memory, Page* pages, int memSize)
{
	int i = 0;
	int lruIndex = 5, lruValue = 101;
	
	while(i < memSize)
	{
		if(memory[i].lastRef < lruValue)
		{
			lruValue = memory[i].lastRef;
			lruIndex = i;
		}
		i++;
	}	
		
	printf("Removed page %c, LRU: %d\n", memory[lruIndex].pid, memory[lruIndex].lastRef);
	
	for(i = 0; i < 10; i++)
	{
		if(memory[lruIndex].pid == pages[i].pid)
		{			
			pages[i].inMemory = false;
			break;		
		}
	}
	return lruIndex;
}

bool addToMemory(Page* memory, Page* page, int memSize, int cIndex, int pIndex)
{
	if(!page[pIndex].inMemory)
	{	
		int i;
		if(cIndex < memSize)
		{
			memory[cIndex] = page[pIndex];
			page[pIndex].inMemory = true;
			printf("Adding  page %d\n", page[pIndex].pid);
		}
		else{
			removeFirstPage(memory, page, memSize);
			memory[memSize-1] = page[pIndex];	
			page[pIndex].inMemory = true;
			printf("Adding  page %d\n", page[pIndex].pid);
		}
		return true;
	}
	return false;
}

int findPID(Page* memory, char pagePID)
{
	int i;	
	for(i = 0; i < 4; i++)
	{
		if(memory[i].pid == pagePID)
		{			
			return i;
		}
	}
	return -1;
}

bool addToLRUMemory(Page* memory, Page* page, int memSize, int cIndex, int pIndex, int lastref)
{
	if(!page[pIndex].inMemory)
	{	
		int lru;
		if(cIndex < memSize)
		{
			memory[cIndex] = page[pIndex];
			memory[cIndex].lastRef = lastref;
			page[pIndex].inMemory = true;
		}
		else{
			lru = removeLRUPage(memory, page, memSize);
			memory[lru] = page[pIndex];
			memory[lru].lastRef = lastref;
			page[pIndex].inMemory = true;
		}
		return true;
	}
	memory[findPID(memory,page[pIndex].pid)].lastRef = lastref;
	return false;
}
