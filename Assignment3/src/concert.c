/*
 * concert.c
 *
 * Represents the concert hall-- data on which seats are taken,
 * and on how many tickets are left.
 */

#include <stdlib.h>
#include <stdbool.h>

#define SEAT_WIDTH 10
#define SEAT_HEIGHT 10

const int SEATS_ACROSS = SEAT_WIDTH;
const int SEAT_ROWS = SEAT_HEIGHT;

typedef struct {
    int tickets;
    bool (*seats)[SEAT_WIDTH];
} Concert;

Concert* concert;

Concert* newConcert()
{
    Concert* newConcert = (Concert*) malloc(sizeof(Concert));
    (*newConcert).tickets = SEATS_ACROSS * SEAT_ROWS;
    printf("%d!\n", (*newConcert).tickets);
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

void setConcert(Concert* c)
{
    printf("%d!\n", getTicketCount(c));
    concert = c;
}

Concert* getConcert()
{
    return concert;
}

bool isFinished(Concert* c)
{
    return getTicketCount(c) <= 0;
}

int getTicketCount(Concert* c)
{
    return (*c).tickets;
}

