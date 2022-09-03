#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "passenger.h"
#include "flight.h"
#include "plane.h"
#include "queue.h"
#include "list.h"

#define PLANE1 "1 EC-4567 BOEING 747 1995 0 100.00 750.00 15000 4 180 1"
#define PLANE2 "2 EC-9876 AIRBUS A320 2000 1 120.00 800.00 20000 8 300 1"
#define PLANE3 "3 EC-8273 TUPOLEV 434 1980 1 120.00 800.00 18000 4 24 0"

#define PASSENGER1  "10 LUISA MARTINEZ 0 38908321Y 1980 7 15 ES 1 7814 1000"    
#define PASSENGER2  "20 JOHN DOE 1 44451217G 1976 3 14 UK 1 1234 100"
#define PASSENGER3  "30 PETER WILLIAMS 1 41072140T 1965 2 28 IR 0 0 0"
#define PASSENGER4  "40 JUSTINE LECLERC 1 23169220R 1960 8 20 FR 1 1332 200"
#define PASSENGER5  "50 JUSTINE LEBLANC 1 23169221R 1965 4 22 FR 1 4362 250"
#define PASSENGER6  "60 MARGA ORTIZ 0 70165321W 1975 4 22 ES 0 0 0"
#define PASSENGER7  "70 JUAN AYUSO 0 58908321Y 1974 5 15 CO 1 5002 150"
#define PASSENGER8  "80 JOHN MARTINEZ 0 18908321R 1964 3 15 CO 1 5003 150"
#define PASSENGER9  "90 LUCIA ORTIZ 0 27888221T 1970 5 30 CO 1 1032 250"
#define PASSENGER10 "100 JAMES HILL 0 44227217J 1994 2 7 US 0 0 0"
#define PASSENGER11 "110 OLIVIER MASSOU 0 70165320X 2010 1 28 FR 0 0 0"
#define PASSENGER12 "120 SARA LARSSON 0 58008421Q 1994 2 6 SE 0 0 0"
#define PASSENGER13 "130 MONIQUE LEBLANC 0 18908321S 1990 2 9 FR 0 0 0"

#define FLIGHT1  "100 BCN BIO 23 4 2019 9 30 -1 -1 0"
#define FLIGHT2  "200 BCN MAD 14 5 2019 10 55 1 1 1"
#define FLIGHT3  "300 MAD BCN 14 5 2019 11 55 1 -1 0"
#define FLIGHT4  "400 BCN MAD 14 5 2019 12 55 1 -1 0"

#define BOOKING1 "0"
#define BOOKING2 "3 10 1 20 0 30 1"
#define BOOKING3 "13 10 1 20 1 30 1 40 0 50 0 60 0 70 0 80 0 90 0 100 1 110 1 120 1 130 1"
#define BOOKING4 "29 10 0 11 0 12 0 13 0 14 0 15 0 16 0 17 0 18 0 19 0 20 0 21 0 22 0 23 0 24 0 25 0 26 0 27 0 28 0 29 0 30 0 31 0 32 0 33 0 34 0 35 0 36 0 37 0 38 0"
#define BOOKING5 "5 40 0 50 0 60 1 70 0 80 1"

void runTests() {	
	int passedTestPR2=0;
	int totalTestPR2=0;

	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 2 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR2(&totalTestPR2, &passedTestPR2);

	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");		
	printf("\tPR2: Passed %d of %d [%0.2f%%]\n", passedTestPR2, totalTestPR2, totalTestPR2 > 0 ? (float)passedTestPR2/totalTestPR2*100.0 : 0.0);
	printf("\n\tTotal: Passed %d of %d [%0.2f%%]\n", passedTestPR2, totalTestPR2, 
            totalTestPR2 ? (float)(passedTestPR2)/(totalTestPR2)*100.0 : 0.0);
	printf("===================================\n");		
}

