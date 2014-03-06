#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define PAGE_SIZE 10

typedef struct {
	bool inMemory;
	char pid;
	int size;
} Page;

Page createPage(int index)
{
	Page* p = (Page*) malloc(sizeof(Page));
	(*p).inMemory = false;
	(*p).pid = (65 + index);
	(*p).size = PAGE_SIZE;
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
	printf("Removed page %c        Pages:  |%c|%c|%c \n", memory[0].pid, memory[1].pid, memory[2].pid, memory[3].pid);
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

bool addToMemory(Page* memory, Page* page, int memSize, int cIndex, int pIndex)
{
	if(!page[pIndex].inMemory)
	{	
		int i;
		if(cIndex < memSize)
		{
			memory[cIndex] = page[pIndex];
			page[pIndex].inMemory = true;
		}
		else{
			removeFirstPage(memory, page, memSize);
			memory[memSize-1] = page[pIndex];	
			page[pIndex].inMemory = true;
		}
		return true;
	}
	return false;
}

