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

#define TOTAL_QUEUES 10

// Defines the last time at which a customer might arrive
// Simulation: minutes
//   Realtime: seconds
const int LAST_CUSTOMER_ARRIVAL_TIME = 59;

int customerCounter = 0;
int (*queue)[TOTAL_QUEUES];

pthread_mutex_t queueMutex;

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
    
    pthread_mutex_lock(&queueMutex);
    int i;
    for(i = 0; queue[i][id] != -1; i++) { }
    queue[i][id] = me;
    printf("Customer %2d added to queue %d at position %d\n", me, id, i);
    pthread_mutex_unlock(&queueMutex);
}

void initializeCustomerQueues(int maxCustomers)
{
    pthread_mutex_init(&queueMutex, NULL);
    queue = malloc(sizeof(int) * maxCustomers * TOTAL_QUEUES);
    int i;
    int j;
    for(i = 0; i < maxCustomers; i++) {
        for(j = 0; j < TOTAL_QUEUES; j++) {
            queue[i][j] = -1;
        }
    }
}

