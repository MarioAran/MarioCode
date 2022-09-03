#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plane.h"

/* The content of the fields of the plane structure is written into the string str */
void getPlaneStr(tPlane plane, int maxSize, char *str) {

    int length;
	
    /* Build the string */	
	length = snprintf(str,maxSize-1,"%d %s %s %s %d %d %.2f %.2f %d %d %d %d", 
             (int)plane.id, plane.plateNumber, plane.producer, plane.model, plane.year,
			 (int)plane.utility, plane.weight, plane.maxSpeed,
			 plane.maxHeight, plane.motors, plane.seats, 
			 (int)plane.isActive);
	if (length>0) 
		str[length]='\0';

}

/* The content of the string str is parsed into the fields of the plane structure */
void getPlaneObject(const char *str, tPlane *plane) {

	int aux_id, aux_utility, aux_active;
 			 
    /* read plane data */
    sscanf(str, "%d %s %s %s %d %d %f %f %d %d %d %d", 
             &aux_id, plane->plateNumber, plane->producer, plane->model, &plane->year, 
			 &aux_utility, &plane->weight, &plane->maxSpeed, 
			 &plane->maxHeight, &plane->motors, &plane->seats, 
			 &aux_active );

    plane->id = (tPlaneId)aux_id;
    plane->utility = (tPlaneUtility)aux_utility;
	plane->isActive = (tBoolean)aux_active;
}

void plane_cpy(tPlane *dst, tPlane src) {

    dst->id = src.id;
    strcpy(dst->plateNumber,src.plateNumber);
	strcpy(dst->producer,src.producer);
	strcpy(dst->model,src.model);
	dst->year = src.year;
	dst->utility = src.utility;
	dst->weight = src.weight;
	dst->maxSpeed = src.maxSpeed;
	dst->maxHeight = src.maxHeight;
	dst->motors = src.motors;
	dst->seats = src.seats;
	dst->isActive = src.isActive;
}

int plane_cmp(tPlane d1, tPlane d2)
{
    int result = 0;
    	
    result= strcmp(d1.producer,d2.producer);
    if (result==0) 
    {
        result= strcmp(d1.model,d2.model);
        if (result==0)
        {
			if (d1.year > d2.year) 
				result = 1;
			else if (d1.year < d2.year)
				result = -1;
			else{
				if (d1.utility > d2.utility)
					result = 1;
				else if (d1.utility < d2.utility)
					result = -1;
				else{
					if (d1.weight > d2.weight)
						result = 1;
					else if (d1.weight < d2.weight)
						result = -1;
					else{
						if (d1.maxSpeed > d2.maxSpeed)
							result = 1;
						else if (d1.maxSpeed < d2.maxSpeed)
							result = -1;
						else{
							if (d1.maxHeight > d2.maxHeight)
								result = 1;
							else if (d1.maxHeight < d2.maxHeight)
								result = -1;
							else{
								if (d1.motors > d2.motors)
									result = 1;
								else if (d1.motors < d2.motors)
									result = -1;
								else{
									if (d1.seats > d2.seats)
										result = 1;
									else if (d1.seats < d2.seats)
										result = -1;
									else{
										if (d1.isActive > d2.isActive)
											result = 1;
										else if (d1.isActive < d2.isActive)
											result = -1;
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

void init_occupied_seats( tPlane *plane )
{
    int row, seat, max_rows;
        
    max_rows= plane->seats / MAX_SEATS_PER_ROW;
    /* set 'no passenger' in all of the plane seats */
    for (row= 0; row < max_rows; row++)
        for (seat= 0; seat < MAX_SEATS_PER_ROW; seat++) 
             plane->layout[row][seat]= NO_PASSENGER;
    
    /* reset plane passengers count to zero */
    plane->occupiedSeats= 0;    
}

void print_occupied_seats( tPlane plane )
{
    int row, seat, max_rows;
        
    max_rows= plane.seats / MAX_SEATS_PER_ROW;
    /* set 'no passenger' in all of the plane seats */
    for (row= 0; row < max_rows; row++)
        for (seat= 0; seat < MAX_SEATS_PER_ROW; seat++) 
            if (plane.layout[row][seat] != NO_PASSENGER)
                printf("Passenger: %d - Seat: %d%c\n", plane.layout[row][seat], row+1, (int)'A' + seat);
}

void planesTable_init(tPlaneTable *planesTable) 
{	
	planesTable->nPlanes= 0;
}

void planesTable_add(tPlaneTable *tabPlanes, tPlane plane, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new plane */
	if(tabPlanes->nPlanes>=MAX_PLANES)
		*retVal = ERR_MEMORY;
		

	if (*retVal == OK) {
		/* Add the new plane to the end of the table */
		plane_cpy(&tabPlanes->table[tabPlanes->nPlanes],plane);
		tabPlanes->nPlanes++;
	}
	
}

int planesTable_find(tPlaneTable tabPlanes, tPlaneId id) {

	int idx = NO_PLANE;
	
	int i=0;
	while(i< tabPlanes.nPlanes && idx==NO_PLANE) {
		/* Check if the id is the same */
		if(id==tabPlanes.table[i].id)  {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

void planesTable_save(tPlaneTable tabPlanes, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all passengers to the file */
        for(i=0;i<tabPlanes.nPlanes;i++) {
            getPlaneStr(tabPlanes.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void planesTable_load(tPlaneTable *tabPlanes, const char* filename, tError *retVal) {
	
	*retVal = OK;

	FILE *fin=0;
	char line[MAX_LINE];
	tPlane newPlane;
	
	/* Initialize the output table */
	planesTable_init(tabPlanes);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the planes */
		while(!feof(fin) && tabPlanes->nPlanes<MAX_PLANES) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getPlaneObject(line, &newPlane);
				/* Add the new plane to the output table */
				planesTable_add(tabPlanes, newPlane, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

void planesTable_filterByUtility(tPlaneTable tabPlanes, tPlaneUtility utility, tPlaneTable *result) {

	tError retVal;
	int i;
	planesTable_init(result);
	for(i=0;i<tabPlanes.nPlanes;i++) {
		if (utility == tabPlanes.table[i].utility){
			planesTable_add(result, tabPlanes.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabPlanes which cannot have more than MAX_PLANES*/
		}
	}

}

void planesTable_getActivePlanes(tPlaneTable tabPlanes, tPlaneTable *result) {

	tError retVal;
	int i;
	planesTable_init(result);
	for(i=0;i<tabPlanes.nPlanes;i++) {
		if (tabPlanes.table[i].isActive){
			planesTable_add(result, tabPlanes.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabPlanes which cannot have more than MAX_PLANES*/
		}
	}
}

float planeTable_getAverageCapacityByUtility(tPlaneTable tabPlane, tPlaneUtility utility) {

	float avgSeats = 0.0;

	int numPlaneProp=0, i;
	int sumSeats = 0;
	
	for(i=0;i<tabPlane.nPlanes;i++) {
		if (tabPlane.table[i].utility==utility){
			sumSeats += tabPlane.table[i].seats;			
			numPlaneProp++;
		}
	}
	if (numPlaneProp>0)
		avgSeats = (float)sumSeats / (float)numPlaneProp;

	return avgSeats;
}

int planeTable_getMaxPlaneHeight(tPlaneTable tabPlane){

	int maxHeight = 0;
	
	int i;
	
	for(i=0;i<tabPlane.nPlanes;i++) {
		if (tabPlane.table[i].maxHeight > maxHeight){
			maxHeight = tabPlane.table[i].maxHeight;
		}
	}

	return maxHeight;
}
