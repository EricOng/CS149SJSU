/*
 * customer.c
 *
 * Contains functions related to the concert's customers;
 * creates new customer threads, who then buy tickets
 */

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// Defines the last time at which a customer might arrive
// Simulation: minutes
//   Realtime: seconds
const int LAST_CUSTOMER_ARRIVAL_TIME = 59;

int customerCounter = 0;

void* customer(void*);
/**
 * Creates a new customer.
 *
 * @param sellerIndex The index of the line to which this customer will go
 * 
 * @return A pointer to the pthread_t thread ID of the customer that was created
 */
pthread_t* newCustomer(int sellerIndex)
{
    pthread_t customerThreadID;
    pthread_attr_t customerAttr;
    pthread_attr_init(&customerAttr);
    int* id = malloc(sizeof(int));
    *id = sellerIndex;
    pthread_create(&customerThreadID, &customerAttr, customer, id);
    return &customerThreadID;
}

/**
 * Callback function for a customer
 */
void* customer(void* arg)
{
    sleep(1 + rand() % LAST_CUSTOMER_ARRIVAL_TIME);
    int me = customerCounter++;
    int id = *((int*) arg);
    printf("Customer: %2d @ line %d\n", me, id);
}

