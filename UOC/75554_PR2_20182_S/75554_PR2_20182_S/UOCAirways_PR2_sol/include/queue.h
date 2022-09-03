#include "data.h"

void boardingQueue_create( tBoardingQueue *queue );
tBoarding boardingQueue_head(tBoardingQueue queue);
tBoolean boardingQueue_empty(tBoardingQueue queue);
tBoolean boardingQueue_full(tBoardingQueue queue);
int  boardingQueue_length(tBoardingQueue queue);
void boardingQueue_enqueue(tBoardingQueue *queue, tBoarding newElement);
void boardingQueue_dequeue(tBoardingQueue *queue);
void boardingQueue_cpy(tBoardingQueue *dst, tBoardingQueue src);
int  boardingQueue_cmp(tBoardingQueue q1, tBoardingQueue q2);
void boardingQueue_save(tBoardingQueue tabBoardings, const char* filename, tError *retVal);
void boardingQueue_load(tBoardingQueue *tabBoardings, const char* filename, tError *retVal);
void getBoardingQueueStr( tBoardingQueue queue, int maxSize, char *str);
void getBoardingQueueObject(const char *str, tBoardingQueue *queue) ;
 
