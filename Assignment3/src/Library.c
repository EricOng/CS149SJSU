#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/time.h>
#include "Library.h"

Concert makeSeating(){
	Concert* c = (Concert*) malloc(sizeof(Concert));
	(*c).sellers = initialize();
	(*c).seating = arrangeSeats();
}

Seller* initialize(){
	Seller* sellers = (Seller*) malloc(numSellers * sizeof(Seller));
	
}

Seller makeSeller(char type){
	Seller* s = (Seller*) malloc(sizeof(Seller));
	(*s).sellerType = type;
	(*s).customers = getCustomers();
}

	

