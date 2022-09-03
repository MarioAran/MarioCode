#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "plane.h"
#include "passenger.h"

int getOption(int numOptions) {
	int option=0;
		
	while(option<1 || option>numOptions) {
		/* Read the input */
		printf(">> ");
			scanf("%u", &option);
		getchar();
		
		/* Check the user input */
		if(option<1 || option>numOptions) {
			printf("Incorrect option.\n");
		}
	}
	 return option;
}

void readPassenger(tPassenger *passenger, tError *retVal) {	

	*retVal = OK;

	int number;
	char buffer[MAX_LINE];
	int length;

	/* Request information from user */ 
    printf("Passenger id (integer less than %d):\n>> ", MAX_PASSENGERS);
    scanf("%d",&number);
	if(number>MAX_PASSENGERS) {
		*retVal = ERROR;
	} else{
		passenger->id = (tPassengerId)number;
	}
	getchar();

    printf("Name (%d char max, no spaces):\n>> ", MAX_NAME-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_NAME) {
		strncpy(passenger->name,buffer,MAX_NAME);
	} else {
		*retVal = ERROR;
	}
	getchar();

    printf("Surname (%d char max, no spaces):\n>> ", MAX_SURNAME-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_SURNAME) {
		strncpy(passenger->surname,buffer,MAX_SURNAME);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Document Type (1 digit being 0=NIF, 1=NIE, 2=PASSPORT, 3=DRIVING_LICENSE, 4=OTHER_DOCUMENTS):\n>> ");
	scanf("%d",&number);
	if(number>=0 && number <=4) {
		passenger->docType = (tDocumentType)(number);
	} else {
		*retVal = ERROR;
	}
	getchar();

    printf("Document number (%d char max, no spaces):\n>> ", MAX_DOC_NUMBER-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_DOC_NUMBER) {
		strncpy(passenger->docNumber,buffer,MAX_DOC_NUMBER);
	} else {
		*retVal = ERROR;
	}
	getchar();
    
	printf("Birthdate Year:\n>> ");
	scanf("%d",&passenger->birthDate.year);
	getchar();
	
	printf("Birthdate Month:\n>> ");
	scanf("%d",&passenger->birthDate.month);
	getchar();
   
	printf("Birthdate Day:\n>> ");
	scanf("%d",&passenger->birthDate.day);
	getchar();
	
	printf("Country (2-digit ISO-3166 code):\n>> ");
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_COUNTRY_CODE) {
		strncpy(passenger->countryISOCode,buffer,MAX_COUNTRY_CODE);
	} else {
		*retVal = ERROR;
	}
	getchar();
	
	printf("Is a customer card holder? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		passenger->customerCardHolder = TRUE;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		passenger->customerCardHolder = FALSE;
	} else {
		*retVal = ERROR;
	}
	
    if (passenger->customerCardHolder) {        
        printf("Card number:\n>> ");
        scanf("%d",&passenger->cardNumber);
        getchar();
        
        printf("Fidelity points:\n>> ");
        scanf("%d",&passenger->fidelityPoints);
        getchar();
    } else {
        passenger->cardNumber= 0;
        passenger->fidelityPoints= 0;        
    }
}

