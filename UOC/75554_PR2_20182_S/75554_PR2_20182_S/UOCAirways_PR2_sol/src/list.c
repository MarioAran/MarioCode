#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int booking_cmp( tBooking b1, tBooking b2 )
{
    int result;
    
    if (b1.passenger == b2.passenger) {
        if (b1.priority == b2.priority)
            result= 0;
        else {
            if (b1.priority < b2.priority)
                result= -1;
            else
                result= 1;
        }
    } else {
        if (b1.passenger < b2.passenger)
            result= -1;
        else 
            result= 1;
    }
    
    return result;
}

void booking_cpy( tBooking *dst, tBooking src )
{
    dst->passenger= src.passenger;
    dst->priority= src.priority;
}

void bookingList_create(tBookingList *list) 
{
    list->nElem= 0;
}

tBoolean bookingList_empty(tBookingList list) {
    
    tBoolean empty;
    
	empty= (list.nElem == 0);
    
    return empty;
}

tBoolean bookingList_full(tBookingList list) {

    tBoolean full= FALSE;

	full= (list.nElem == MAX_BOOKINGS);

    return full;
}

tError bookingList_insert(tBookingList *list, tBooking newElement, int index) {

	tError retVal= OK;

    int i;

	if (list->nElem == MAX_BOOKINGS)
			retVal= ERR_MEMORY;
	else {
		if (index < 1 || index > list->nElem+1)
			retVal= ERR_INVALID_DATA;
		else {
			index--;
			for (i=list->nElem-1; i>= index; i--)
				 booking_cpy( &(list->table[i+1]), list->table[i]);
			list->nElem++;
			booking_cpy( &(list->table[index]), newElement );
		}
	}	
	
	return retVal;
}

tError bookingList_delete(tBookingList *list, int index) 
{
	tError retVal= OK;

	int i;
	
	if (list->nElem==0)
		retVal= ERROR;
	else {
		if (index < 1 || index > list->nElem)
			retVal= ERR_INVALID_DATA;
		else {
			index--;
			for (i=index; i<list->nElem-1; i++)
				 booking_cpy( &(list->table[i]), list->table[i+1] );
			list->nElem--;
		}
	}
	
	return retVal;
}

tError bookingList_get(tBookingList list, int index, tBooking *elem) {
	tError retVal= OK;

	if (list.nElem==0)
		retVal= ERROR;
	else {
		if (index < 1 || index > list.nElem)
			retVal= ERR_INVALID_DATA;
		else {
			index--;
			booking_cpy( elem, list.table[index] );
		}
	}

	return retVal;
}

tBoolean bookingList_end(tBookingList list, int index) {
    
    tBoolean end;
    
	end= (index-1 >= list.nElem);

    return end;
}

tError bookingList_replace(tBookingList *list, int index, tBooking elem) {
	tError retVal= OK;

	if (list->nElem==0)
		retVal= ERROR;
	else {
		if (index < 1 || index > list->nElem)
			retVal= ERR_INVALID_DATA;
		else {
			index--;
			booking_cpy( &(list->table[index]), elem );
		}
	}

	return retVal;
}

unsigned int bookingList_length(tBookingList list) {
    
    unsigned int nElements= 0;
    
    nElements= list.nElem;

    return nElements;
}

int bookingList_cmp( tBookingList b1, tBookingList b2 )
{
    int i;
    int result= 0;
    
    if (b1.nElem < b2.nElem)
        result= -1;
    else if (b1.nElem > b2.nElem)
        result= 1;
    else {
        i= 0;
        while (i < b1.nElem && result == 0) {
            result= booking_cmp(b1.table[i], b2.table[i]);
            i++;
        }
    }
    
    return result;
}

void bookingList_cpy( tBookingList *dst, tBookingList src )
{
    int i;
    
    dst->nElem= src.nElem;
    for (i=0; i< src.nElem; i++)
        booking_cpy(&dst->table[i], src.table[i]);
}
