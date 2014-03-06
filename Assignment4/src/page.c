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
	int accessCount;
} Page;

Page createPage(int index)
{
	Page* p = (Page*) malloc(sizeof(Page));
	(*p).inMemory = false;
	(*p).pid = (65 + index);
	(*p).size = PAGE_SIZE;
	(*p).lastRef = 999;
	(*p).accessCount = 0;
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

int findLFU(Page* memory, int memSize)
{
	int i;
	int lfu = memory[0].accessCount;
	int lfu_index = 0;
	for(i = 0; i < memSize; i++)
	{
		printf("page %d has freq %d\n", memory[i].pid, memory[i].accessCount);
		if(memory[i].accessCount <= lfu)
		{
			lfu = memory[i].accessCount;
			lfu_index = i;
		}
	}
	printf("Least freq page %d \n", memory[lfu_index].pid);
	return lfu_index;
}
int findMFU(Page* memory, int memSize)
{
	int i;
	int lfu = memory[0].accessCount;
	int lfu_index = 0;
	for(i = 0; i < memSize; i++)
	{
		printf("page %d has freq %d\n", memory[i].pid, memory[i].accessCount);
		if(memory[i].accessCount >= lfu)
		{
			lfu = memory[i].accessCount;
			lfu_index = i;
		}
	}
	printf("Most freq page %d \n", memory[lfu_index].pid);
	return lfu_index;
}

void removeLFUPage(Page* memory, Page* pages, int memSize)
{
	int i;
	int lfu_Index = findLFU(memory, memSize);
	for(i = 0; i < 10; i++)
	{
		if(memory[lfu_Index].pid == pages[i].pid)
		{			
			pages[i].inMemory = false;
			break;		
		}
	}	
	printf("Removed page %d\n", memory[lfu_Index].pid);
	int count = lfu_Index;
	while(count != memSize)
	{
		if(count + 1 < memSize)
		{	
			memory[count] = memory[count + 1];
		}
		count++;
	}
}

void removeMFUPage(Page* memory, Page* pages, int memSize)
{
	int i;
	int mfu_Index = findMFU(memory, memSize);
	for(i = 0; i < 10; i++)
	{
		if(memory[mfu_Index].pid == pages[i].pid)
		{			
			pages[i].inMemory = false;
			break;		
		}
	}	
	printf("Removed page %d\n", memory[mfu_Index].pid);
	int count = mfu_Index;
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

bool addToLFUMemory(Page* memory, Page* page, int memSize, int cIndex, int pIndex)
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
			removeLFUPage(memory, page, memSize);
			memory[memSize-1] = page[pIndex];	
			page[pIndex].inMemory = true;
			printf("Adding  page %d\n", page[pIndex].pid);
		}
		return true;
	}
	else{
		int i;
		int j;
		
		for(j = 0;j < memSize; j++)
		{
			if(memory[j].pid == page[pIndex].pid)
			{
				memory[j].accessCount += 1;
				page[pIndex].accessCount += 1;
			}
		}
	}
		printf("Page %d accessed %d -> %d\n", page[pIndex].pid, page[pIndex].accessCount - 1, page[pIndex].accessCount);
	return false;
}

bool addToMFUMemory(Page* memory, Page* page, int memSize, int cIndex, int pIndex)
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
			removeMFUPage(memory, page, memSize);
			memory[memSize-1] = page[pIndex];	
			page[pIndex].inMemory = true;
			printf("Adding  page %d\n", page[pIndex].pid);
		}
		return true;
	}
	else{
		int i;
		int j;
		
		for(j = 0;j < memSize; j++)
		{
			if(memory[j].pid == page[pIndex].pid)
			{
				memory[j].accessCount += 1;
				page[pIndex].accessCount += 1;
			}
		}
	}
		printf("Page %d accessed %d -> %d\n", page[pIndex].pid, page[pIndex].accessCount - 1, page[pIndex].accessCount);
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
