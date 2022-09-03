#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"
#include "list.h"
#include "queue.h"
#include "passenger.h"

/* The content of the fields of the booking structure is written into the string str */
void getBookingStr(tBookingList bookings, int maxSize, char *str) {

    int length, i;
    char tempStr[MAX_LINE];  
    tBooking booking;  

    /* write the size of the list */
    length= snprintf(str, maxSize-1, "%d", bookingList_length(bookings));

 	if (length>0) 
		str[length]='\0';
    
	/* loop the elements of the list of booking writting its elements */
	for(i=1; !bookingList_end(bookings,i); i++) 
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);

        /* get the current booking */
		bookingList_get(bookings, i, &booking);
        
        /* write it as a string */
        length= snprintf(str, maxSize-1, "%s %d %d", tempStr, 
                booking.passenger, booking.priority);

        if (length>0) 
            str[length]='\0';
    }

	if (length>0) 
		str[length]='\0';
}

/* The content of the string str is parsed into the fields of the booking structure */
void getBookingObject(const char *str, tBookingList *bookings) 
{
	int i, size, aux_passenger_id, aux_priority;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   
	tBooking newBooking;

    /* read stack size */
    sscanf(str, "%d %[^\n]s", &size, tempStr); 

    /* Initialize the bookings table */
    bookingList_create(bookings);

    for (i= 1; i<= size; i++)
    {
        /* read the loaded booking as a string*/
        sscanf(tempStr, "%d %d %[^\n]s", &aux_passenger_id, &aux_priority, nextStr); 
        newBooking.passenger= (tPassengerId)(aux_passenger_id);
        newBooking.priority= (tBoolean)(aux_priority);

        /* add the booking to the table */
        bookingList_insert(bookings,newBooking,i);

        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}

/* The content of the fields of the flight structure is written into the string str */
void getFlightStr(tFlight flight, int maxSize, char *str) {

    int length;
	
    /* Build the string */	
	length = snprintf(str,maxSize-1,"%d %s %s %d %d %d %d %d %d %d %d", 
             (int)flight.id, flight.originAirport, flight.destinationAirport, 
             flight.date.day, flight.date.month, flight.date.year, flight.time.hour, flight.time.minute,
			 (int)flight.plane, flight.boardingGate, (int)flight.status);
             
	if (length>0) 
		str[length]='\0';
}

/* The content of the string str is parsed into the fields of the flight structure */
void getFlightObject(const char *str, tFlight *flight) {

	int aux_id, aux_plane, aux_status;
 			 
    /* read flight data */
    sscanf(str, "%d %s %s %d %d %d %d %d %d %d %d", 
        &aux_id, flight->originAirport, flight->destinationAirport, 
        &flight->date.day, &flight->date.month, &flight->date.year, &flight->time.hour, &flight->time.minute, 
        &aux_plane, &flight->boardingGate, &aux_status);

    flight->id = (tFlightId)aux_id;
    flight->plane = (tPlaneId)aux_plane;
    flight->status = (tFlightStatus)aux_status;
    
    bookingList_create( &flight->bookings );
    boardingQueue_create(&flight->priority);
    boardingQueue_create(&flight->front);
    boardingQueue_create(&flight->back);
    boardingQueue_create(&flight->overbooking);
}

int time_cmp( tTime t1, tTime t2 ) {

    int result;
    
    result= 0;

    if (t1.hour > t2.hour)
        result= 1;
    else if (t1.hour < t2.hour)
        result= -1;
    else {
        if (t1.minute > t2.minute)
            result= 1;
        else if (t1.minute < t2.minute)
            result= -1;
    }
    
    return result;
}

void time_cpy( tTime *dst, tTime src ) {
    dst->hour= src.hour;
    dst->minute= src.minute;
}

void flight_cpy(tFlight *dst, tFlight src) 
{
    dst->id= src.id;
    strcpy(dst->originAirport, src.originAirport);
    strcpy(dst->destinationAirport, src.destinationAirport);
    date_cpy(&dst->date, src.date);
    time_cpy(&dst->time, src.time);
    dst->plane= src.plane;
    dst->boardingGate= src.boardingGate;
    dst->status= src.status;
    bookingList_cpy( &dst->bookings, src.bookings );
    boardingQueue_cpy( &dst->priority, src.priority );
    boardingQueue_cpy( &dst->front, src.front );
    boardingQueue_cpy( &dst->back, src.back );
    boardingQueue_cpy( &dst->overbooking, src.overbooking );
}

int flight_cmp(tFlight d1, tFlight d2)
{
    int result = 0;

    if (d1.id > d2.id)
        result= 1;
    else if (d1.id < d2.id)
        result= -1;
    else {
        result= strcmp( d1.originAirport, d2.originAirport );
        if (result == 0) {
            result= strcmp( d1.destinationAirport, d2.destinationAirport );
            if (result == 0) {
                result= date_cmp(d1.date, d2.date);
                if (result==0) {
                    result= time_cmp(d1.time, d2.time);
                    if (result==0) {
                        if (d1.plane > d2.plane)
                            result= 1;
                        else if (d1.plane < d2.plane)
                            result= -1;
                        else {
                            if (d1.boardingGate > d2.boardingGate)
                                result= 1;
                            else if (d1.boardingGate < d2.boardingGate)
                                result= -1;
                            else {
                                if (d1.status > d2.status)
                                    result= 1;
                                else if (d1.status < d2.status)
                                    result= -1;   
                                else {
                                    result= bookingList_cmp(d1.bookings,d2.bookings);
                                    if (result==0) {
                                        result= boardingQueue_cmp(d1.priority,d2.priority);
                                        if (result==0) {
                                            result= boardingQueue_cmp(d1.front,d2.front);
                                            if (result==0) {
                                                result= boardingQueue_cmp(d1.back,d2.back);
                                                if (result==0) {
                                                    result= boardingQueue_cmp(d1.overbooking,d2.overbooking);
                                                }                                        
                                            }                                        
                                        }                                        
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

void flightsTable_init(tFlightTable *flightsTable) {
	
	flightsTable->nFlights= 0;
}

void flightsTable_add(tFlightTable *tabFlights, tFlight flight, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new flight */
	if(tabFlights->nFlights>=MAX_FLIGHTS)
		*retVal = ERR_MEMORY;

	if (*retVal == OK) {
		/* Add the new flight to the end of the table */
		flight_cpy(&tabFlights->table[tabFlights->nFlights],flight);
		tabFlights->nFlights++;
	}
}

int flightsTable_find(tFlightTable tabFlights, tFlightId id) {

	int idx = NO_PLANE;
	
	int i=0;
	while(i< tabFlights.nFlights && idx==NO_PLANE) {
		/* Check if the id is the same */
		if(id==tabFlights.table[i].id)  {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

void flightsTable_save(tFlightTable tabFlights, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save general flight data to the file */
        for(i=0;i<tabFlights.nFlights;i++) {
            getFlightStr(tabFlights.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
        
        /* Save the bookings */
        getBookingStr(tabFlights.table[i].bookings, MAX_LINE, str);
        fprintf(fout, "%s\n", str);
            
        /* Close the file */
        fclose(fout);
	}
}

void flightsTable_load(tFlightTable *tabFlights, const char* filename, tError *retVal) {
	
	*retVal = OK;

	FILE *fin=0;
	char line[MAX_LINE];
	tFlight newFlight;
	
	/* Initialize the output table */
	flightsTable_init(tabFlights);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the flights */
		while(!feof(fin) && tabFlights->nFlights<MAX_FLIGHTS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
                /* Obtain the object */
                getFlightObject(line, &newFlight);
                /* Remove any content from the line */
                line[0] = '\0';
                /* Read one line (maximum 511 chars) and store it in "line" variable */
                fgets(line, MAX_LINE-1, fin);
                /* Ensure that the string is ended by 0*/
                line[MAX_LINE-1]='\0';
                if(strlen(line)>0) {
                    /* get the bookings*/
                    getBookingObject(line,&newFlight.bookings);
                    /* Add the new flight to the output table */
                    flightsTable_add(tabFlights, newFlight, retVal);		
                }
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}
