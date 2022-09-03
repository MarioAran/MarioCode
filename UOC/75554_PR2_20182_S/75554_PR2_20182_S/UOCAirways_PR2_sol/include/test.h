/* Run all the test set */
#include "data.h"
#include "api.h"

/* Runs the applications tests */
void runTests();

/* Runs the applications tests corresponding to PR2 */
void runTestsPR2(int* totalTest, int* passedTest);

/* Tests all data of a flight is correct */
void test_data_checking(int *totalTest, int *passedTest);
 
/* Tests the process of checkin is correct */
void test_flight_checkin(int *totalTest, int *passedTest);

/* Tests the process of boarding is correct */
void test_flight_boarding(int *totalTest, int *passedTest);

/* Tests the process of overbooking treatment is correct */
void test_flight_overbooking(int *totalTest, int *passedTest);
