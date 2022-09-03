#include "data.h"

/* Get a textual representation of a plane */
void getPlaneStr(tPlane plane, int maxSize, char *str);

/* Get a plane object from its textual representation */
void getPlaneObject(const char *str, tPlane *plane);

/* Copy the plane data in src to dst*/
void plane_cpy(tPlane *dst, tPlane src);

/* Compares the plane data of p1 and p2*/
int plane_cmp(tPlane p1, tPlane p2);

/* Frees all the occupied seats of a plane */
void init_occupied_seats( tPlane *plane );

/* Prints a textual representation of the occupied seats of a plane */
void print_occupied_seats( tPlane plane );

/* Initializes the given planes table */
void planesTable_init(tPlaneTable *planesTable);

/* Add a new plane to the table of planes */
void planesTable_add(tPlaneTable *tabPlanes, tPlane plane, tError *retVal);

/* Find a plane in the table */
int planesTable_find(tPlaneTable tabPlanes, tPlaneId id);

/* Load the table of planes from a file */
void planesTable_load(tPlaneTable *tabPlanes, const char* filename, tError *retVal);

/* Save a table of planes to a file */
void planesTable_save(tPlaneTable tabPlanes, const char* filename, tError *retVal);

/* Obtain from a table of planes those of a given utility type */
void planesTable_filterByUtility(tPlaneTable tabPlanes, tPlaneUtility utility, tPlaneTable *result);

/* Obtain from a table of planes those that are active */
void planesTable_getActivePlanes(tPlaneTable tabPlanes, tPlaneTable *result);

/* Obtain from a table of planes the average number of seats by utility type */
float planeTable_getAverageCapacityByUtility(tPlaneTable tabPlane, tPlaneUtility utility);

/* Obtain from a table of planes the maximum height of a plane */
int planeTable_getMaxPlaneHeight(tPlaneTable tabPlane);

