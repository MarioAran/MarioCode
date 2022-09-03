#include "data.h"

/* Get a textual representation of a passenger */
void getPassengerStr(tPassenger passenger, int maxSize, char *str);
	
/* Get a passenger object from its textual representation */
void getPassengerObject(const char *str, tPassenger *passenger);

/* Compare two dates */
int date_cmp( tDate d1, tDate d2 );

/* Copy the date in src to dst */
void date_cpy( tDate *dst, tDate src );

/* Compare two passengers */
int passenger_cmp(tPassenger passenger1, tPassenger passenger2);

/* Copy the passenger data in src to dst*/
void passenger_cpy(tPassenger *dst, tPassenger src);

/* Initialize the table of passengers */
void passengerTable_init(tPassengerTable *table);

/* Add a new passenger to the table of passengers */
void passengerTable_add(tPassengerTable *table, tPassenger passenger, tError *retVal);

/* Find a passenger in the table and returns its position */
int passengerTable_find(tPassengerTable table, tPassengerId id);

/* Remove the first occurence of a passenger in the table */
void passengerTable_del(tPassengerTable *table, tPassenger passenger);

/* Load the table of passengers from a file */
void passengerTable_load(tPassengerTable *table, const char* filename, tError *retVal);

/* Save a table of passengers to a file */
void passengerTable_save(tPassengerTable table, const char* filename, tError *retVal);
    
/* Filter all passengers from the given country */
void passengerTable_filterByCountry(tPassengerTable table, tCountry country, tPassengerTable *result);

/* Filter all passengers with a birthdate within the specified interval */
void passengerTable_filterByBirthDateInterval(tPassengerTable tabPassenger, tDate minAge, tDate maxAge, tPassengerTable *result);

/* Gets the number of passengers holding a customer card*/
int passengerTable_getNumberOfCardHolders(tPassengerTable tabPassenger);

/* Gets the maximum amount of fidelity points of a passenger */
float passengerTable_getMaxFidelityPoints(tPassengerTable tabPassenger);
