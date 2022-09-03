#include "data.h"
#include "api.h"

/* Request an option to the user and check its validity */
int getOption(int numOptions);

/* Define the main menu options type */
typedef enum {MAIN_MENU_LOAD, MAIN_MENU_SAVE, MAIN_MENU_PASSENGER, 
              MAIN_MENU_PLANE, MAIN_MENU_STAT,
              MAIN_MENU_EXIT} tMainMenuOptions;

/* Define the passengers management menu options type */
typedef enum {PASSENGER_MENU_LIST, PASSENGER_MENU_ADD, PASSENGER_MENU_DEL, 
              PASSENGER_MENU_CLEAR_ALL, PASSENGER_MENU_PASSENGERS_BY_COUNTRY,
			  PASSENGER_MENU_PASSENGERS_BY_AGE_INTERVAL,
              PASSENGER_MENU_EXIT} tPassengerMenuOptions;

/* Define the planes management menu options type */
typedef enum {PLANE_MENU_LIST, PLANE_MENU_ADD, PLANE_MENU_UTILITY, PLANE_MENU_ACTIVE_PLANES,
              PLANE_MENU_EXIT} tPlaneMenuOptions;

/* Define the stats menu options type */
typedef enum {STAT_MENU_NUM_CARD_HOLDER_PASSENGERS, STAT_MENU_MAX_FIDELITY_POINTS,
			  STAT_MENU_AVG_CAPACITY, STAT_MENU_MAX_PLANE_HEIGHT,
              STAT_MENU_EXIT} tStatMenuOptions;

/* Print the main menu options */
void printMainMenuOptions();

/* Get the option for the main menu */
tMainMenuOptions getMenuOption();

/* Perform the actions for the main menu */
void mainMenu(tAppData *appData);

/* Print the passenger management menu options */
void printPassengerMenuOptions();

/* Get the option for the passenger management menu */
tPassengerMenuOptions getPassengerMenuOption();

/* Perform the actions for the passenger management menu */
void passengerMenu(tAppData *appData);

/* Print the planes management menu options */
void printPlaneMenuOptions();

/* Get the option for the planes management menu */
tPlaneMenuOptions getPlaneMenuOption();

/* Perform the actions for the planes management menu */
void planeMenu(tAppData *appData);

/* Print the stats menu options */
void printStatMenuOptions();

/* Get the option for the status menu */
tStatMenuOptions getStatMenuOption();

/* Perform the actions for the status menu */
void statMenu(tAppData appData);