void readPlane(tPlane *plane, tError *retVal) {	

	*retVal = OK;

	char buffer[MAX_LINE];
	int number, length, seats;

	printf("Plane id (integer less than %d):\n>> ",MAX_PLANES);
	scanf("%d",&number);
	if(number>MAX_PLANES) {
		*retVal = ERROR;
	} else {
		plane->id= (tPlaneId)(number);
	}
	getchar();
	
    printf("Plane plate number (max %d char, no spaces):\n>> ", MAX_PLATE_NUMBER-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_PLATE_NUMBER) {
		strncpy(plane->plateNumber,buffer,MAX_PLATE_NUMBER);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Plane producer (max %d char, no spaces):\n>> ", MAX_PRODUCER_NAME-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_PRODUCER_NAME) {
		strncpy(plane->producer,buffer,MAX_PRODUCER_NAME);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Plane model (max %d char, no spaces):\n>> ", MAX_MODEL_NAME-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_MODEL_NAME) {
		strncpy(plane->model,buffer,MAX_MODEL_NAME);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Fabrication year:\n>> ");
	scanf("%d",&(plane->year));
	getchar();

	printf("Plane utility (1 digit being 0=COMMERCIAL 1=PRIVATE 2=GOVERNMENTAL 3=MILITAR 4=EXPERIMENTAL 5=OTHERS):\n>> ");
	scanf("%d",&number);
	if(number>=0 && number <=5) {
		plane->utility= (tPlaneUtility)(number);
	} else {
		*retVal = ERROR;
	}
	getchar();
	
	printf("Plane weight (in tones):\n>> ");
	scanf("%f",&(plane->weight));
	getchar();
	
	printf("Plane max speed (in km/h):\n>> ");
	scanf("%f",&(plane->maxSpeed));
	getchar();

	printf("Plane max flight height (in number of feet):\n>> ");
	scanf("%d",&(plane->maxHeight));
	getchar();
	
	printf("Number of motors:\n>> ");
	scanf("%d",&(plane->motors));
	getchar();
	
	printf("Capacity of plane (in number of seats):\n>> ");
	scanf("%d",&seats);
	getchar();
    while (seats % MAX_SEATS_PER_ROW != 0)
    {
        printf("Incorrect capacity (entered value must be a multiple of %d).\n", MAX_SEATS_PER_ROW);
        printf("Capacity of plane (in number of seats):\n>> ");
        scanf("%d",&seats);
        getchar();
    }
    plane->seats= seats;

	printf("Is an active plane? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		plane->isActive = TRUE;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		plane->isActive = FALSE;
	} else {
		*retVal = ERROR;
	}
	getchar();
}

void printPlaneTable(tPlaneTable table) {
    
  	int i;	
	char planeStr[MAX_LINE];
	
	if(table.nPlanes==0) {
		printf("No planes.\n");
	} else {
		for(i=0;i<table.nPlanes;i++) {
			getPlaneStr(table.table[i], MAX_LINE, planeStr);
			printf("[%u] - %s\n", i+1, planeStr);
		}		
	}
}

void printPassengerTable(tPassengerTable table) {
	int i;	
	char passengerStr[MAX_LINE];
	
	if(table.nPassengers==0) {
		printf("No passengers.\n");
	} else {
		for(i=0;i<table.nPassengers;i++) {
			getPassengerStr(table.table[i], MAX_LINE, passengerStr);
			printf("[%u] - %s\n", i+1, passengerStr);
		}		
	}
}


/*****************
 **   MAIN MENU **
*****************/
void printMainMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Main Menu \n");
	printf("=======================\n");
	printf("1) Load data from file\n");
	printf("2) Save data to file\n");
	printf("3) Manage passengers\n");
	printf("4) Manage planes\n");
	printf("5) View statistics\n");
	printf("6) Exit\n");	
}

tMainMenuOptions getMainMenuOption() {
	/* Convert to the correct type */
	return (tMainMenuOptions)(getOption(6)-1);
}

void mainMenu(tAppData *appData) 
{
	tMainMenuOptions option;
	tError retVal;
		
	/* Assign the data path */
	appData_setPath(appData,"../");
		
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printMainMenuOptions();
		option=getMainMenuOption();
		
		/* Do the action for the given option */
		if (option == MAIN_MENU_LOAD) {
			appData_load(appData,&retVal);
			if(retVal==OK) {
				printf("Data loaded\n");
			} else {	
				printf("No previous data loaded\n");
			}
		} else if (option == MAIN_MENU_SAVE) {
			appData_save(*appData,&retVal);
			if(retVal==OK) {
				printf("Data saved\n");
			} else {	
				printf("Cannot save the data\n");
			}
		} else if (option == MAIN_MENU_PASSENGER) {
			passengerMenu(appData);
		} else if (option == MAIN_MENU_PLANE) {
			planeMenu(appData);
		} else if (option == MAIN_MENU_STAT) {
			statMenu(*appData);
		} 
	} while (option!=MAIN_MENU_EXIT);
}

