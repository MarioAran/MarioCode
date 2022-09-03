#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appData_init(tAppData *object);

/* Load the application data from file */
void appData_load(tAppData *object, tError *error);

/* Save the application data to a file */
void appData_save(tAppData object, tError *error);

/* Allow to assign a path to the application data */
void appData_setPath(tAppData *object, const char *path);

/* 
 * API - Entities management (planes, passengers and flights)
 */

/* Return a table with the passengers */
void getPassengers(tAppData object, tPassengerTable *result);

/* Get the passenger information */
void getPassenger(tAppData object, tPassengerId passengerId, tPassenger *passenger, tError *retVal);

/* Add a new passenger */
void addPassenger(tAppData *object, tPassenger passenger, tError *retVal);

/* Remove a certain passenger */
void removePassenger(tAppData *object, tPassenger passenger);

/* Return the table of planes */
void getPlanes(tAppData object, tPlaneTable *result);

/* Get the plane information */
void getPlane(tAppData object, tPlaneId planeId, tPlane *plane, tError *retVal);

/* Add a new plane */
void addPlane(tAppData *object, tPlane plane, tError *retVal);

/* Return the table of flights */
void getFlights(tAppData object, tFlightTable *result);

/* Get the flight information */
void getFlight(tAppData object, tFlightId id, tFlight *flight, tError *retVal);

/* Add a new flight */
void addFlight(tAppData *object, tFlight flight, tError *retVal);

/* 
 * API - Flight processment
 */

/* Checks a flight data */
void checkData(tFlight flight, tPassengerTable passengers, tPlaneTable planes, tError *retVal );

/* Gets the threshold rows for priority, front and back plane rows */
void getThresholdRows( int totalSeats, int *max_priority_row, int *max_front_row, int *max_back_row);

/* Assigns a suitable seat to a passenger according to its booking. This action return a boarding card
   and updates counters for priority seats, front seat and back seats. */
void assignSeat( tBooking booking, tBoarding *card, int totalSeats,
                 int maxPriorityRow, int maxFrontRow, int maxBackRow,
                 int *seatsPriority, int *seatsFront, int *seatsBack );

/* Proceeds with the checkin process for the given flight */
void checkinFlight(tFlight *flight, tPlane plane, tError *retVal );

/* Accomodates a passenger with the given boarding card into the plane */
void accomodatePassenger( tPlane *plane, tBoarding boarding, tError *retVal );

/* Proceeds with the boarding process of the given flight */
void boardFlight(tFlight *flight, tPassengerTable *passengers, tPlane *plane, tError *retVal );

/* Closes a flight */
void closeFlight( tFlight *flight );

/* Assign a boarding gate to a flight */
void assignBoardingGate( tFlight *flight );

/* Prepares a plane for the boarding process */
void setUpPlane( tPlane *plane );

/* Processes an individual flight */
void processFlight(tFlight *flight, tPassengerTable *passengers, tPlaneTable *planes, tError *retVal );

/* Looks for the next flight between two given locations in the table of flights, beginning at the startIndex position */
int searchNextFlight( tFlightTable flights, tAirport origin, tAirport destination, int startIndex );

/* Reallocates overbooked passengers of a flight into the booking list of another flight */
void reallocatePassengers( tBoardingQueue *queue, tBookingList *list, tPassengerTable *passengers );

/* Processes all flights of the company */
void processAllFlights(tAppData *object, tError *retVal );
