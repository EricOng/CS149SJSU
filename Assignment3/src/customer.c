/*
 * customer.c
 *
 * Contains functions related to the concert's customers;
 * creates new customer threads, who then buy tickets
 */

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

const int LAST_CUSTOMER_ARRIVAL_TIME = 59;

int customerCounter = 0;

void* customer(void*);

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

void* customer(void* arg)
{
    sleep(1 + rand() % LAST_CUSTOMER_ARRIVAL_TIME);
    int me = customerCounter++;
    int id = *((int*) arg);
    printf("Customer: %2d @ line %d\n", me, id);
}