/*********************************
 **   PASSENGER MANAGEMENT MENU **
*********************************/
void printPassengerMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage Passengers\n");
	printf("=======================\n");
	printf("1) List passengers\n");	
	printf("2) Add passenger\n");
	printf("3) Delete passenger\n");	
	printf("4) Clear all passengers\n");
	printf("5) Get list of passengers by country\n");	
	printf("6) Get list of passengers by age interval\n");	
	printf("7) Exit\n");	
}

tPassengerMenuOptions getPassengerMenuOption() {
	/* Convert to the correct type */
	return (tPassengerMenuOptions)(getOption(7)-1);
}

void passengerMenu(tAppData *appData) {
	tPassengerMenuOptions option;
	tPassenger newPassenger;
	tPassengerTable passengerTable,resultTable;
	char passengerStr[MAX_LINE];
	int i, pos=0;
	tDate minDate, maxDate;
    tCountry countryCode;
	tError retVal;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printPassengerMenuOptions();
		option=getPassengerMenuOption();
		
		/* Do the action for the given option */
		if (option == PASSENGER_MENU_LIST ) {
			getPassengers(*appData, &passengerTable);
			printPassengerTable(passengerTable);
		} else if (option == PASSENGER_MENU_ADD) {
			printf("Enter the information for the new passenger:\n");
			readPassenger(&newPassenger,&retVal);
			getPassengerStr(newPassenger, MAX_LINE, passengerStr);
			if(retVal==OK) {
				addPassenger(appData, newPassenger, &retVal);
				if(retVal==OK){
					printf("Passenger added: %s\n", passengerStr);
				} else if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("Duplicated passenger not added: %s\n", passengerStr);
				} else {
					printf("No more space. Passenger not added: %s\n", passengerStr);
				}
			} else {
				printf("Error in input. Passenger not added: %s\n", passengerStr);
			}
		} else if (option == PASSENGER_MENU_DEL) {
			getPassengers(*appData, &passengerTable);			
			/* Print the passengers */			
			printPassengerTable(passengerTable);		

			if (passengerTable.nPassengers > 0) {
				/* Ask the number of the register to be removed */
				printf("Enter the number of the passenger to delete:\n");
				pos=getOption(passengerTable.nPassengers);
				/* Remove the selected passenger */				
				removePassenger(appData, passengerTable.table[pos-1]);
			}
		} else if (option == PASSENGER_MENU_CLEAR_ALL) {
			getPassengers(*appData, &passengerTable);	
			for (i= 0; i< passengerTable.nPassengers; i++) {
				/* Remove the passenger */				
				removePassenger(appData, passengerTable.table[i]);
			}
		} else if (option == PASSENGER_MENU_PASSENGERS_BY_COUNTRY) {
			printf("Country code):\n");
			scanf("%s",countryCode);			
			getPassengers(*appData, &passengerTable);
			passengerTable_filterByCountry(passengerTable,countryCode,&resultTable); 
			printPassengerTable(resultTable);	
			
		} else if (option == PASSENGER_MENU_PASSENGERS_BY_AGE_INTERVAL) {
			printf("Enter minimum birthdate. Year:\n");
			scanf("%d",&minDate.year);
			printf("Enter minimum birthdate. Month:\n");
			scanf("%d",&minDate.month);
			printf("Enter minimum birthdate. Day:\n");
			scanf("%d",&minDate.day);
			printf("Enter maximum birthdate. Year:\n");
			scanf("%d",&maxDate.year);
			printf("Enter maximum birthdate. Month:\n");
			scanf("%d",&maxDate.month);
			printf("Enter maximum birthdate. Day:\n");
			scanf("%d",&maxDate.day);			
            getPassengers(*appData, &passengerTable);
			passengerTable_filterByBirthDateInterval(passengerTable, minDate, maxDate, &resultTable); 
			printPassengerTable(resultTable);	
		}

	} while(option!=PASSENGER_MENU_EXIT);
}

/********************************
 **   PLANE MANAGEMENT MENU **
********************************/
void printPlaneMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage planes\n");
	printf("=======================\n");
	printf("1) List planes\n");	
	printf("2) Add plane\n");
	printf("3) List planes by utility\n");
	printf("4) List active planes\n");
	printf("5) Exit\n");	
}

