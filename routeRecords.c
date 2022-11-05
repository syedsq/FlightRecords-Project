#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "routerecords.h"

//creates array of routeRecord and initializes it
routeRecord *createRecords( FILE *fileIn)
{
        int N = 0;
	int i = 0;

        if(fileIn == NULL)
        {
                printf("Error\n");
        }
        char buffer[1000];

        while(!feof(fileIn))
        {
                fgets(buffer, 1000, fileIn);
                N++;
        }
        rewind(fileIn);
	
	routeRecord *r = (routeRecord*)malloc(sizeof(routeRecord) * N);
	int j;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < 6;j++)
		{
			r[i].passengerCount[j] = 0;
		}
	}
	return r;
}

//This function process the CSV file and enters data into the array.
int fillRecords( routeRecord *r, FILE *fileIn )
{
	int numMonth, N, i, passCount;
	N = 0;
	i = 0;
	
	char origin[4], destination[4], airLn[4],type[11];
	char buffer[1000];

	fgets(buffer, 1000, fileIn);
	while(fgets(buffer,1000, fileIn) != NULL)
	{
		sscanf(buffer,"%d,%[^,],%[^,],%[^,],%[^,],%d", &numMonth, origin, destination, airLn, type, &passCount);
		if(strlen(airLn) == 2)
		{	
			i = findAirlineRoute(r, N, origin, destination, airLn);
			if(i != -1)
			{
				r[i].passengerCount[numMonth - 1] = passCount;
			}
			else
			{
				strcpy(r[N].orgCode, origin);;
				strcpy(r[N].destCode, destination);
				strcpy(r[N].airlineCode, airLn);
				r[N].passengerCount[numMonth - 1] = passCount;
				N++;
			}
		}
	}
	rewind(fileIn);
	return N;
	
}

//This function finds record in the routeRecord array with the same origin, destination and airline code and returns that index of that record
int findAirlineRoute( routeRecord *r, int length, const char *origin, const char *destination, const char *airline )
{
	int i;
	for(i = 0; i < length; i++)
	{
		if((strcmp(r[i].orgCode, origin)==0) && (strcmp(r[i].destCode, destination)==0) && (strcmp(r[i].airlineCode, airline)==0))
		{
			return i;
		}
	}
	return -1;

}

