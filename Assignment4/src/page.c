#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define PAGES_ON_DISK 10
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

Page* initializePages()
{
	Page* book = (Page*) malloc(PAGES_ON_DISK * sizeof(Page));
	int i = 0;
	while(i < PAGES_ON_DISK)
	{
		book[i] = createPage(i);
		i++;
	}
	return book;
}
