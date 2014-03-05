/*
 * seller.c
 *
 * Contains functions related to the ticket sellers;
 * creates new seller threads to serve customers
 */

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define HIGH 'H'
#define MEDIUM 'M'
#define LOW 'L'

void* highSeller(void*);
void* mediumSeller(void*);
void* lowSeller(void*);

/**
 * Creates a new seller.
 *
 * @param type The type of seller-- either 'H', 'M', or 'L'
 * @param index The index of this particular seller
 *
 * @return A pointer to the pthread_t thread ID created by this method
 */
pthread_t* newSeller(char type, int index)
{
    // Initialize the new thread and its components
    pthread_t sellerThreadID;
    pthread_attr_t sellerAttr;
    pthread_attr_init(&sellerAttr);
    // Prepare an int pointer to be sent to the callback functions
    int* id = malloc(sizeof(int));
    *id = index;
    // Create the pointer with the callback function corresponding
    // to this seller's type
    if(type == HIGH) {
        pthread_create(&sellerThreadID, &sellerAttr, highSeller, id);
    } else if(type == MEDIUM) {
        pthread_create(&sellerThreadID, &sellerAttr, mediumSeller, id);
    } else if(type == LOW) {
        pthread_create(&sellerThreadID, &sellerAttr, lowSeller, id);
    } else {
        return NULL;
    }
    return &sellerThreadID;
}

/**
 * Callback function for a high-priced seller
 */
void* highSeller(void* arg)
{
    int id = *((int *) arg);
}

/**
 * Callback function for a medium-priced seller
 */
void* mediumSeller(void* arg)
{
    int id = *((int*) arg);
}

/**
 * Callback function for a low-priced seller
 */
void* lowSeller(void* arg)
{
    int id = *((int*) arg);
}

