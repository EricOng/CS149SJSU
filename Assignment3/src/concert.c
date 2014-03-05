/*
 * concert.c
 *
 * Represents the concert hall-- data on which seats are taken,
 * and on how many tickets are left.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>

#define SEAT_WIDTH 10
#define SEAT_HEIGHT 10

const int SEATS_ACROSS = SEAT_WIDTH;
const int SEAT_ROWS = SEAT_HEIGHT;

// Concert struct
typedef struct {
    int tickets;               // Total number of tickets yet to be sold
    bool (*seats)[SEAT_WIDTH]; // Record of which seats have been taken
} Concert;

// Global variable; concert singleton
Concert* concert;

time_t startTime;

/**
 * Creates a new concert.
 *
 * @return A pointer to the Concert struct created by this method
 */
Concert* newConcert()
{
    Concert* newConcert = (Concert*) malloc(sizeof(Concert));
    (*newConcert).tickets = SEATS_ACROSS * SEAT_ROWS;
    (*newConcert).seats = malloc(sizeof(bool) * (*newConcert).tickets);
    int i;
    int j;
    for(i = 0; i < SEAT_ROWS; i++) {
        for(j = 0; j < SEATS_ACROSS; j++) {
            (*newConcert).seats[i][j] = false;
        }
    }
    return newConcert;
}

/**
 * Sets the conert singleton
 *
 * @param c A pointer to the Concert struct that should be the new singleton
 */
void setConcert(Concert* c)
{
    concert = c;
    time(&startTime);
}

/**
 * Returns the concert singleton
 *
 * @return A pointer to the current concert singleton
 */
Concert* getConcert()
{
    return concert;
}

/**
 * Determines whether a concert has been sold out.
 * 
 * @param c A pointer to the concert
 *
 * @return true if the concert has no more tickets; false otherwise
 */
bool isFinished(Concert* c)
{
    return getTicketCount(c) <= 0;
}

/**
 * Returns the total number of tickets left in a concert
 *
 * @param c A pointer to the concert
 *
 * @return The number of tickets left to be sold
 */
int getTicketCount(Concert* c)
{
    return (*c).tickets;
}