void test_data_checking(int *totalTest, int *passedTest) 
{	
    tBoarding boardingCard;
    tFlight flight;
    tPlane plane;
    tPassenger p1, p2, p3;
    tAppData data;
    tError retVal;
    
    appData_init(&data);
    
	printf("=================================================\n");
	printf(" DATA CHECKING (Exercise 1) \n");
	printf("=================================================\n");

	getFlightObject(FLIGHT2, &flight);  
    getBookingObject(BOOKING2,&flight.bookings);
    flightsTable_add(&data.flights,flight,&retVal);

	printf("\nTest 1.1: Check flight with a non existing plane");
	(*totalTest)++;
    checkData(data.flights.table[0],data.passengers,data.planes,&retVal);
    if (retVal==ERR_NO_PLANE) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}    
    
	printf("\nTest 1.2: Check flight with an existing plane but invalid number of seats");
	(*totalTest)++;
    getPlaneObject(PLANE1, &plane);
    plane.seats= 17;
    planesTable_add(&data.planes,plane,&retVal);
    checkData(data.flights.table[0],data.passengers,data.planes,&retVal);
    if (retVal==ERR_INVALID_DATA) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}    

	printf("\nTest 1.3: Check flight with a correct plane but non-existing passenger");
	(*totalTest)++;
    planesTable_init(&data.planes);
    getPlaneObject(PLANE1, &plane);
    planesTable_add(&data.planes,plane,&retVal);
    checkData(data.flights.table[0],data.passengers,data.planes,&retVal);
    if (retVal==ERR_NO_PASSENGER) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}    
    
	printf("\nTest 1.4: Check flight already started: flight status");
	(*totalTest)++;
	getPassengerObject(PASSENGER1, &p1);
	getPassengerObject(PASSENGER2, &p2);
	getPassengerObject(PASSENGER3, &p3);
    passengerTable_add(&data.passengers,p1,&retVal);
    passengerTable_add(&data.passengers,p2,&retVal);
    passengerTable_add(&data.passengers,p3,&retVal);
    checkData(data.flights.table[0],data.passengers,data.planes,&retVal);
    if (retVal==ERR_STARTED_FLIGHT) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1.5: Check flight already started: boarding gate");
	(*totalTest)++;
    data.flights.table[0].status= BOOKING;
    checkData(data.flights.table[0],data.passengers,data.planes,&retVal);
    if (retVal==ERR_STARTED_FLIGHT) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}       
    
	printf("\nTest 1.6: Check flight already started: enqueued passengers");
	(*totalTest)++;
    data.flights.table[0].boardingGate= NO_BOARDING_GATE;
    boardingCard.passengerId= 10;
    boardingCard.row= NO_ROW;
    boardingCard.seat= NO_SEAT;
    boardingQueue_enqueue( &data.flights.table[0].priority, boardingCard );
    checkData(data.flights.table[0],data.passengers,data.planes,&retVal);
    if (retVal==ERR_STARTED_FLIGHT) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	} 
    
	printf("\nTest 1.7: Check flight: all checking passed");
	(*totalTest)++;
    boardingQueue_create( &data.flights.table[0].priority );
    checkData(data.flights.table[0],data.passengers,data.planes,&retVal);
    if (retVal==OK) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}     
}

