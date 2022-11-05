#ifndef ROUTERECORDS_H
#define ROUTERECORDS_H

typedef struct routeRecord_struct
{
	char orgCode[4];
	char destCode[4];
	char airlineCode[3];
	int passengerCount[6];
}routeRecord;

typedef enum SearchType { ROUTE, ORIGIN, DESTINATION, AIRLINE } SearchType;

routeRecord *createRecords( FILE *fileIn );

int fillRecords( routeRecord *r, FILE *fileIn );

int findAirlineRoute( routeRecord *r, int length, const char *origin, const char *destination, const char *airline );

void searchRecords( routeRecord *r, int length, const char *key1, const char *key2, SearchType st );

void printRecords( routeRecord *r, int length);
void printMenu();

#endif


