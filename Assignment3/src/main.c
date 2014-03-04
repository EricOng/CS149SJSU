/*
 * The main method for assignment 3.
 * More specific code should be put in separate files
 * and grouped appropriately.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("%s requires ONE command-line argument\n", argv[0]);
        printf("(the number of customers per seller).\n");
        return 0;
    }
    
    const int NUMBER_OF_CUSTOMERS = atoi(argv[1]);
    
    printf("Proceeding with %d customers per seller.\n", NUMBER_OF_CUSTOMERS);
    
    return 0;
}

