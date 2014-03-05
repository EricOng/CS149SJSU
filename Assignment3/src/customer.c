/*
 * customer.c
 *
 * Contains functions related to the concert's customers;
 * creates new customer threads, who then buy tickets
 */

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>