void test_flight_checkin(int *totalTest, int *passedTest) 
{	
    int max_priority_row, max_front_row, max_back_row;
    tAppData data;
    tPassenger p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13;
    tFlight flight;
    tPlane plane;
    tError retVal;

    /* initialize structures */
    appData_init(&data);

    /* add a plane */
    getPlaneObject(PLANE3, &plane);
    planesTable_add(&data.planes,plane,&retVal);

    /* add passengers */
	getPassengerObject(PASSENGER1, &p1);
	getPassengerObject(PASSENGER2, &p2);
	getPassengerObject(PASSENGER3, &p3);
	getPassengerObject(PASSENGER4, &p4);
	getPassengerObject(PASSENGER5, &p5);
	getPassengerObject(PASSENGER6, &p6);
	getPassengerObject(PASSENGER7, &p7);
	getPassengerObject(PASSENGER8, &p8);
	getPassengerObject(PASSENGER9, &p9);
	getPassengerObject(PASSENGER10, &p10);
	getPassengerObject(PASSENGER11, &p11);
	getPassengerObject(PASSENGER12, &p12);
	getPassengerObject(PASSENGER13, &p13);
    passengerTable_add(&data.passengers,p1,&retVal);
    passengerTable_add(&data.passengers,p2,&retVal);
    passengerTable_add(&data.passengers,p3,&retVal);
    passengerTable_add(&data.passengers,p4,&retVal);
    passengerTable_add(&data.passengers,p5,&retVal);
    passengerTable_add(&data.passengers,p6,&retVal);
    passengerTable_add(&data.passengers,p7,&retVal);
    passengerTable_add(&data.passengers,p8,&retVal);
    passengerTable_add(&data.passengers,p9,&retVal);
    passengerTable_add(&data.passengers,p10,&retVal);
    passengerTable_add(&data.passengers,p11,&retVal);
    passengerTable_add(&data.passengers,p12,&retVal);
    passengerTable_add(&data.passengers,p13,&retVal);

    /* add flight with bookings */
  	getFlightObject(FLIGHT2, &flight);  
    getBookingObject(BOOKING3,&flight.bookings);
    flightsTable_add(&data.flights,flight,&retVal);

	printf("=================================================\n");
	printf(" FLIGHT CHECK-IN (Exercise 2) \n");
	printf("=================================================\n");
  
    checkinFlight(&data.flights.table[0], plane, &retVal);    
    getThresholdRows( plane.seats, &max_priority_row, &max_front_row, &max_back_row );

	printf("\nTest 2.1: Check flight status (checkin)");
	(*totalTest)++;
    if (retVal == OK &&
        data.flights.table[0].status == CHECKIN) 
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}  
    
	printf("\nTest 2.2: Check priority queue passengers (seating at rows 1 to %d)", max_priority_row);
	(*totalTest)++;
    if (retVal == OK &&
        boardingQueue_length( data.flights.table[0].priority ) == 6 &&
        data.flights.table[0].priority.table[0].passengerId == 10 &&
        data.flights.table[0].priority.table[1].passengerId == 20 &&
        data.flights.table[0].priority.table[2].passengerId == 30 &&  
        data.flights.table[0].priority.table[3].passengerId == 100 &&  
        data.flights.table[0].priority.table[4].passengerId == 110 &&  
        data.flights.table[0].priority.table[5].passengerId == 120) 
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}  

	printf("\nTest 2.3: Check front queue passengers (seating at rows %d to %d)", max_priority_row+1, max_front_row);
	(*totalTest)++;
    if (retVal == OK &&
        boardingQueue_length( data.flights.table[0].front ) == 1 &&
        data.flights.table[0].front.table[0].passengerId == 80)
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}  
    
	printf("\nTest 2.4: Check back queue passengers (seating at rows %d to %d)", max_front_row+1, max_back_row);
	(*totalTest)++;
    if (retVal == OK &&
        boardingQueue_length( data.flights.table[0].back ) == 5 &&
        data.flights.table[0].back.table[0].passengerId == 40 &&
        data.flights.table[0].back.table[1].passengerId == 50 &&
        data.flights.table[0].back.table[2].passengerId == 60 &&
        data.flights.table[0].back.table[3].passengerId == 70 &&
        data.flights.table[0].back.table[4].passengerId == 90)
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}  

	printf("\nTest 2.5: Check overbooking queue passengers (no seats assigned)");
	(*totalTest)++;
    if (retVal == OK &&
        boardingQueue_length( data.flights.table[0].overbooking ) == 1 &&
        data.flights.table[0].overbooking.table[0].passengerId == 130) 
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}      
}

