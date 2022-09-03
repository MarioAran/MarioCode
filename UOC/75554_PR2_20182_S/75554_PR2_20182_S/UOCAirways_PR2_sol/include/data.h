/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

#define MAX_PLANES 50
#define MAX_PLATE_NUMBER 20+1
#define MAX_PRODUCER_NAME 25+1
#define MAX_MODEL_NAME 15+1

#define MAX_NAME 15+1
#define MAX_SURNAME 25+1
#define MAX_DOC_NUMBER 20+1
#define MAX_COUNTRY_CODE 2+1

#define MAX_PASSENGERS 100
#define MAX_PATHNAME 500
#define MAX_LINE 514
#define NO_PLANE -1
#define NO_PASSENGER -1
#define NO_FLIGHT -1
#define NO_BOARDING_GATE -1
#define NO_ROW -1
#define NO_SEAT '\0'

#define MAX_FLIGHTS 5
#define MAX_AIRPORT_IATA_CODE 3+1
#define MAX_BOARDING 100
#define MAX_BOOKINGS 100

#define PRIORITY_ROW_PERCENT 0.25
#define FRONT_ROW_PERCENT 0.25
#define BACK_ROW_PERCENT 0.5
#define MAX_ROWS 50
#define MAX_SEATS_PER_ROW 6

#define BOARDING_THRESHOLD_1 50
#define BOARDING_THRESHOLD_2 100
#define BOARDING_THRESHOLD_3 200
#define BOARDING_GATE_1 1
#define BOARDING_GATE_2 2
#define BOARDING_GATE_3 3

#define BOARDING_POINTS    100
#define OVERBOOKING_POINTS 200

/* Definition of a boolean type */
typedef enum {FALSE, TRUE} tBoolean;

/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_CANNOT_READ=-1, ERR_CANNOT_WRITE=-2, 
              ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, 
              ERR_ENTRY_NOT_FOUND=-6,
              ERR_NO_PASSENGER=-7,ERR_NO_PLANE=-8,ERR_NO_FREE_GAP=-9,
              ERR_STARTED_FLIGHT} tError;

typedef int tPassengerId;
typedef int tPlaneId;
typedef int tFlightId;

typedef enum {
  COMMERCIAL, PRIVATE, GOVERNMENTAL, MILITAR, EXPERIMENTAL, OTHERS 
} tPlaneUtility;

typedef struct {
    tPlaneId id; 
	char plateNumber[MAX_PLATE_NUMBER]; 
	char producer[MAX_PRODUCER_NAME]; 
	char model[MAX_MODEL_NAME]; 
	int  year; 
	tPlaneUtility utility; 
	float weight; 
	float maxSpeed; 
	int maxHeight; 
	int  motors; 
	int  seats; 
	tBoolean isActive; 
    int occupiedSeats;
    tPassengerId layout[MAX_ROWS][MAX_SEATS_PER_ROW];
} tPlane;

typedef struct {
	tPlane table[MAX_PLANES];
	int nPlanes;
} tPlaneTable;

typedef enum {
  NIF, NIE, PASSPORT, DRIVING_LICENSE, OTHER_DOCUMENTS
} tDocumentType;

typedef struct {
  int day, month, year;
} tDate;

typedef struct {
  int hour, minute;
} tTime;

typedef char tCountry[MAX_COUNTRY_CODE];

typedef struct {
    tPassengerId id;
    char name[MAX_NAME];
    char surname[MAX_SURNAME];	
    tDocumentType docType;
    char docNumber[MAX_DOC_NUMBER];	
    tDate birthDate;
    tCountry countryISOCode;
    tBoolean customerCardHolder;
    int cardNumber;
    int fidelityPoints;
} tPassenger;

typedef struct {
	tPassenger table[MAX_PASSENGERS];
	int nPassengers;
} tPassengerTable;

typedef struct {
    tPassengerId passenger;
    tBoolean priority;
} tBooking;

typedef struct {
	tBooking table[MAX_BOOKINGS];
	unsigned int nElem;
} tBookingList;

typedef char tAirport[MAX_AIRPORT_IATA_CODE];

typedef struct {
    tPassengerId passengerId;
    int row;
    char seat;
} tBoarding;

typedef struct {
	tBoarding table[MAX_BOARDING];
	unsigned int nElem;
} tBoardingQueue;

typedef enum { BOOKING, CHECKIN, BOARDING, CLOSED } tFlightStatus;

typedef struct {
    tFlightId id;
    tAirport originAirport;
    tAirport destinationAirport;
    tDate date;
    tTime time;
    tPlaneId plane;
    int boardingGate;
    tFlightStatus status;
    tBookingList bookings;
    tBoardingQueue priority;
    tBoardingQueue front;
    tBoardingQueue back;
    tBoardingQueue overbooking;
} tFlight;

typedef struct {
    tFlight table[MAX_FLIGHTS];
    int nFlights;
} tFlightTable;

/* Definition of the application data structure */
typedef struct 
{
	/* Path where data will be stored */
	char path[MAX_PATHNAME];
	
	/* Planes table */
	tPlaneTable planes;
	
	/* Passengers table */
	tPassengerTable passengers;
    
	/* Flights table */
    tFlightTable flights;
	
} tAppData;

#endif /*__DATA_H*/