//This function searches the routeRecord and prints the result of the search.
void searchRecords( routeRecord *r, int length, const char *key1, const char *key2, SearchType st )
{
	int i, avg = 0, totalPass = 0, janTotal = 0, febTotal = 0, marTotal = 0, aprTotal = 0, mayTotal = 0, juneTotal = 0, matches = 0;

	if(st == ROUTE)
	{	
		printf("Searching by route..\n");
		for(i = 0; i < length; i++)
		{
			if((strcmp(r[i].orgCode, key1)==0) && (strcmp(r[i].destCode, key2)==0))
			{
				printf("%s (%s-%s) ", r[i].airlineCode, r[i].orgCode, r[i].destCode);
				janTotal += r[i].passengerCount[0];
				febTotal += r[i].passengerCount[1];
				marTotal += r[i].passengerCount[2];
				aprTotal += r[i].passengerCount[3];
				mayTotal += r[i].passengerCount[4];
				juneTotal += r[i].passengerCount[5];
				matches++;
			}
			
		}	
		totalPass = janTotal + febTotal + marTotal + aprTotal + mayTotal + juneTotal;
		avg = totalPass / 6;
		
		printf("\n");	
		printf("%d matches found.\n", matches);	
	
		printf("\n");
		printf("Statistics\n");
  		printf("Total Passengers: %d\n", totalPass);
    		printf("Total Passengers in Month 1: %d\n", janTotal);
   		printf("Total Passengers in Month 2: %d\n", febTotal);
   		printf("Total Passengers in Month 3: %d\n", marTotal);
   		printf("Total Passengers in Month 4: %d\n", aprTotal);
   		printf("Total Passengers in Month 5: %d\n", mayTotal);
   		printf("Total Passengers in Month 6: %d\n", juneTotal);
		printf("\n");
   		printf("Average Passengers per Month: %d\n", avg); 
		
	}
	
	if( st == ORIGIN)
	{
		printf("Searching by origin..\n");
		for(i = 0; i < length; i++)
                {
                        if(strcmp(r[i].orgCode, key1)==0)
                        {
                                printf("%s (%s-%s) ", r[i].airlineCode, r[i].orgCode, r[i].destCode);
                                janTotal += r[i].passengerCount[0];
                                febTotal += r[i].passengerCount[1];
                                marTotal += r[i].passengerCount[2];
                                aprTotal += r[i].passengerCount[3];
                                mayTotal += r[i].passengerCount[4];
                                juneTotal += r[i].passengerCount[5];
                                matches++;
                        }
                       
               }
        	totalPass = janTotal + febTotal + marTotal + aprTotal + mayTotal + juneTotal;
        	avg = totalPass / 6;
		
		printf("\n");
        	printf("%d matches found.\n", matches);

        	printf("\n");
        	printf("Statistics\n");
        	printf("Total Passengers: %d\n", totalPass);
        	printf("Total Passengers in Month 1: %d\n", janTotal);
        	printf("Total Passengers in Month 2: %d\n", febTotal);
        	printf("Total Passengers in Month 3: %d\n", marTotal);
        	printf("Total Passengers in Month 4: %d\n", aprTotal);
        	printf("Total Passengers in Month 5: %d\n", mayTotal);
        	printf("Total Passengers in Month 6: %d\n", juneTotal);
        	printf("\n");
        	printf("Average Passengers per Month: %d\n", avg);
	}

	if( st == DESTINATION)
	{
		printf("Searching by destination..\n");

		for(i = 0; i < length; i++)
                {
                        if(strcmp(r[i].destCode, key1)==0)
                        {
				
                                printf("%s (%s-%s) ", r[i].airlineCode, r[i].orgCode, r[i].destCode);
                                janTotal += r[i].passengerCount[0];
                                febTotal += r[i].passengerCount[1];
                                marTotal += r[i].passengerCount[2];
                                aprTotal += r[i].passengerCount[3];
                                mayTotal += r[i].passengerCount[4];
                                juneTotal += r[i].passengerCount[5];
                                matches++;
                        }
                }
       		totalPass = janTotal + febTotal + marTotal + aprTotal + mayTotal + juneTotal;
        	avg = totalPass / 6;
		
		printf("\n");
        	printf("%d matches found.\n", matches);

        	printf("\n");
        	printf("Statistics\n");
        	printf("Total Passengers: %d\n", totalPass);
        	printf("Total Passengers in Month 1: %d\n", janTotal);
        	printf("Total Passengers in Month 2: %d\n", febTotal);
        	printf("Total Passengers in Month 3: %d\n", marTotal);
        	printf("Total Passengers in Month 4: %d\n", aprTotal);
        	printf("Total Passengers in Month 5: %d\n", mayTotal);
        	printf("Total Passengers in Month 6: %d\n", juneTotal);
        	printf("\n");
        	printf("Average Passengers per Month: %d\n", avg);
	}

	if( st == AIRLINE)
	{
		printf("Searching by airline..\n");
		for(i = 0; i < length; i++)
                {
                        if(strcmp(r[i].airlineCode, key1)==0)
                        {
				
                                printf("%s (%s-%s) ", r[i].airlineCode, r[i].orgCode, r[i].destCode);
                                janTotal += r[i].passengerCount[0];
                                febTotal += r[i].passengerCount[1];
                                marTotal += r[i].passengerCount[2];
                                aprTotal += r[i].passengerCount[3];
                                mayTotal += r[i].passengerCount[4];
                                juneTotal += r[i].passengerCount[5];
                                matches++;
                        }
                }
        	totalPass = janTotal + febTotal + marTotal + aprTotal + mayTotal + juneTotal;
       		avg = totalPass / 6;
		
		printf("\n");
        	printf("%d matches found.\n", matches);

       		printf("\n");
        	printf("Statistics\n");
        	printf("Total Passengers: %d\n", totalPass);
        	printf("Total Passengers in Month 1: %d\n", janTotal);
        	printf("Total Passengers in Month 2: %d\n", febTotal);
        	printf("Total Passengers in Month 3: %d\n", marTotal);
        	printf("Total Passengers in Month 4: %d\n", aprTotal);
        	printf("Total Passengers in Month 5: %d\n", mayTotal);
        	printf("Total Passengers in Month 6: %d\n", juneTotal);
        	printf("\n");
        	printf("Average Passengers per Month: %d\n", avg);
	
	}
	

}

//This function prints the records.
void printRecords( routeRecord *r, int length)
{
	int i = 0;
	for(i = 0; i < length; i++)
	{
		printf("%s %s %s", r[i].orgCode, r[i].destCode, r[i].airlineCode);
		printf("January: %d\nFebruary: %d\nMarch: %d\nApril: %d\nMay: %d\nJune: %d\n", r[i].passengerCount[0], r[i].passengerCount[1], r[i].passengerCount[2], r[i].passengerCount[3], r[i].passengerCount[4], r[i]. passengerCount[5]);
	}
}

void printMenu()
{
        printf( "\n\n######### Airline Route Records Database MENU #########\n" );
        printf( "1. Search by Route\n" );
        printf( "2. Search by Origin Airport\n" );
        printf( "3. Search by Destination Airport\n" );
        printf( "4. Search by Airline\n" );
        printf( "5. Quit\n" );
        printf( "Enter your selection: " );

}
