#include "data.h"

/* Get a textual representation of a flight */
void getFlightStr(tFlight flight, int maxSize, char *str);

/* Get a flight object from its textual representation */
void getFlightObject(const char *str, tFlight *flight);

/* Get a textual representation of a booking list */
void getBookingStr(tBookingList bookings, int maxSize, char *str);

/* Get a booking list object from its textual representation */
void getBookingObject(const char *str, tBookingList *bookings);

/* Compare two times */
int time_cmp( tTime t1, tTime t2 );

/* Copy the time in src to dst */
void time_cpy( tTime *dst, tTime src );

/* Copy the flight data in src to dst*/
void flight_cpy(tFlight *dst, tFlight src);

/* Compares the flight data of p1 and p2*/
int flight_cmp(tFlight p1, tFlight p2);

/* Initializes the given flights table */
void flightsTable_init(tFlightTable *flightsTable);

/* Add a new flight to the table of flights */
void flightsTable_add(tFlightTable *tabFlights, tFlight flight, tError *retVal);

/* Find a flight in the table */
int flightsTable_find(tFlightTable tabFlights, tFlightId id);

/* Load the table of flights from a file */
void flightsTable_load(tFlightTable *tabFlights, const char* filename, tError *retVal);

/* Save a table of flights to a file */
void flightsTable_save(tFlightTable tabFlights, const char* filename, tError *retVal);

