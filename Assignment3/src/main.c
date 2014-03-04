/*
 * The main method for assignment 3.
 * More specific code should be put in separate files
 * and grouped appropriately.
 */

#include <stdio.h>
#include <stdlib.h>
#include "./tools.c"

int main(int argc, char* argv[])
{
    if(argc != 2) // Test for the right number of command-line arguments
    { // If the count is wrong, print a usage mesage instead.
        printf("%s requires ONE command-line argument\n", argv[0]);
        printf("(the number of customers per seller).\n");
        return 0;
    }
    
    // Convert the number of customers passed to the program to an
    // int for later use
    const int NUMBER_OF_CUSTOMERS = atoi(argv[1]);
    
    printf("Proceeding with %d customers per seller.\n", NUMBER_OF_CUSTOMERS);
    
    return 0;
}