tPlaneMenuOptions getPlaneMenuOption() {
	/* Convert to the correct type */
	return (tPlaneMenuOptions)(getOption(5)-1);
}

void planeMenu(tAppData *appData) {
	tError retVal = OK;
	tPlaneMenuOptions option;
	tPlaneTable planeTable, utilTable, activeTable;
	tPlane newPlane;
	char planeStr[MAX_LINE];
	int utility;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printPlaneMenuOptions();
		option=getPlaneMenuOption();
		
		/* Do the action for the given option */
		if (option == PLANE_MENU_LIST) {
			getPlanes(*appData, &planeTable);
			printPlaneTable(planeTable);
		} else if (option == PLANE_MENU_ADD) {
			readPlane(&newPlane,&retVal);
			getPlaneStr(newPlane, MAX_LINE, planeStr);
			if(retVal==OK) {
				addPlane(appData, newPlane, &retVal);
				if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("ERROR: A plane with the same ID already exists\n");
				} else {
					printf("Plane added: %s\n", planeStr);
				}
			} else {
				printf("Error in input. Plane not added: %s\n", planeStr);
			}
		} else if (option == PLANE_MENU_UTILITY) {
			getPlanes(*appData, &planeTable);
			printf("Plane utility (1 digit being 0=COMMERCIAL 1=PRIVATE 2=GOVERNMENTAL 3=MILITAR 4=EXPERIMENTAL 5=OTHERS):\n");
			scanf("%d",&utility);
			planesTable_filterByUtility(planeTable, (tPlaneUtility)utility, &utilTable);
			printPlaneTable(utilTable);
		} else if (option == PLANE_MENU_ACTIVE_PLANES) {
			getPlanes(*appData, &planeTable);
			planesTable_getActivePlanes(planeTable, &activeTable);
			printPlaneTable(activeTable);
		}
	} while(option!=PLANE_MENU_EXIT);	
}


/******************
 **   STAT MENU **
******************/
void printStatMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Stats \n");
	printf("=======================\n");
	printf("1) Get number of card holders\n");	
	printf("2) Get max number of fidelity points\n");	
	printf("3) Get average plane capacity for a plane utility\n");	
	printf("4) Get maximum plane flight height\n");	
	printf("5) Exit\n");	
}

tStatMenuOptions getStatMenuOption() {
	/* Convert to the correct type */
	return (tStatMenuOptions)(getOption(5)-1);
}

void statMenu(tAppData appData) {
	tStatMenuOptions option;
	tPassengerTable passengerTable;
	tPlaneTable planeTable;
    int utility, numCardHolderPassengers, maxPoints;
	
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printStatMenuOptions();
		option=getStatMenuOption();
		
		/* Do the action for the given option */
		if (option == STAT_MENU_NUM_CARD_HOLDER_PASSENGERS) {			
			getPassengers(appData, &passengerTable);
			numCardHolderPassengers= passengerTable_getNumberOfCardHolders(passengerTable); 
			printf("Number of card holders: %d\n", numCardHolderPassengers);

		} else if (option == STAT_MENU_MAX_FIDELITY_POINTS) {
			getPassengers(appData, &passengerTable);
			maxPoints= passengerTable_getMaxFidelityPoints(passengerTable); 
			printf("Maximum number of fidelity points: %d points\n", maxPoints);
		
		} else if (option == STAT_MENU_AVG_CAPACITY) {
			getPlanes(appData, &planeTable);
			printf("Plane utility (1 digit being 0=COMMERCIAL 1=PRIVATE 2=GOVERNMENTAL 3=MILITAR 4=EXPERIMENTAL 5=OTHERS):\n");
			scanf("%d",&utility);
			printf("Average capacity by utility: %.2f seats\n", planeTable_getAverageCapacityByUtility(planeTable,(tPlaneUtility)utility));
		} else if (option == STAT_MENU_MAX_PLANE_HEIGHT) {
			getPlanes(appData, &planeTable);
			printf("Maximum plane height: %d feet\n", planeTable_getMaxPlaneHeight(planeTable));
		} 
		
	} while(option!=STAT_MENU_EXIT);	
}
