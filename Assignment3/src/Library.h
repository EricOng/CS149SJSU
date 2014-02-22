				//if you guys want to split things up go ahead

typedef struct {
	int waitTime; 		//time that customer has waited (for extra credit)
	int arrivalTime; 	//when the customer arrived
	int seatNum; 		//seat assigned in the 10 x 10 concert seating; Row 1 = 0-9; -1 for unassigned	
	char assignedSeller; 	//TicketSeller customer belongs to
	
}Customer;

typedef stuct {
	char sellerType; 	//quality of tickets seller has; H - high/expensive, M - medium, L - low/cheap
	Customer* customers; 	//queue of customers for this seller
}Seller;

typedef struct {
	bool filled;		//if the seat is filled or not
	int seatNum; 		//id for the seat
}Seat; 

typedef struct {
	Seat* seat; 		//10 x 10 matrix of seats; Row 1 = 0-9
	Seller* sellers; 	//sellers for this concert; 1H, 3M, 6L
}Concert;
