#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void boarding_cpy( tBoarding *dst, tBoarding src )
{
    dst->passengerId= src.passengerId;
    dst->row= src.row;
    dst->seat= src.seat;
}

int boarding_cmp( tBoarding b1, tBoarding b2 )
{
    int result= 0;
    
    if (b1.passengerId < b2.passengerId)
        result= -1;
    else if (b1.passengerId > b2.passengerId)
        result= 1;
    else {
        if (b1.row < b2.row)
            result= -1;
        else if (b1.row > b2.row)
            result= 1;
        else {
            if (b1.seat < b2.seat)
                result= -1;
            else if (b1.seat > b2.seat)
                result= 1;
            else    
                result= 0;
        }
    }
    
    return result;
}

void boardingQueue_create( tBoardingQueue *queue ) {
	queue->nElem=0;
}

tBoarding boardingQueue_head(tBoardingQueue queue) {
	tBoarding head;
	boarding_cpy(&head,queue.table[0]);
	return head;
}

tBoolean boardingQueue_empty(tBoardingQueue queue) {	
	tBoolean empty = TRUE;
	empty = (queue.nElem==0);
	return empty;
}

tBoolean boardingQueue_full(tBoardingQueue queue) {	
	tBoolean full = FALSE;
	full = (queue.nElem==MAX_BOARDING);
	return full;
}

int boardingQueue_length(tBoardingQueue queue)
{
    return queue.nElem;
}

void boardingQueue_enqueue(tBoardingQueue *queue, tBoarding newElement) {

	boarding_cpy(&(queue->table[queue->nElem]),newElement);
	queue->nElem++;

}

void boardingQueue_dequeue (tBoardingQueue *queue) {
	
	unsigned int i=0;
	
	for (i=0; i<queue->nElem-1; i++) {
		boarding_cpy(&(queue->table[i]),queue->table[i+1]);
	}
	queue->nElem--;
}

void boardingQueue_cpy(tBoardingQueue *dst, tBoardingQueue src)
{    
    boardingQueue_create(dst);
    while (!boardingQueue_empty(src)) {
            boardingQueue_enqueue(dst, boardingQueue_head(src));
            boardingQueue_dequeue(&src);
    }
}

int boardingQueue_cmp(tBoardingQueue q1, tBoardingQueue q2)
{
    int result;
    
    result= 0;
    
    if (boardingQueue_length(q1) < boardingQueue_length(q2))
        result= -1;
    else if (boardingQueue_length(q1) > boardingQueue_length(q2))
        result= 1;
    else {
        while (!boardingQueue_empty(q1) && result==0) {
                result= boarding_cmp(boardingQueue_head(q1), boardingQueue_head(q2));
                boardingQueue_dequeue(&q1);
                boardingQueue_dequeue(&q2);
        }            
    }
    
    return result;
}
    
void getBoardingStr( tBoarding boarding, int maxSize, char *str )
{
    int length;

    /* write it as a string */
    length= snprintf(str, maxSize-1, "%d %d %d", 
            boarding.passengerId, boarding.row, boarding.seat);
            
    if (length>0) 
        str[length]='\0';
} 

void getBoardingObject(const char *str, tBoarding *boarding) 
{
	int aux_passenger_id;
    
    /* read the loaded train as a string*/
    sscanf(str, "%d %d %c", &aux_passenger_id, &boarding->row, &boarding->seat); 
    boarding->passengerId= (tPassengerId)(aux_passenger_id);
}

/* The content of the fields of the queue structure is written into the string str */
void getBoardingQueueStr( tBoardingQueue queue, int maxSize, char *str) 
{
    int length;
	tBoarding boarding;
    char tempStr[MAX_LINE];    

    /* write the size of the stack */
    length= snprintf(str, maxSize-1, "%d", boardingQueue_length(queue));
 	if (length>0) 
		str[length]='\0';

    while(!boardingQueue_empty(queue))
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);

        /* get the top of the stack */
        boarding = boardingQueue_head(queue);

        /* write it as a string */
        getBoardingStr(boarding, maxSize, str);

        /* dequeue the head element to allow writting of next element */
        boardingQueue_dequeue(&queue);
    }

 	if (length>0) 
		str[length]='\0';
}


/* The content of the string str is parsed into the fields of the queue structure */
void getBoardingQueueObject(const char *str, tBoardingQueue *queue) 
{
	int i, size, aux_passenger_id;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   
	tBoarding newBoarding;

    /* read queue size */
    sscanf(str, "%d %[^\n]s", &size, tempStr); 

    /* Initialize the quaue */
    boardingQueue_create(queue);

    for (i= 0; i< size; i++)
    {
        /* read the loaded train as a string*/
        sscanf(tempStr, "%d %d %c %[^\n]s", &aux_passenger_id, &newBoarding.row, &newBoarding.seat, nextStr); 
        newBoarding.passengerId= (tPassengerId)(aux_passenger_id);

        /* enqueue it on the queue */
        boardingQueue_enqueue( queue, newBoarding );

        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}

void boardingQueue_save(tBoardingQueue queue, const char* filename, tError *retVal) {

	*retVal = OK;
	FILE *fout=0;
	char str[MAX_LINE];
	tBoarding req;
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {

		/* Save all boardings to the file */
		while(!boardingQueue_empty(queue)){
			req = boardingQueue_head(queue);
			getBoardingStr(req, MAX_LINE, str);
			fprintf(fout, "%s\n", str);
			boardingQueue_dequeue(&queue);
		}
           
        /* Close the file */
		fclose(fout);
	} 
}

void boardingQueue_load(tBoardingQueue *queue, const char* filename, tError *retVal) {
	
	*retVal = OK;
	
	FILE *fin=0;
	char line[MAX_LINE];
	tBoarding newBoarding;
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

	/* Initialize the queue */
		boardingQueue_create(queue);

		/* Read all the lines (boardings) */
		while(!feof(fin) && !boardingQueue_full(*queue)) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getBoardingObject(line, &newBoarding);
				/* Add the new boarding to the queue */
				boardingQueue_enqueue(queue, newBoarding);		
			}
		}

		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}