void test_flight_boarding(int *totalTest, int *passedTest) 
{	
    tAppData data;
    tPassenger p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13;
    int prev_points_passenger_10, prev_points_passenger_20, prev_points_passenger_40;
    int prev_points_passenger_50, prev_points_passenger_70, prev_points_passenger_80;
    int post_points_passenger_10, post_points_passenger_20, post_points_passenger_40;
    int post_points_passenger_50, post_points_passenger_70, post_points_passenger_80;
    int prev_points_passenger_90, post_points_passenger_90;
    int prev_points_passenger_30, prev_points_passenger_60;
    int prev_points_passenger_110, prev_points_passenger_120;
    int prev_points_passenger_130, prev_points_passenger_100;    
    int post_points_passenger_30, post_points_passenger_60;
    int post_points_passenger_110, post_points_passenger_120;
    int post_points_passenger_130, post_points_passenger_100;
    tFlight flight;
    tPlane plane;
    tError retVal;

    /* initialize structures */
    appData_init(&data);

    /* add a plane */
    getPlaneObject(PLANE3, &plane);
    planesTable_add(&data.planes,plane,&retVal);

    /* add passengers */
	getPassengerObject(PASSENGER1, &p1);
	getPassengerObject(PASSENGER2, &p2);
	getPassengerObject(PASSENGER3, &p3);
	getPassengerObject(PASSENGER4, &p4);
	getPassengerObject(PASSENGER5, &p5);
	getPassengerObject(PASSENGER6, &p6);
	getPassengerObject(PASSENGER7, &p7);
	getPassengerObject(PASSENGER8, &p8);
	getPassengerObject(PASSENGER9, &p9);
	getPassengerObject(PASSENGER10, &p10);
	getPassengerObject(PASSENGER11, &p11);
	getPassengerObject(PASSENGER12, &p12);
	getPassengerObject(PASSENGER13, &p13);
    passengerTable_add(&data.passengers,p1,&retVal);
    passengerTable_add(&data.passengers,p2,&retVal);
    passengerTable_add(&data.passengers,p3,&retVal);
    passengerTable_add(&data.passengers,p4,&retVal);
    passengerTable_add(&data.passengers,p5,&retVal);
    passengerTable_add(&data.passengers,p6,&retVal);
    passengerTable_add(&data.passengers,p7,&retVal);
    passengerTable_add(&data.passengers,p8,&retVal);
    passengerTable_add(&data.passengers,p9,&retVal);
    passengerTable_add(&data.passengers,p10,&retVal);
    passengerTable_add(&data.passengers,p11,&retVal);
    passengerTable_add(&data.passengers,p12,&retVal);
    passengerTable_add(&data.passengers,p13,&retVal);

    /* add flight with bookings */
  	getFlightObject(FLIGHT2, &flight);  
    getBookingObject(BOOKING3,&flight.bookings);
    flightsTable_add(&data.flights,flight,&retVal);

    /* do flight checkin */
    checkinFlight(&data.flights.table[0], plane, &retVal);    

    /* setup the plane */
    setUpPlane(&data.planes.table[0]);

    /* store points of customer card holders */
    prev_points_passenger_10= data.passengers.table[0].fidelityPoints;
    prev_points_passenger_20= data.passengers.table[1].fidelityPoints;
    prev_points_passenger_40= data.passengers.table[3].fidelityPoints;
    prev_points_passenger_50= data.passengers.table[4].fidelityPoints;
    prev_points_passenger_70= data.passengers.table[6].fidelityPoints;
    prev_points_passenger_80= data.passengers.table[7].fidelityPoints;
    prev_points_passenger_90= data.passengers.table[8].fidelityPoints;

    /* store points of non customers card holders (undefined values) */
    prev_points_passenger_30 = data.passengers.table[2].fidelityPoints;
    prev_points_passenger_60 = data.passengers.table[5].fidelityPoints;
    prev_points_passenger_100= data.passengers.table[9].fidelityPoints;
    prev_points_passenger_110= data.passengers.table[10].fidelityPoints;
    prev_points_passenger_120= data.passengers.table[11].fidelityPoints;
    prev_points_passenger_130= data.passengers.table[12].fidelityPoints;

    /* do flight boarding */
    boardFlight( &data.flights.table[0], &data.passengers, 
                 &data.planes.table[0], &retVal ); 

	printf("=================================================\n");
	printf(" FLIGHT BOARDING (Exercise 3) \n");
	printf("=================================================\n");

	printf("\nTest 3.1: Check flight status (boarding)");
	(*totalTest)++;
    if (retVal == OK &&
        data.flights.table[0].status == BOARDING) 
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 3.2: Check plane layout");
	(*totalTest)++;
    if (retVal == OK &&
        data.planes.table[0].occupiedSeats == 13 &&
        data.planes.table[0].layout[0][0] == 10 &&  /* SEAT: 1A */
        data.planes.table[0].layout[0][1] == 20 &&  /* SEAT: 1B */
        data.planes.table[0].layout[0][2] == 30 &&  /* SEAT: 1C */
        data.planes.table[0].layout[0][3] == 100 && /* SEAT: 1D */
        data.planes.table[0].layout[0][4] == 110 && /* SEAT: 1E */
        data.planes.table[0].layout[0][5] == 120 && /* SEAT: 1F */
        data.planes.table[0].layout[1][0] == 80 &&  /* SEAT: 2A */
        data.planes.table[0].layout[1][1] == 130 && /* SEAT: 2B */
        data.planes.table[0].layout[2][0] == 40 &&  /* SEAT: 3A */
        data.planes.table[0].layout[2][1] == 50 &&  /* SEAT: 3B */
        data.planes.table[0].layout[2][2] == 60 &&  /* SEAT: 3C */
        data.planes.table[0].layout[2][3] == 70 &&  /* SEAT: 3D */
        data.planes.table[0].layout[2][4] == 90)    /* SEAT: 3E */
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 3.3: Check boarding fidelity points (customer card holders)");
    post_points_passenger_10= data.passengers.table[0].fidelityPoints;
    post_points_passenger_20= data.passengers.table[1].fidelityPoints;
    post_points_passenger_40= data.passengers.table[3].fidelityPoints;
    post_points_passenger_50= data.passengers.table[4].fidelityPoints;
    post_points_passenger_70= data.passengers.table[6].fidelityPoints;
    post_points_passenger_80= data.passengers.table[7].fidelityPoints;
    post_points_passenger_90= data.passengers.table[8].fidelityPoints;
	(*totalTest)++;
    if ((retVal == OK) && 
        (post_points_passenger_10 - prev_points_passenger_10 == BOARDING_POINTS) &&
        (post_points_passenger_20 - prev_points_passenger_20 == BOARDING_POINTS) &&
        (post_points_passenger_40 - prev_points_passenger_40 == BOARDING_POINTS) &&
        (post_points_passenger_50 - prev_points_passenger_50 == BOARDING_POINTS) &&
        (post_points_passenger_70 - prev_points_passenger_70 == BOARDING_POINTS) &&
        (post_points_passenger_80 - prev_points_passenger_80 == BOARDING_POINTS) &&
        (post_points_passenger_90 - prev_points_passenger_90 == BOARDING_POINTS))
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 3.4: Check boarding fidelity points (non customer card holders)");
    post_points_passenger_30 = data.passengers.table[2].fidelityPoints;
    post_points_passenger_60 = data.passengers.table[5].fidelityPoints;
    post_points_passenger_100= data.passengers.table[9].fidelityPoints;
    post_points_passenger_110= data.passengers.table[10].fidelityPoints;
    post_points_passenger_120= data.passengers.table[11].fidelityPoints;
    post_points_passenger_130= data.passengers.table[12].fidelityPoints;
	(*totalTest)++;
    if ((retVal == OK) && 
        (prev_points_passenger_30  == post_points_passenger_30) &&
        (prev_points_passenger_60  == post_points_passenger_60) &&
        (prev_points_passenger_100 == post_points_passenger_100) &&
        (prev_points_passenger_110 == post_points_passenger_110) &&
        (prev_points_passenger_120 == post_points_passenger_120) &&
        (prev_points_passenger_130 == post_points_passenger_130))
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void test_flight_overbooking(int *totalTest, int *passedTest)
{    
    int prev_n_overbookings, prev_n_bookings, post_n_overbookings, post_n_bookings; 
    int prev_fidelity_points_34, prev_fidelity_points_35, prev_fidelity_points_36;
    int prev_fidelity_points_37, prev_fidelity_points_38;
    int post_fidelity_points_34, post_fidelity_points_35, post_fidelity_points_36;
    int post_fidelity_points_37, post_fidelity_points_38;
    int i, index;
    tAppData data;
    tPassenger p;
    tFlight flight;
    tPlane plane;
    tError retVal;

    /* initialize structures */
    appData_init(&data);

    /* add a plane */
    getPlaneObject(PLANE3, &plane);
    planesTable_add(&data.planes,plane,&retVal);

    /* add dummy passengers until the plane is full + 5 more overbooked passengers*/
    getPassengerObject(PASSENGER1, &p);
    for (i= 0; i<plane.seats + 5; i++) 
    {
        passengerTable_add(&data.passengers,p,&retVal);
        p.cardNumber++;
        p.id++;
    }
    
    /* set the last one as non card holder */
    data.passengers.table[data.passengers.nPassengers-1].customerCardHolder= FALSE;
    data.passengers.table[data.passengers.nPassengers-1].cardNumber= 0;
    data.passengers.table[data.passengers.nPassengers-1].fidelityPoints= 0;

    /* add flights with bookings */
  	getFlightObject(FLIGHT2, &flight);  
    getBookingObject(BOOKING4,&flight.bookings);
    flightsTable_add(&data.flights,flight,&retVal);

    /* do flight checkin */
    checkinFlight(&data.flights.table[0], plane, &retVal);    

    /* setup the plane */
    setUpPlane(&data.planes.table[0]);

    /* get fidelity points before boarding */
    prev_fidelity_points_34= data.passengers.table[24].fidelityPoints;
    prev_fidelity_points_35= data.passengers.table[25].fidelityPoints;
    prev_fidelity_points_36= data.passengers.table[26].fidelityPoints;
    prev_fidelity_points_37= data.passengers.table[27].fidelityPoints;
    prev_fidelity_points_38= data.passengers.table[28].fidelityPoints;
    
    /* do flight boarding */
    boardFlight( &data.flights.table[0], &data.passengers, 
                 &data.planes.table[0], &retVal ); 

	printf("=================================================\n");
	printf(" FLIGHT OVERBOOKING (Exercise 4) \n");
	printf("=================================================\n");

	printf("\nTest 4.1: Check flight result (all seats occupied and 'no free gap' while boarding)");
	(*totalTest)++;
    if (retVal == ERR_NO_FREE_GAP &&
        data.flights.table[0].status == BOARDING && 
        data.planes.table[0].seats == data.planes.table[0].occupiedSeats) 
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 4.2: Check overbooked passengers");
	(*totalTest)++;
    if (boardingQueue_length(data.flights.table[0].overbooking)== 5  && 
        data.flights.table[0].overbooking.table[0].passengerId == 34 && 
        data.flights.table[0].overbooking.table[1].passengerId == 35 &&  
        data.flights.table[0].overbooking.table[2].passengerId == 36 &&  
        data.flights.table[0].overbooking.table[3].passengerId == 37 &&  
        data.flights.table[0].overbooking.table[4].passengerId == 38 ) 
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 4.3: Check no boarding points added to overbooked passengers");
    post_fidelity_points_34= data.passengers.table[24].fidelityPoints;
    post_fidelity_points_35= data.passengers.table[25].fidelityPoints;
    post_fidelity_points_36= data.passengers.table[26].fidelityPoints;
    post_fidelity_points_37= data.passengers.table[27].fidelityPoints;
    post_fidelity_points_38= data.passengers.table[28].fidelityPoints;
	(*totalTest)++;
    if (prev_fidelity_points_34 == post_fidelity_points_34 &&
        prev_fidelity_points_35 == post_fidelity_points_35 && 
        prev_fidelity_points_36 == post_fidelity_points_36 && 
        prev_fidelity_points_37 == post_fidelity_points_37 && 
        prev_fidelity_points_38 == post_fidelity_points_38) 
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

    /* add more flights */
  	getFlightObject(FLIGHT3, &flight);  
    getBookingObject(BOOKING1,&flight.bookings);
    flightsTable_add(&data.flights,flight,&retVal);

  	getFlightObject(FLIGHT4, &flight);  
    getBookingObject(BOOKING5,&flight.bookings);
    flightsTable_add(&data.flights,flight,&retVal);

	printf("\nTest 4.4: Search next flight");
	(*totalTest)++;
    index= searchNextFlight( data.flights, data.flights.table[0].originAirport, 
                             data.flights.table[0].destinationAirport, 1 );
    if (index == 2) 
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 4.5: Reallocate passengers: check number of passengers transferred");
	(*totalTest)++;
    prev_n_overbookings= boardingQueue_length(data.flights.table[0].overbooking);
    prev_n_bookings= data.flights.table[2].bookings.nElem;
    reallocatePassengers( &data.flights.table[0].overbooking, 
                          &data.flights.table[2].bookings,
                          &data.passengers );
    post_n_overbookings= boardingQueue_length(data.flights.table[0].overbooking);
    post_n_bookings= data.flights.table[2].bookings.nElem;
    if (prev_n_overbookings + prev_n_bookings == post_n_overbookings + post_n_bookings &&
        post_n_overbookings == 0) 
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 4.6: Reallocate passengers: check correct insertion");
	(*totalTest)++;
    if (data.flights.table[2].bookings.table[0].passenger==34 && 
        data.flights.table[2].bookings.table[1].passenger==35 &&  
        data.flights.table[2].bookings.table[2].passenger==36 &&  
        data.flights.table[2].bookings.table[3].passenger==37 &&  
        data.flights.table[2].bookings.table[4].passenger==38 &&  
        data.flights.table[2].bookings.table[5].passenger==40 &&  
        data.flights.table[2].bookings.table[6].passenger==50 &&  
        data.flights.table[2].bookings.table[7].passenger==60 &&  
        data.flights.table[2].bookings.table[8].passenger==70 &&  
        data.flights.table[2].bookings.table[9].passenger==80 ) 
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 4.7: Reallocate passengers: check priority for card holders");
	(*totalTest)++;
    if (data.flights.table[2].bookings.table[0].passenger== 34   && 
        data.flights.table[2].bookings.table[0].priority == TRUE &&
        data.flights.table[2].bookings.table[1].passenger== 35   &&  
        data.flights.table[2].bookings.table[1].priority == TRUE &&
        data.flights.table[2].bookings.table[2].passenger== 36   &&
        data.flights.table[2].bookings.table[2].priority == TRUE &&
        data.flights.table[2].bookings.table[3].passenger== 37   &&
        data.flights.table[2].bookings.table[3].priority == TRUE) 
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 4.8: Reallocate passengers: check no priority for non-card holders");
	(*totalTest)++;
    if (data.flights.table[2].bookings.table[4].passenger== 38 &&
        data.flights.table[2].bookings.table[4].priority == FALSE)
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 4.9: Reallocate passengers: check overbooking points added for card holders");
    post_fidelity_points_34= data.passengers.table[24].fidelityPoints;
    post_fidelity_points_35= data.passengers.table[25].fidelityPoints;
    post_fidelity_points_36= data.passengers.table[26].fidelityPoints;
    post_fidelity_points_37= data.passengers.table[27].fidelityPoints;
	(*totalTest)++;
    if ((post_fidelity_points_34 - prev_fidelity_points_34 == OVERBOOKING_POINTS) &&
        (post_fidelity_points_35 - prev_fidelity_points_35 == OVERBOOKING_POINTS) && 
        (post_fidelity_points_36 - prev_fidelity_points_36 == OVERBOOKING_POINTS) && 
        (post_fidelity_points_37 - prev_fidelity_points_37 == OVERBOOKING_POINTS))
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 4.10: Reallocate passengers: check no overbooking points for non-card holders");
    post_fidelity_points_38= data.passengers.table[28].fidelityPoints;
	(*totalTest)++;
    if (post_fidelity_points_38 == prev_fidelity_points_38)
    {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void runTestsPR2(int *totalTest, int *passedTest) {
	*totalTest=0;
	*passedTest=0;
	
    test_data_checking(totalTest, passedTest);
    test_flight_checkin(totalTest, passedTest);
    test_flight_boarding(totalTest, passedTest);
    test_flight_overbooking(totalTest, passedTest);
}
